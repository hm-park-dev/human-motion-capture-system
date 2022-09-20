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
    [SerializeField]
    private Move leftUpperArm;

    [Header("Socket Conf")]
    [SerializeField] private string serverIP = "192.168.0.11";
    [SerializeField] private int Port = 8080;

    TcpClient client;
    byte[] receiveBuffer;
    StreamReader reader;
    bool socketReady = false;
    NetworkStream stream;

    private Dictionary<string, Move> comPorts;

    [Header("Button Conf")]
    [SerializeField] private Button streamingButton;
    [SerializeField] private Button syncButton;
    [SerializeField] private Text streamingBtnText;
    [SerializeField] private Text billboardText;

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
        streamingButton.onClick.AddListener(OnClickStreaming);
        syncButton.onClick.AddListener(OnClickSyncBtn);

        comPorts = new Dictionary<string, Move>();
        if (leftUpperArm != null) comPorts.Add("leftUpperArm", leftUpperArm);

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
                synchronized = true;

                if (socketReady)
                {
                    if (stream.DataAvailable)
                    {
                        receiveBuffer = new byte[500];
                        string msg = reader.ReadLine();
                        //Debug.Log(msg);

                        string[] split_msg = msg.Split(',');

                        if (split_msg.Length == 10)
                        {
                            i = float.Parse(split_msg[3]);
                            j = float.Parse(split_msg[5]);
                            k = float.Parse(split_msg[7]);
                            w = float.Parse(split_msg[9]);
                            switch (split_msg[0])
                            {
                                case "P2PSRV2":
                                    leftUpperArm.sendQuaternion(i, j, k, w);
                                    break;
                                default:
                                    break;
                            }

                        }

                    }
                    foreach (KeyValuePair<string, Move> element in comPorts)
                    {
                        element.Value.startCalibration(element.Key);
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

                    if (split_msg.Length == 10)
                    {
                        i = float.Parse(split_msg[3]);
                        j = float.Parse(split_msg[5]);
                        k = float.Parse(split_msg[7]);
                        w = float.Parse(split_msg[9]);

                        switch (split_msg[0])
                        {
                            case "P2PSRV2":
                                leftUpperArm.sendQuaternion(i, j, k, w);
                                break;
                            default:
                                break;
                        }
                        
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
            }
        }
        catch (Exception e)
        {
            Debug.Log("On client connect exception " + e);
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
