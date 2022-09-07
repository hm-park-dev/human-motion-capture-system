using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Controller : MonoBehaviour
{
    [SerializeField]
    private Move leftUpperArm;

    private Dictionary<string, Move> comPorts;
    public Text streamingBtnText;

    public Text billboardText;

    private bool streaming = false;
    private bool synchronizing = false;
    private float syncTime = 0f;
    [SerializeField] private int syncDuration = 3;

    // Start is called before the first frame update
    void Start()
    {
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

                foreach (KeyValuePair<string, Move> element in comPorts)
                {
                    element.Value.startCalibration(element.Key);
                }
            }
        }
    }

    public void OnClickStreaming()
    {
        if (streaming)
        {
            foreach (KeyValuePair<string, Move> element in comPorts)
                element.Value.sendStopMsg();
            streamingBtnText.GetComponent<Text>().text = "Start Streaming";
            streaming = false;
        }
        else
        {
            foreach (KeyValuePair<string, Move> element in comPorts)
                element.Value.sendStartMsg();
            streamingBtnText.GetComponent<Text>().text = "Stop Streaming";
            streaming = true;
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
}
