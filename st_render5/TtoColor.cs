using System;

/// <summary>
/// Class1 的摘要说明
/// </summary>
/// 
namespace st_render5
{
    public partial class strender
    {
        public static byte[] TtoBD(double[] temp)
        {
            byte[] o = new byte[temp.Length];
            for (int i = 0; i < temp.Length; i++)
            {
                o[i] = ColorScale.BD(temp[i]);
            }
            return o;
        }
        public static byte[] TtoColor2(double[] temp)
        {
            byte[] o = new byte[temp.Length * 3];
            for (int i = 0; i < temp.Length; i++)
            {
                o[i * 3] = ColorScale.color2b(temp[i]);
                o[i * 3 + 1] = ColorScale.color2g(temp[i]);
                o[i * 3 + 2] = ColorScale.color2r(temp[i]);
            }
            return o;
        }
        public static byte[] TtoWVNRL(double[] temp)
        {
            byte[] o = new byte[temp.Length*3];
            for (int i = 0; i < temp.Length; i++)
            {
                o[i*3] = ColorScale.wvnrlb(temp[i]);
                o[i*3+1] = ColorScale.wvnrlg(temp[i]);
                o[i*3+2] = ColorScale.wvnrlr(temp[i]);
            }
            return o;
        }
    }
}