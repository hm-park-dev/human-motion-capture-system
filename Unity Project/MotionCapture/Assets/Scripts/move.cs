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

    float x_acc = 0;
    float y_acc = 0;
    float z_acc = 0;

    float x_gyr = 0;
    float y_gyr = 0;
    float z_gyr = 0;

    float x_mag = 0;
    float y_mag = 0;
    float z_mag = 0;


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
        /*
        if (x_acc != 0 && y_acc != 0 && z_acc != 0 && x_gyr != 0 && y_gyr != 0 && z_gyr != 0 && x_mag != 0 && y_mag != 0 && z_mag != 0)
        {
            double pitch = 180 * Math.Atan2(x_acc, Math.Sqrt(y_acc * y_acc + z_acc * z_acc)) / Math.PI;
            double roll = 180 * Math.Atan2(y_acc, Math.Sqrt(x_acc * x_acc + z_acc * z_acc)) / Math.PI;

            double mag_x = x_mag * Math.Cos(pitch) + y_mag * Math.Sin(roll) * Math.Sin(pitch) + z_mag * Math.Cos(roll) * Math.Sin(pitch);
            double mag_y = y_mag * Math.Cos(roll) - z_mag * Math.Sin(roll);
            double yaw = 180 * Math.Atan2(-mag_y, mag_x) / Math.PI;

            this.transform.rotation = Quaternion.Euler((float)pitch, (float)roll, 0);
        }
        */
    }



    void OnApplicationQuit()
    {
        m_SerialPort.Close();
    }
}
