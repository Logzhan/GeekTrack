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

        [DllImport("GeekTrackSDK.dll", EntryPoint = "GeekTrack_Init", CallingConvention = CallingConvention.Cdecl)]
        public extern static void GeekTrack_Init();

        [DllImport("GeekTrackSDK.dll", EntryPoint = "GetEulerAngles", CallingConvention = CallingConvention.Cdecl)]
        public extern static GeekEulerAngles GetEulerAngles();

        static void Main(string[] args)
        {
            GeekTrack_Init();
            while (true) {
                GeekEulerAngles angles =  GetEulerAngles();
                Thread.Sleep(100);
                //Debug.Log("<color=#9400D3>" + + "</color>");
                Console.WriteLine(angles.x + "," + angles.y + "," + angles.z);
            }
            
        }
    }
}
