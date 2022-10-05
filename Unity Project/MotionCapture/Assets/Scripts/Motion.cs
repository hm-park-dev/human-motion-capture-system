using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

using System;
using System.Linq;
using System.IO.Ports;
using SimpleCircularBuffer;

using FusionFx;

public class Motion : MonoBehaviour
{
	[Header("Segment")]
	[SerializeField] private Transform segment;
	[SerializeField] private Transform segCore;
	[SerializeField] private Transform testCore;
	[SerializeField] private int degre;

	[Header("Text")]
	[SerializeField] private Text heTxt;

	private bool isCalibrate = false;
	private bool doCalibrate = false;
	private bool pre = true;
	private bool received = false;
	private Vector3 calibrationVector;

	private float i = 0f;
	private float j = 0f;
	private float k = 0f;
	private float w = 0f;
	private Quaternion quat = Quaternion.identity;
    private Quaternion rotOffset = Quaternion.identity;

	private string segName;

	byte[] receiveBuffer;

	void Start()
	{
		receiveBuffer = new byte[256];
	}

	void Update()
	{
		if (pre && received)
		{
			doCalibrate = true;
			pre = false;
		}
		
		if (doCalibrate)
        {
            //rotOffset = transform.rotation;
            //rotOffset = transform.localRotation;
            if (testCore != null) testCore.rotation = Quaternion.Euler(0,0,degre);
            transform.rotation = quat;

            segment.rotation = Quaternion.Euler(0,0,degre);

            isCalibrate = true;
            doCalibrate = false;
        }

        if (isCalibrate)
        {
            if (testCore != null)
            {
                //testCore.transform.rotation = segment.rotation;
                testCore.transform.rotation = quat;
            }
            transform.rotation = quat; 
            // transform.rotation = rotOffset * quat; 

        }
		
		/*
		// Using Slerp
		if (doCalibrate)
        {
            //rotOffset = transform.rotation;
            //rotOffset = transform.localRotation;
            if (testCore != null) testCore.rotation = Quaternion.Euler(0,0,-90);
            transform.rotation = Quaternion.Slerp(transform.rotation, quat, 0.8f);
            segment.rotation = Quaternion.Euler(0,0,-90);

            isCalibrate = true;
            doCalibrate = false;
        }

        if (isCalibrate)
        {
            if (testCore != null)
            {
                testCore.transform.rotation = segment.rotation;
                //testCore.transform.rotation = quat;
            }
            transform.rotation = Quaternion.Slerp(transform.rotation, quat, 0.8f);
                        
        }
		*/
	}


	public void reSync()
	{
		isCalibrate = false;
		doCalibrate = true;
	}

	public void sendQuaternion(float qi, float qj, float qk, float qs)
	{
		i = qi;
		j = qj;
		k = qk;
		w = qs;
		received = true;

		// quat.Set(0, i, -j, w);
		quat.Set(i, k, -j, w);
	}
}