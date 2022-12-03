using System;

/// <summary>
/// Class1 的摘要说明
/// </summary>
/// 
namespace st_render5
{
    public partial class strender
    {
        public static void RenderHSD(string path, string file, string color, string outpic)
        {
            Console.WriteLine("RenderHSD");
            if (outpic == null) { outpic = file + ".png"; }
            HSdata dt = ReadHSDFile(path, file);
            double[] t = Calibration(dt.data, dt.wl, dt.c, dt.H, dt.k, dt.Slope, dt.intc);
            byte[] pixel = null;
            byte type = 0;
            if (color == "BD") { pixel = TtoBD(t); type = 1; }
            else if (color == "2") { pixel = TtoColor2(t); type = 2; }
            else if (color == "WVNRL") { pixel = TtoWVNRL(t); type = 2; }
            
            if (type == 1) { SaveasPNGBW(pixel, dt.w, dt.h, path, outpic); }
            else if (type == 2) { SaveasPNGRGB(pixel, dt.w, dt.h, path, outpic); }
        }
        public static void RenderHSD(string path, string file, string color,string outpath, string outpic,int x1,int y1,int x2,int y2,bool deleteDAT)
        {
            Console.WriteLine("RenderHSD");
            Console.WriteLine("(" + x1 + "," + y1 + ")");
            Console.WriteLine("(" + x2 + "," + y2 + ")");
            int w = (x2 - x1 + 1);
            int h=(y2 - y1 + 1);
            UInt16[] dat = new UInt16[ w* h];
            if (outpic == null) { outpic = file + ".png"; }
            Console.WriteLine("Reading");
            HSdata dt = ReadHSDFile(path, file,deleteDAT);
            Console.WriteLine("convert");
            for (int i = 0; i < h; i++)
            {
                for (int j = 0; j < w; j++)
                {
                    dat[i * w + j] = dt.data[(i + y1) * dt.w + x1 + j];
                }
            }
            Console.WriteLine("Calibrate");
            double[] t = Calibration(dat, dt.wl, dt.c, dt.H, dt.k, dt.Slope, dt.intc);
            byte[] pixel = null;
            byte type = 0;
            Console.WriteLine("Color");
            if (color == "BD") { pixel = TtoBD(t); type = 1; }
            else if (color == "2") { pixel = TtoColor2(t); type = 2; }
            else if (color == "WVNRL") { pixel = TtoWVNRL(t); type = 2; }
            Console.WriteLine("Save pic");
            if (type == 1) { SaveasPNGBW(pixel, w, h, outpath, outpic); }
            else if (type == 2) { SaveasPNGRGB(pixel, w, h, outpath, outpic); }
            
        }
    }

}
