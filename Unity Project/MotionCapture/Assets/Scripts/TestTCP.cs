using System.Collections;
using System.Collections.Generic;
using System.Net.Sockets;
using UnityEngine;
using System.Text;
using System;
using System.IO;
using System.Runtime.InteropServices;

public class TestTCP : MonoBehaviour
{
    TcpClient client;
    string serverIP = "192.168.0.11";
    int port = 8080;
    byte[] receiveBuffer;
    StreamReader reader;
    bool socketReady = false;
    NetworkStream stream;

    // Start is called before the first frame update
    void Start()
    {
        CheckReceive();
    }

    // Update is called once per frame
    void Update()
    {
        if (socketReady)
        {
            if (stream.DataAvailable)
            {
                receiveBuffer = new byte[500];
                //stream.Read(receiveBuffer, 0, receiveBuffer.Length);
                //stream.ReadLine();
                //string msg = Encoding.UTF8.GetString(receiveBuffer, 0, receiveBuffer.Length);

                string msg = reader.ReadLine();
                Debug.Log(msg);
            }
        }
    }

    void CheckReceive()
    {
        if (socketReady) return;
        try
        {
            client = new TcpClient(serverIP, port);

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
}
