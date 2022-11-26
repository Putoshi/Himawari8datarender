using System;
namespace st_render5
{
    public partial class strender
    {
        public struct HSdata
        {
            public byte[] SatelliteName ;//= new char[16];
            public UInt32 TotalHLenth;
            public byte[] FileName ;//= new char[128];
            public UInt16 w;
            public UInt16 h;
            public UInt16 band;
            public double wl;
            public UInt16 bitnum;
            public double Slope;
            public double intc;
            public double c0;
            public double c1;
            public double c2;
            public double c;
            public double H;
            public double k;
            public UInt16 len8;
            public UInt16 len9;
            public UInt32 len10;
            public UInt16[] data;
            public double[] temp;
            public byte isread;
        }
        public struct GMSdataIR
        {
            public UInt16 ControlBlockSize;
            //...............
        }
    }
    public partial class TYInfo
    {
        //another:ReadandP.cs
        public string Message;
        public string Ocean;
        public string numbers;
        public string lats;
        public string lons;
        public char NS;
        public char EW;

        public string Ys;
        public string Ms;
        public string Ds;
        public string Hs;
        public int Y;
        public int M;
        public int D;
        public int H;
        public int MIN;


        public int number;
        public double lat;
        public double lon;
        public double lato;
        public double lono;
        public double dlat;
        public double dlon;
   
        public int x;
        public int y;

        public string color;
    }
    public class InputArgs
    {
        public string filename;
        public string path;
        public string color;
        public string outputpic;
        public int op;
        public InputArgs()
        {
            filename = null;
            path = null;
            color = null;
            outputpic = null;
            op = 0;
        }
        public static InputArgs SplitInput(string[] input)
        {
            InputArgs arg = new InputArgs();
            int i = 1;
            if (input.Length < 2)
            {
                arg.op = 2;
            }
            else
            {
                while (i < input.Length)
                {

                    if (input[i] == "hsdfile") { arg.op = 1; }
                    if (i < input.Length - 1)
                    {
                        if (input[i] == "path") { i++; arg.path = input[i]; }
                        else if (input[i] == "file") { i++; arg.filename = input[i]; }
                        else if (input[i] == "color") { i++; arg.color = input[i]; }
                        else if (input[i] == "out") { i++; arg.outputpic = input[i]; }
                    }
                    i++;
                }
            }
            return arg;
        }
    }
}