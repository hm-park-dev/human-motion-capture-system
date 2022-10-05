using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using System.Net.Sockets;
using System.Text;
using System;
using System.IO;
using System.Runtime.InteropServices;

public class SerialController : MonoBehaviour
{
    [Header("Serial Motion")]
    [SerializeField] private SerialMotion leftUpperArm;
    [SerializeField] private SerialMotion leftForearm;
    // [SerializeField] private SerialMotion leftWrist;
    // [SerializeField] private SerialMotion rightUpperArm;
    // [SerializeField] private SerialMotion rightForearm;
    // [SerializeField] private SerialMotion rightWrist;

    private Dictionary<string, SerialMotion> comPorts;

    [Header("Button Conf")]
    [SerializeField] private Button streamingButton;
    [SerializeField] private Button syncButton;
    [SerializeField] private Text streamingBtnText;
    [SerializeField] private Text billboardText;
    [SerializeField] private Text connectionText;

    private bool streaming = false;
    private bool synchronizing = false;
    private bool synchronized = false;
    private float syncTime = 0f;
    [SerializeField] private int syncDuration = 3;

    // Start is called before the first frame update
    void Start()
    {
        billboardText.GetComponent<Text>().text = "";
        connectionText.GetComponent<Text>().text = "";
        streamingButton.onClick.AddListener(OnClickStreaming);
        syncButton.onClick.AddListener(OnClickSyncBtn);

        comPorts = new Dictionary<string, SerialMotion>();
        if (leftUpperArm != null) comPorts.Add("leftUpperArm", leftUpperArm);
        if (leftForearm != null) comPorts.Add("leftForearm", leftForearm);
        // if (leftWrist != null) comPorts.Add("leftWrist", leftWrist);
        // if (rightUpperArm != null) comPorts.Add("rightUpperArm", rightUpperArm);
        // if (rightForearm != null) comPorts.Add("rightForearm", rightForearm);
        // if (rightWrist != null) comPorts.Add("rightWrist", rightWrist);
    }

    // Update is called once per frame
    void Update()
    {
        if (synchronizing)
        {
            syncTime -= Time.deltaTime;

            billboardText.GetComponent<Text>().text = string.Format("준비하세요.\n{0:0.00}", syncTime);

            if (syncTime < 0)
            {
                synchronizing = false;
                billboardText.GetComponent<Text>().text = "";
                
                foreach (KeyValuePair<string, SerialMotion> element in comPorts)
                {
                    element.Value.startCalibration();
                }
            }
        }
    }

    public void OnClickStreaming()
    {
        if (streaming)
        {
            // foreach (KeyValuePair<string, SerialMotion> element in comPorts)
            //     element.Value.ClosePort();
            streamingBtnText.GetComponent<Text>().text = "Start Streaming";
            streaming = false;
            Debug.Log("Stop Button Click");
        }
        else
        {
            //  foreach (KeyValuePair<string, SerialMotion> element in comPorts)
            //      element.Value.OpenPort();
            streamingBtnText.GetComponent<Text>().text = "Stop Streaming";
            streaming = true;
            Debug.Log("Start Button Click");
        }
    }

    public void OnClickSyncBtn()
    {
        if (streaming && !synchronizing)
        {
            Debug.Log("Sync Button Click");
            syncTime = (float)syncDuration;
            billboardText.GetComponent<Text>().text = "" + syncTime;
            synchronizing = true;
            
        }
    }
}
