using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TestRigBones : MonoBehaviour
{
    public GameObject humanoid;
    private float x, y, z;

    public GameObject rightLowerArm;
    public GameObject rightUpperArm;

    // Start is called before the first frame update
    void Start()
    {
        x = 0;
        y = 0;
        z = 0;
    }

    // Update is called once per frame
    void Update()
    {
        if (Input.GetKeyDown(KeyCode.W))
            y += 10;
        if (Input.GetKeyDown(KeyCode.A))
            x += 10;
        if (Input.GetKeyDown(KeyCode.S))
            y -= 10;
        if (Input.GetKeyDown(KeyCode.D))
            x -= 10;

        Quaternion q = Quaternion.Euler(x, y, z);
        rightLowerArm.transform.localRotation = q;
    }
}
