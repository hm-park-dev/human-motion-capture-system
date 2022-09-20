using System;
using System.Linq;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;


namespace FusionFx
{
    public class FusionFxFrame
    {
        // Real Time Clock
        public byte hour;
        public byte min;
        public byte sec;
        public byte sub_sec;

        // Acc
        public int acc_x;
        public int acc_y;
        public int acc_z;

        // Gyro
        public int gyro_x;
        public int gyro_y;
        public int gyro_z;

        // Mag
        public int mag_x;
        public int mag_y;
        public int mag_z;

        // Fx Quaternions
        public float quat_w;
        public float quat_x;
        public float quat_y;
        public float quat_z;

        // Fx Rotations
        public float rot_x; // Yaw
        public float rot_y; // Pitch
        public float rot_z; // Roll

        // Fx Gravity
        public float grav_x;
        public float grav_y;
        public float grav_z;

        // Fx linear acceleration
        public float linAcc_x;
        public float linAcc_y;
        public float linAcc_z;

        // Fx Heading
        public float heading;
        public float headingErr;

        // + Motion Sensor ID
        public int sensorID;

        // Fx Elapsed Time (us)
        public int elpased;

        public FusionFxFrame(byte[] frame){
            hour = frame[ffIdx.Hour];
            min = frame[ffIdx.Min];
            sec = frame[ffIdx.Sec];
            sub_sec = frame[ffIdx.Sub_sec];

            //acc
            acc_x = convertByteToInt(frame, ffIdx.Acc_x);
            acc_y = convertByteToInt(frame, ffIdx.Acc_y);
            acc_z = convertByteToInt(frame, ffIdx.Acc_z);

            // gyro
            gyro_x = convertByteToInt(frame, ffIdx.Gyro_x);
            gyro_y = convertByteToInt(frame, ffIdx.Gyro_y);
            gyro_z = convertByteToInt(frame, ffIdx.Gyro_z);

            //mag
            mag_x = convertByteToInt(frame, ffIdx.Mag_x);
            mag_y = convertByteToInt(frame, ffIdx.Mag_y);
            mag_z = convertByteToInt(frame, ffIdx.Mag_z);

            // quat
            quat_w = convertByteToFloat(frame, ffIdx.Quat_w);
            quat_x = convertByteToFloat(frame, ffIdx.Quat_x);
            quat_y = convertByteToFloat(frame, ffIdx.Quat_y);
            quat_z = convertByteToFloat(frame, ffIdx.Quat_z);

            //rot
            rot_x = convertByteToFloat(frame, ffIdx.Rot_x);
            rot_y = convertByteToFloat(frame, ffIdx.Rot_y);
            rot_z = convertByteToFloat(frame, ffIdx.Rot_z);

            //gravity
            grav_x = convertByteToFloat(frame, ffIdx.Grav_x);
            grav_y = convertByteToFloat(frame, ffIdx.Grav_y);
            grav_z = convertByteToFloat(frame, ffIdx.Grav_z);

            //linAcc
            linAcc_x = convertByteToFloat(frame, ffIdx.LinAcc_x);
            linAcc_y = convertByteToFloat(frame, ffIdx.LinAcc_y);
            linAcc_z = convertByteToFloat(frame, ffIdx.LinAcc_z);

            //heading
            heading = convertByteToFloat(frame, ffIdx.Heading);
            headingErr = convertByteToFloat(frame, ffIdx.HeadingErr);

            //sensor
            sensorID = convertByteToInt(frame, ffIdx.SensorID);

            elpased = convertByteToInt(frame, ffIdx.Elapsed);
        }

        private int convertByteToInt(byte[] frame, int offset){
            //convert32Endian(frame, offset);
            return BitConverter.ToInt32(frame, offset);
        }

        private float convertByteToFloat(byte[] frame, int offset){
            //convert32Endian(frame, offset);
            return (float)BitConverter.ToSingle(frame, offset);
        }

        private void convert32Endian(byte[] frame, int offset)
        {
            byte upper = frame[offset];
            byte lower = frame[offset+1];
            frame[offset] = frame[offset+3];
            frame[offset+1] = frame[offset+2];
            frame[offset+2] = lower;
            frame[offset+3] = upper;
        }
    }

    

    public static class ffIdx
    {
        public const int Hour        = 3;
        public const int Min         = 4;
        public const int Sec         = 5;
        public const int Sub_sec     = 6;

        public const int Acc_x       = 19;
        public const int Acc_y       = 23;
        public const int Acc_z       = 27;

        public const int Gyro_x      = 31;
        public const int Gyro_y      = 35;
        public const int Gyro_z      = 39;

        public const int Mag_x       = 43;
        public const int Mag_y       = 47;
        public const int Mag_z       = 51;

        public const int Quat_w      = 55;
        public const int Quat_x      = 59;
        public const int Quat_y      = 63;
        public const int Quat_z      = 67;

        public const int Rot_x       = 71;
        public const int Rot_y       = 75;
        public const int Rot_z       = 79;

        public const int Grav_x      = 83;
        public const int Grav_y      = 87;
        public const int Grav_z      = 91;

        public const int LinAcc_x    = 95;
        public const int LinAcc_y    = 99;
        public const int LinAcc_z    = 103;

        public const int Heading     = 107;
        public const int HeadingErr  = 111;

        public const int SensorID = 115;

        public const int Elapsed = 119;
    }
}

