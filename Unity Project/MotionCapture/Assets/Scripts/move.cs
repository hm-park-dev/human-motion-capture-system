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
	private Quaternion q;

	private string segName;

	byte[] receiveBuffer;

	void Start()
	{
		receiveBuffer = new byte[256];
		q = new Quaternion(i, j, k, w);
	}

	void Update()
	{

		if (doCalibarate)
		{
			//Debug.Log("doing doCalibarate");
			// calibrationVector = new Vector3(j, -i, k);

			// if (testCore != null) testCore.rotation = Quaternion.Euler(0, 0, 90);
			//transform.rotation = Quaternion.Euler(q.eulerAngles);
			transform.rotation = Quaternion.Lerp(transform.rotation, q, 0.01f);

			// segment.rotation = Quaternion.Euler(0,0,90);
			if (segName.Equals("Left_Upper_Arm_Joint_01"))
				segment.rotation = Quaternion.Euler(0, 0, 90);
			else segment.rotation = Quaternion.Euler(0, 0, 90);

			isCalibrate = true;
			doCalibarate = false;
		}

		if (isCalibrate)
		{
			// Debug.Log("doing isCalibarate");
			// Debug.Log("i: " + i + " j: " + j + " k: " + k + " w: " + w);
			if (testCore != null && segCore != null)
			{
				//segCore.transform.rotation = Quaternion.Euler(FromQ2(q));  // ����
				//testCore.transform.rotation = segment.rotation; // ����
			}
			//transform.rotation = Quaternion.Euler(q.eulerAngles);
			transform.rotation = Quaternion.Lerp(transform.rotation, q, 0.01f);

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


		q.Set(i, j, k, w);
	}

}