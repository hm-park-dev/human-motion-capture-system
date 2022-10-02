using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using System.Net.Sockets;
using System.Text;
using System;
using System.IO;
using System.Runtime.InteropServices;

public class Controller : MonoBehaviour
{
    [Header("Motion")]
    [SerializeField] private Motion leftUpperArm;
    [SerializeField] private Motion leftForearm;
    [SerializeField] private Motion leftWrist;
    [SerializeField] private Motion rightUpperArm;
    [SerializeField] private Motion rightForearm;
    [SerializeField] private Motion rightWrist;


    [Header("Socket Conf")]
    [SerializeField] private string serverIP = "192.168.0.11";
    [SerializeField] private int Port = 8080;
    [SerializeField] private Button newSockSetButton;
    [SerializeField] private InputField ipField;
    [SerializeField] private InputField portField;

    TcpClient client;
    byte[] receiveBuffer;
    StreamReader reader;
    bool socketReady = false;
    NetworkStream stream;

    private Dictionary<string, Motion> comPorts;

    [Header("Button Conf")]
    [SerializeField] private Button streamingButton;
    [SerializeField] private Button syncButton;
    [SerializeField] private Text streamingBtnText;
    [SerializeField] private Text syncBtnText;
    [SerializeField] private Text billboardText;
    [SerializeField] private Text connectionText;

    private bool streaming = false;
    private bool synchronizing = false;
    private bool synchronized = false;
    private float syncTime = 0f;
    [SerializeField] private int syncDuration = 3;

    private float i;
    private float j;
    private float k;
    private float w;

    // Start is called before the first frame update
    void Start()
    {

        billboardText.GetComponent<Text>().text = "";
        connectionText.GetComponent<Text>().text = "Gateway IP: " + serverIP + "\nPort: " + Port.ToString();
        streamingButton.onClick.AddListener(OnClickStreaming);
        syncButton.onClick.AddListener(OnClickSyncBtn);
        newSockSetButton.onClick.AddListener(OnClickSocketBtn);

        comPorts = new Dictionary<string, Motion>();
        if (leftUpperArm != null) comPorts.Add("leftUpperArm", leftUpperArm);
        if (leftForearm != null) comPorts.Add("leftForearm", leftForearm);
        if (leftWrist != null) comPorts.Add("leftWrist", leftWrist);
        if (rightUpperArm != null) comPorts.Add("rightUpperArm", rightUpperArm);
        if (rightForearm != null) comPorts.Add("rightForearm", rightForearm);
        if (rightWrist != null) comPorts.Add("rightWrist", rightWrist);

    }

    // Update is called once per frame
    void Update()
    {
        billboardText.GetComponent<Text>().text = "";
        connectionText.GetComponent<Text>().text = "Gateway IP: " + serverIP + "\nPort: " + Port.ToString();

        // Sync 버튼 클릭시
        if (synchronizing)
        {
            syncTime -= Time.deltaTime;

            billboardText.GetComponent<Text>().text = string.Format("준비하세요.\n{0:0.00}", syncTime);

            // Sync 대기 시간이 지남
            if (syncTime < 0)
            {
                synchronizing = false;
                billboardText.GetComponent<Text>().text = "";
                synchronized = true;
                syncBtnText.GetComponent<Text>().text = "Re Sync";

                if (socketReady)
                {
                    if (stream.DataAvailable)
                    {
                        receiveBuffer = new byte[500];
                        string msg = reader.ReadLine();
                        // Debug.Log(msg);

                        string[] split_msg = msg.Split(',');

                        if (split_msg.Length == 16)
                        {
                            i = float.Parse(split_msg[1]);
                            j = float.Parse(split_msg[2]);
                            k = float.Parse(split_msg[3]);
                            w = float.Parse(split_msg[4]);
                            switch (split_msg[0])
                            {
                                case "P2PSRV1":
                                    leftWrist.sendQuaternion(i, j, k, w);
                                    break;
                                case "P2PSRV2":
                                    leftForearm.sendQuaternion(i, j, k, w);
                                    break;
                                case "P2PSRV3":
                                    leftUpperArm.sendQuaternion(i, j, k, w);
                                    break;
                                case "P2PSRV4":
                                    rightUpperArm.sendQuaternion(i, j, k, w);
                                    break;
                                case "P2PSRV5":
                                    rightForearm.sendQuaternion(i, j, k, w);
                                    break;
                                case "P2PSRV6":
                                    rightWrist.sendQuaternion(i, j, k, w);
                                    break;
                                default:
                                    break;
                            }

                        }
                        else {
                            Debug.Log("length X");
                        }

                    }
                }
            }
        }

        if (synchronized)
        {
            if (socketReady)
            {
                if (stream.DataAvailable)
                {
                    receiveBuffer = new byte[500];
                    string msg = reader.ReadLine();
                    Debug.Log(msg);

                    string[] split_msg = msg.Split(',');

                    if (split_msg.Length == 16)
                    {
                        i = float.Parse(split_msg[1]);
                        j = float.Parse(split_msg[2]);
                        k = float.Parse(split_msg[3]);
                        w = float.Parse(split_msg[4]);

                        switch (split_msg[0])
                        {
                            case "P2PSRV1":
                                leftWrist.sendQuaternion(i, j, k, w);
                                break;
                            case "P2PSRV2":
                                leftForearm.sendQuaternion(i, j, k, w);
                                break;
                            case "P2PSRV3":
                                leftUpperArm.sendQuaternion(i, j, k, w);
                                break;
                            case "P2PSRV4":
                                rightUpperArm.sendQuaternion(i, j, k, w);
                                break;
                            case "P2PSRV5":
                                rightForearm.sendQuaternion(i, j, k, w);
                                break;
                            case "P2PSRV6":
                                rightWrist.sendQuaternion(i, j, k, w);
                                break;
                            default:
                                Debug.Log("switch default: " + split_msg[0]);
                                break;
                        }
                        
                    }
                    else {
                        Debug.Log("Error MSG: " + msg);
                    }

                }
            }
        }
    }

    public void OnClickStreaming()
    {
        if (streaming)
        {
            //foreach (KeyValuePair<string, Move> element in comPorts)
            //    element.Value.sendStopMsg();
            streamingBtnText.GetComponent<Text>().text = "Start Streaming";
            streaming = false;

            CloseSocket();
        }
        else
        {
            //foreach (KeyValuePair<string, Move> element in comPorts)
            //    element.Value.sendStartMsg();
            streamingBtnText.GetComponent<Text>().text = "Stop Streaming";
            streaming = true;

            CheckReceive();
        }
    }

    public void OnClickSyncBtn()
    {
        if (streaming && !synchronizing)
        {
            syncTime = (float)syncDuration;
            billboardText.GetComponent<Text>().text = "" + syncTime;
            synchronizing = true;
        }

        // 다시 싱크 버튼을 클릭한다면
        if (streaming && synchronized)
        {
            foreach (KeyValuePair<string, Motion> element in comPorts)
               element.Value.reSync();
        }
    }

    public void OnClickSocketBtn()
    {
        if (ipField != null && ipField.text != "")
            serverIP = ipField.text;
        if (portField != null && portField.text != "")
            Port = Int32.Parse(portField.text);
    }

    void CheckReceive()
    {
        if (socketReady) return;
        try
        {
            client = new TcpClient(serverIP, Port);

            if (client.Connected)
            {
                stream = client.GetStream();
                reader = new StreamReader(stream);
                Debug.Log("Connect Success");
                socketReady = true;
                billboardText.GetComponent<Text>().text = "Connect Success";
            }
        }
        catch (Exception e)
        {
            Debug.Log("On client connect exception " + e);
            billboardText.GetComponent<Text>().text = "Connect Fail";
        }
    }

    void CloseSocket()
    {
        if (!socketReady) return;

        reader.Close();
        client.Close();
        socketReady = false;
    }
}
