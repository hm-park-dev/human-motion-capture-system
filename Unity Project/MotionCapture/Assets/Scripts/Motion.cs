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

	[Header("Text")]
	[SerializeField] private Text heTxt;

	private bool isCalibrate = false;
	private bool doCalibarate = false;
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

		if (doCalibarate)
                    {
                        //rotOffset = transform.rotation;
                        rotOffset = transform.localRotation;
                        if (testCore != null) testCore.rotation = Quaternion.Euler(0,0,-90);

                        transform.rotation = quat;
                        
                        segment.rotation = Quaternion.Euler(0,0,-90);

                        isCalibrate = true;
                        doCalibarate = false;
                    }

                    if (isCalibrate)
                    {
                        if (testCore != null)
                        {
                            testCore.transform.rotation = segment.rotation;
                            //testCore.transform.rotation = quat;
                        }
                        transform.rotation = quat; 
                        
                    }
	}


	public void startCalibration(string seg)
	{
		segName = seg;
		// heTxt.GetComponent<Text>().text = comPort + "(" + segName + ") : ";
		doCalibarate = true;
	}

	public void sendQuaternion(float qi, float qj, float qk, float qs)
	{
		i = qi;
		j = qj;
		k = qk;
		w = qs;


		quat.Set(i, j, k, w);
	}

}