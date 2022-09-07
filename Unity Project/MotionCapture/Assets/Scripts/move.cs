using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

using System;
using System.Linq;
using System.IO.Ports;
using SimpleCircularBuffer;

using FusionFx;

public class Move : MonoBehaviour
{
    [Header("Serial Conf")]
    [SerializeField] private int baudrate = 921600;
    [SerializeField] private String comPort = "COM3";
    SerialPort port;
    private int bufSize = 512;
    private SimpleCircularBuffer<byte> buf;

    private const int TMsg_MaxLen = 256;

    private const byte TMsg_EOF = 0xF0;
    private const byte TMsg_BS = 0xF1;
    private const byte TMsg_BS_EOF = 0xF2;

	[Header("Segment")]
	[SerializeField] private Transform segment;
	[SerializeField] private Transform segCore;
	[SerializeField] private Transform testCore;

	[Header("Text")]
    [SerializeField] private Text heTxt;

    private bool isCalibrate = false;
    private bool doCalibarate = false;
    private Vector3 calibrationVector;

    private string segName;


    void Start()
    {
        buf = new SimpleCircularBuffer<byte>(bufSize, true);

        port = new SerialPort(comPort, baudrate, Parity.None, 8, StopBits.One);

        port.Open();

        heTxt.GetComponent<Text>().text = comPort;
    }

    private void Update()
    {
		try
		{
			if (port.IsOpen && port.BytesToRead > 0)
			{
				var tBuf = new byte[bufSize];
				var readLen = port.Read(tBuf, 0, TMsg_MaxLen);
				// Debug.Log(string.Join(", ",tBuf));

				if (readLen > 0)
				{
					buf.Push(tBuf, 0, readLen);

					int bufLen = buf.Used;

					for (int i = 0; i < bufLen; i++)
					{
						if (buf.Get(i) == TMsg_EOF)
						{
							//Debug.Log("len : " + i);

							var frame = new byte[i + 1];
							int frameLen = 0;

							for (int idx = 0; idx < i; idx++)
							{
								if (buf.Get(idx) == TMsg_BS)
								{
									if (buf.Get(idx + 1) == TMsg_BS) frame[frameLen] = TMsg_BS;
									else if (buf.Get(idx + 1) == TMsg_BS_EOF) frame[frameLen] = TMsg_EOF;
									else
									{
										Debug.LogError("Invalid BS Sequence!!!!!!");
									}
									frameLen++;
									idx++;
								}
								else
								{
									frame[frameLen] = buf.Get(idx);
									frameLen++;
								}
							}

							buf.Pop(i + 1);

							if (checkCKS(frame.Take(i).ToArray()))
							{   // 체크섬 통과
								if (frame[2] == 0x13 + 0x80)
								{
									Debug.Log(segName + " Rcv Msg : " + string.Join(", ", frame));
								}
								else if (frame[2] == 0x08)
								{ // Command Check
									FusionFxFrame fx = new FusionFxFrame(frame);


									heTxt.GetComponent<Text>().text = comPort + "(" + segName + ") : " + fx.headingErr;

									if (doCalibarate)
									{
										//calibrationVector = new Vector3(fx.rot_y, -fx.rot_x, fx.rot_z);

										if (testCore != null) testCore.rotation = Quaternion.Euler(0, 0, 90);

										transform.rotation = Quaternion.Euler(-fx.rot_y, fx.rot_x, -fx.rot_z);

										//segment.rotation = Quaternion.Euler(0,0,90);
										if (segName.Equals("leftUpperArm")) segment.rotation = Quaternion.Euler(0, 0, 90);
										else segment.rotation = Quaternion.Euler(0, 0, 90);

										isCalibrate = true;
										doCalibarate = false;
									}

									if (isCalibrate)
									{

										if (testCore != null && segCore != null)
										{
											segCore.transform.rotation = Quaternion.Euler(-fx.rot_y, fx.rot_x, -fx.rot_z);  // 절대
											testCore.transform.rotation = segment.rotation; // 보정
										}
										transform.rotation = Quaternion.Euler(-fx.rot_y, fx.rot_x, -fx.rot_z);

										//if (segName.Equals("leftLowerArm")) Debug.Log("" + transform.eulerAngles);
										/*
										if (testCore != null && segCore != null)
										{
											segCore.transform.rotation = Quaternion.Euler(-fx.rot_y, fx.rot_x, -fx.rot_z);
											testCore.transform.rotation = segCore.transform.rotation;
											testCore.transform.Rotate(calibrationVector);
											if (segName.Equals("leftUpperArm"))
												testCore.transform.Rotate(new Vector3(0, 0, 90));
											transform.rotation = testCore.transform.rotation;
										}
										{
											transform.rotation = Quaternion.Euler(-fx.rot_y, fx.rot_x, -fx.rot_z);
											transform.Rotate(calibrationVector);
											if (segName.Equals("leftUpperArm"))
												transform.Rotate(new Vector3(0, 0, 90));
										}
										*/
									}
								}
							}
							else
							{
								Debug.LogError("CehckSum Failed : [" + i + "] " + string.Join(", ", frame));
							}

							break;
						}
					}

				}
			}
		}
		catch (Exception e)
		{
			Debug.Log(e);
		}
	}

	public void startCalibration(string seg)
	{
		segName = seg;
		heTxt.GetComponent<Text>().text = comPort + "(" + segName + ") : ";
		doCalibarate = true;
	}

	public void testFunction()
	{
		//transform.rotation = Quaternion.Euler(0,0,90);


		//transform.rotation = Quaternion.Euler(30,40,60);

		//segment.rotation = Quaternion.Euler(0,0,90);
		//transform.rotation = Quaternion.Euler(0,0,180);
		//segCore.rotation = Quaternion.Euler(0,90,0);
		onClickBtnSendMsg();
	}

	private void OnApplicationQuit()
	{
		sendStopMsg();
		port.Close();
	}


	public void onClickBtnSendMsg()
	{
		var testFrame = new byte[5];

		testFrame[0] = 50;      // dst addr
		testFrame[1] = 1;       // src addr
		testFrame[2] = 0x13;    // cmd 1 = ping cmd 0x13 get Output type
		testFrame[3] = 0;
		testFrame[4] = TMsg_EOF;

		testFrame[3] = computeCKS(testFrame);

		port.Write(testFrame, 0, 5);
	}

	public void sendStartMsg()
	{
		var startFrame = new byte[6];

		startFrame[0] = 50;
		startFrame[1] = 1;
		startFrame[2] = 0x08;
		startFrame[3] = 0x70;
		startFrame[4] = 0;
		startFrame[5] = TMsg_EOF;

		startFrame[4] = computeCKS(startFrame);

		port.Write(startFrame, 0, 6);
	}

	public void sendStopMsg()
	{
		var testFrame = new byte[5];

		testFrame[0] = 50;      // dst addr
		testFrame[1] = 1;       // src addr
		testFrame[2] = 0x09;        // cmd 1 = ping
		testFrame[3] = 0;
		testFrame[4] = TMsg_EOF;

		testFrame[3] = computeCKS(testFrame);

		port.Write(testFrame, 0, 5);
	}

	private byte computeCKS(byte[] frame)
	{
		byte rtv = 0;

		foreach (byte b in frame)
		{
			if (b != TMsg_EOF) rtv -= b;
		}

		return rtv;
	}

	private bool checkCKS(byte[] frame)
	{
		byte rtv = 0;

		foreach (byte b in frame)
		{
			rtv += b;
		}

		return (rtv == 0) ? true : false;
	}
}
