using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

using System;
using System.Linq;
using System.IO.Ports;

public class SerialMotion : MonoBehaviour
{
    [Header("Serial Conf")]
	[SerializeField] private int baudrate = 115200;
	[SerializeField] private String comPort = "COM5";
	SerialPort port;

    [Header("Segment")]
	[SerializeField] private Transform segment;
	[SerializeField] private Transform segCore;
	[SerializeField] private Transform testCore;


    [SerializeField] private Text msgText;
    private bool isSync = false;
    private bool isCalibrate = false;
	private bool doCalibarate = false;
	private Vector3 calibrationVector;
    private string segName;

    private float qi;
    private float qj;
    private float qk;
    private float qs;
    private float SCALE_FACTOR = 10000.0f;
    private Quaternion quat;
    private Quaternion rotOffset = Quaternion.identity;

    private string strExt = "-- MOTIONFX APPLICATION SERVER : NOTIFY CLIENT WITH NEW QUAT PARAMETER VALUE \n  \n";
    // Start is called before the first frame update
    void Start()
    {
        port = new SerialPort(comPort, baudrate, Parity.None, 8, StopBits.One);
        port.ReadTimeout = 30;
        port.Open();
        quat = Quaternion.identity;
    }

    // Update is called once per frame
    void Update()
    {
        try
        {
            if (port.IsOpen)
            {
                //string msg = port.ReadTo("-- MOTIONFX APPLICATION SERVER : NOTIFY CLIENT WITH NEW QUAT PARAMETER VALUE");
                string msg = port.ReadTo("\r");
                //msgText.GetComponent<Text>().text = msg;
                
                if (msg.CompareTo(strExt) != 0) 
                {
                    //msgText.GetComponent<Text>().text = msg;


                    string[] split_msg = msg.Split("/");
                    split_msg[0].Replace(" ", "");
                    string[] q = split_msg[0].Split(",");

                    // qi qj qk
                    qi = float.Parse(q[0]) / SCALE_FACTOR;
                    qj = float.Parse(q[1]) / SCALE_FACTOR;
                    qk = float.Parse(q[2]) / SCALE_FACTOR;
                    
                    
                    qs = ComputeQs(qi, qj, qk);
                    quat.Set(qi, qj, qk , qs);
                    Debug.Log(qi.ToString() + "," + qj.ToString() + "," + qk.ToString() + "," + qs.ToString());


                    if (doCalibarate)
                    {
                        //rotOffset = transform.rotation;
                        rotOffset = transform.localRotation;
                        if (testCore != null) testCore.rotation = Quaternion.Euler(0,0,90);

                        transform.rotation = quat;
                        
                        segment.rotation = Quaternion.Euler(0,0,90);

                        isCalibrate = true;
                        doCalibarate = false;
                    }

                    if (isCalibrate)
                    {
                        if (testCore != null)
                        {
                            testCore.transform.rotation = segment.rotation;
                        }
                        transform.rotation = quat; 
                        
                    }
                    
                }
                
                
            }
        }
        catch(Exception e) 
        {
            // Debug.Log(e);

        }
    }

    // public void OpenPort()
    // {
    //     port.Open();
    // }

    // public void ClosePort()
    // {
    //     port.Close();
    //     isSync = false;
    // }

    public void startCalibration()
    {
        doCalibarate = true;
    }

    float ComputeQs(float qi, float qj, float qk)
    {
        float t = 1f - (qi * qi + qj * qj + qk * qk);

        if (t > 0)
        {
            return (float)Math.Sqrt(t);
        }
        else
        {
            return 0;
        }
    }

    Quaternion getEulerInverse (Quaternion q)
	{
		Vector3 e = q.eulerAngles;
		e.x *= -1;
		e.y *= -1;
		return Quaternion.Euler (e);
	}
}
