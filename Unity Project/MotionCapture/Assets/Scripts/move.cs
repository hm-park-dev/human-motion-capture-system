using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using System.IO.Ports;
using System;

public class move : MonoBehaviour
{
    // Serial Port Test
    public Text serialText;

    SerialPort m_SerialPort = new SerialPort("COM3", 115200, Parity.None, 8, StopBits.One);
    string m_Data = null;
    public bool setOrigin = false;
    Quaternion rotOffset = Quaternion.identity;

    const double RAD_TO_DEG = 180 / Math.PI;
    const float dt = 1000.0f;

    float x_acc = 0;
    float y_acc = 0;
    float z_acc = 0;

    float x_gyr = 0;
    float y_gyr = 0;
    float z_gyr = 0;

    float x_mag = 0;
    float y_mag = 0;
    float z_mag = 0;

    double pitch;
    double roll;

    Kalman kalmanX = new Kalman();
    Kalman kalmanY = new Kalman();
    double gyroXangle, gyroYangle; // Angle calculate using the gyro only
    double compAngleX, compAngleY; // Calculated angle using a complementary filter
    double kalAngleX, kalAngleY; // Calculated angle using a Kalman filter


    void Start()
    {
        m_SerialPort.Open();

        if (setOrigin)
        {
            rotOffset = this.transform.rotation;
            setOrigin = false;
        }
    }

    private void Update()
    {
        Test();
    }

    void Test()
    {
        try
        {
            if (m_SerialPort.IsOpen)
            {
                m_Data = m_SerialPort.ReadLine();
                m_SerialPort.ReadTimeout = 1000;
            }
        }
        catch (Exception e)
        {
            Debug.Log(e);
        }

        string[] values = m_Data.Split(',');

        if (values.Length == 5 && values[0] == "ACC") // Rotation of the first one 
        {
            x_acc = float.Parse(values[2]);
            y_acc = float.Parse(values[3]);
            z_acc = float.Parse(values[4]);
            // this.transform.rotation = new Quaternion(w, x, y, z) * Quaternion.Inverse(rotOffset);
        }
        else if (values.Length == 5 && values[0] == "GYR")
        {
            x_gyr = float.Parse(values[2]);
            y_gyr = float.Parse(values[3]);
            z_gyr = float.Parse(values[4]);
        }
        else if (values.Length == 5 && values[0] == "MAG")
        {
            x_mag = float.Parse(values[2]);
            y_mag = float.Parse(values[3]);
            z_mag = float.Parse(values[4]);
        }
        else if (values.Length != 5)
        {
            Debug.LogWarning(m_Data);
        }

        
        serialText.text = "ACC: " + x_acc.ToString() + " " + y_acc.ToString() + " " + z_acc.ToString() 
            + "\nGYR: " + x_gyr.ToString() + " " + y_gyr.ToString() + " " + z_gyr.ToString() 
            + "\nMAG: " + x_mag.ToString() + " " + y_mag.ToString() + " " + z_mag.ToString();
        

        pitch = 180 * Math.Atan2(-x_acc, Math.Sqrt(y_acc * y_acc + z_acc * z_acc)) / Math.PI;
        // double roll = 180 * Math.Atan2(y_acc, Math.Sqrt(x_acc * x_acc + z_acc * z_acc)) / Math.PI;
        roll = 180 * Math.Atan2(y_acc, z_acc) / Math.PI;
    
        gyroXangle = roll;
        gyroYangle = pitch;
        compAngleX = roll;
        compAngleY = pitch;
        double gyroXrate = x_gyr / 131.0; // Convert to deg/s
        double gyroYrate = y_gyr / 131.0; // Convert to deg/s

        if ((roll < -90 && kalAngleX > 90) || (roll > 90 && kalAngleX < -90))
        {
            kalmanX.setAngle((float)roll);
            compAngleX = roll;
            kalAngleX = roll;
            gyroXangle = roll;
        }
        else
            kalAngleX = kalmanX.getAngle((float)roll, (float)gyroXrate, dt); // Calculate the angle using a Kalman filter

        if (Math.Abs(kalAngleX) > 90)
            gyroYrate = -gyroYrate; // Invert rate, so it fits the restriced accelerometer reading
        kalAngleY = kalmanY.getAngle((float)pitch, (float)gyroYrate, dt);

        gyroXangle += gyroXrate * dt; // Calculate gyro angle without any filter
        gyroYangle += gyroYrate * dt;
        //gyroXangle += kalmanX.getRate() * dt; // Calculate gyro angle using the unbiased rate
        //gyroYangle += kalmanY.getRate() * dt;

        compAngleX = 0.93 * (compAngleX + gyroXrate * dt) + 0.07 * roll; // Calculate the angle using a Complimentary filter
        compAngleY = 0.93 * (compAngleY + gyroYrate * dt) + 0.07 * pitch;

        // Reset the gyro angle when it has drifted too much
        if (gyroXangle < -180 || gyroXangle > 180)
            gyroXangle = kalAngleX;
        if (gyroYangle < -180 || gyroYangle > 180)
            gyroYangle = kalAngleY;

        Debug.Log(kalAngleX.ToString() + " " + kalAngleY.ToString());
        this.transform.rotation = Quaternion.Euler((float)kalAngleX, (float)kalAngleY, 0);
    }



    void OnApplicationQuit()
    {
        m_SerialPort.Close();
    }
}

class Kalman
{
    private float Q_angle = 0.001f;
    private float Q_bias = 0.003f;
    private float R_measure = 0.03f;

    private float angle = 0.0f;
    private float bias = 0.0f;
    private float rate;

    private float[,] P = new float[2, 2];

    public float getAngle(float newAngle, float newRate, float dt)
    {
        rate = newRate - bias;
        angle += dt * rate;

        // Update estimation error covariance - Project the error covariance ahead
        /* Step 2 */
        P[0, 0] += dt * (dt * P[1, 1] - P[0, 1] - P[1, 0] + Q_angle);
        P[0, 1] -= dt * P[1, 1];
        P[1, 0] -= dt * P[1, 1];
        P[1, 1] += Q_bias * dt;

        // Discrete Kalman filter measurement update equations - Measurement Update ("Correct")
        // Calculate Kalman gain - Compute the Kalman gain
        /* Step 4 */
        float S = P[0, 0] + R_measure; // Estimate error
        /* Step 5 */
        float[] K = new float[2]; // Kalman gain - This is a 2x1 vector
        K[0] = P[0, 0] / S;
        K[1] = P[1, 0] / S;

        // Calculate angle and bias - Update estimate with measurement zk (newAngle)
        /* Step 3 */
        float y = newAngle - angle; // Angle difference
        /* Step 6 */
        angle += K[0] * y;
        bias += K[1] * y;

        // Calculate estimation error covariance - Update the error covariance
        /* Step 7 */
        float P00_temp = P[0, 0];
        float P01_temp = P[0, 1];

        P[0, 0] -= K[0] * P00_temp;
        P[0, 1] -= K[0] * P01_temp;
        P[1, 0] -= K[1] * P00_temp;
        P[1, 1] -= K[1] * P01_temp;

        return angle;
    }

    public void setAngle(float angle)
    {
        this.angle = angle;
    }

    public float getRate()
    {
        return this.rate;
    }

    public void setQangle(float Q_angle)
    {
        this.Q_angle = Q_angle;
    }

    public void setQbias(float Q_bias)
    {
        this.Q_bias = Q_bias;
    }

    public void setRmeasure(float R_measure) { this.R_measure = R_measure; }

    public float getQangle() { return this.Q_angle; }

    public float getQbias() { return this.Q_bias; }

    public float getRmeasure() { return this.R_measure; }
}
