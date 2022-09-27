using System;
using System.Runtime.InteropServices;
using System.Threading;

namespace TestGeekTrack
{
    class Program
    {
        public struct GeekEulerAngles
        {
            public float x, y, z;
        };

        public struct GeekQuaternion
        {
            public float w, x, y, z;
        };

        [DllImport("GeekTrackSDK.dll", EntryPoint = "GeekTrack_Init", CallingConvention = CallingConvention.Cdecl)]
        public extern static void GeekTrack_Init();

        [DllImport("GeekTrackSDK.dll", EntryPoint = "GetEulerAngles", CallingConvention = CallingConvention.Cdecl)]
        public extern static GeekEulerAngles GetEulerAngles(int devId);

        [DllImport("GeekTrackSDK.dll", EntryPoint = "GetQuaternion", CallingConvention = CallingConvention.Cdecl)]
        public extern static GeekQuaternion GetQuaternion(int devId);

        static void Main(string[] args)
        {
            GeekTrack_Init();
            while (true) {
                GeekEulerAngles angles = GetEulerAngles(0);
                GeekQuaternion quat = GetQuaternion(0);
                Thread.Sleep(30);
                //Debug.Log("<color=#9400D3>" + + "</color>");
                Console.WriteLine(quat.w + "," + quat.x + "," + quat.y + "," + quat.z);
            }
            
        }
    }
}
