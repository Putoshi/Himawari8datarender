using System;

/// <summary>
/// Class1 的摘要说明
/// </summary>
/// 
namespace st_render5
{
    public partial class strender
    {
        public class ColorScale
        {
            public static byte BD(double temp)
            {
                byte o = 0;
                if (temp > 303.15)
                {
                    o = 0;
                }
                else if (temp > 282.15)
                {
                    o = (byte)((303.15 - temp) * 12);
                }
                else if (temp > 242.15)
                {
                    o = (byte)((282.15 - temp) * 2 + 100);
                }
                else if (temp > 231.15)
                {
                    o = 80;
                }
                else if (temp > 219.15)
                {
                    o = 130;
                }
                else if (temp > 209.15)
                {
                    o = 190;
                }
                else if (temp > 203.15)
                {
                    o = 0;
                }
                else if (temp > 197.15)
                {
                    o = 255;
                }
                else if (temp > 192.15)
                {
                    o = 170;
                }
                else
                {
                    o = 120;
                }
                return o;
            }
            public static byte color2r(double temp)
            {
                byte o = 0;
                if (temp > 303.15)
                {
                    o = 0;
                }
                else if (temp > 243.15)
                {
                    o = (byte)((303.15 - temp) * 4);
                }
                else if (temp > 223.15)
                {
                    o = 50;
                }
                else if (temp > 203.15)
                {
                    o = 0;
                }
                else if (temp > 193.15)
                {
                    o = (byte)((203.15 - temp) * 20 + 50);
                }
                else if (temp > 183.15)
                {
                    o = (byte)((temp - 183.15) * 25);
                }
                else// (temp > 173.15)
                {
                    o = (byte)((temp - 173.15) * 25);
                }
                return o;
            }
            public static byte color2g(double temp)
            {
                byte o = 0;
                if (temp > 303.15)
                {
                    o = 0;
                }
                else if (temp > 243.15)
                {
                    o = (byte)((303.15 - temp) * 4);
                }
                else if (temp > 223.15)
                {
                    o = (byte)((temp - 223.15) * 6 + 120);
                }
                else if (temp > 213.15)
                {
                    o = 0;
                }
                else if (temp > 203.15)
                {
                    o = (byte)((213.15 - temp) * 20 + 50);
                }
                else if (temp > 193.15)
                {
                    o = 0;
                }
                else if (temp > 183.15)
                {
                    o = (byte)((temp - 183.15) * 25);
                }
                else// (temp > 173.15)
                {
                    o = (byte)((temp - 173.15) * 25);
                }
                return o;
            }
            public static byte color2b(double temp)
            {
                byte o = 0;
                if (temp > 303.15)
                {
                    o = 0;
                }
                else if (temp > 243.15)
                {
                    o = (byte)((303.15 - temp) * 4);
                }
                else if (temp > 223.15)
                {
                    o = (byte)((temp - 223.15) * 6 + 120);
                }
                else if (temp > 213.15)
                {
                    o = (byte)((223.15 - temp) * 20 + 50);
                }

                else if (temp > 183.15)
                {
                    o = 0;
                }
                else// (temp > 173.15)
                {
                    o = (byte)((temp - 173.15) * 25);
                }
                return o;
            }
            public static byte wvnrlr(double temp)
            {
                byte o = 128;
                if (temp > 273.15)
                {
                    o = 127;
                }
                else if (temp > 263.15)
                {
                    o = (byte)((temp - 263.15) * 10.8 + 20);
                }
                else if (temp > 253.15)
                {
                    o = (byte)(20 + (263.15 - temp) * 3);
                }
                else if (temp > 243.15)
                {
                    o = (byte)(50 + (253.15 - temp) * 7.8);
                }
                else if (temp > 233.15)
                {
                    o = (byte)((127 + 243.15 - temp) * 12.8);
                }
                else if (temp > 223.15)
                {
                    o = 255;
                }
                else if (temp > 203.15)
                {
                    o = (byte)(127 + (temp - 203.15) * 6.4);
                }
                return o;
            }
            public static byte wvnrlg(double temp)
            {
                byte o = 0;
                if (temp > 273.15)
                {
                    o = 0;
                }
                else if (temp > 263.15)
                {
                    o = (byte)((273.15 - temp) * 10);
                }
                else if (temp > 253.15)
                {
                    o = (byte)(100 + (263.15 - temp) * 5);
                }
                else if (temp > 243.15)
                {
                    o = (byte)(150 + (253.15 - temp) * 10.5);
                }
                else if (temp > 233.15)
                {
                    o = 255;
                }
                else if (temp > 223.15)
                {
                    o = (byte)(180 + (temp - 223.15) * 7.5);
                }
                else if (temp > 203.15)
                {
                    o = (byte)((temp - 203.15) * 9);
                }
                return o;
            }
            public static byte wvnrlb(double temp)
            {
                byte o = 0;
                if (temp > 273.15)
                {
                    o = 140;
                }
                else if (temp > 263.15)
                {
                    o = (byte)(140 + (273.15 - temp) * 9);
                }
                else if (temp > 253.15)
                {
                    o = (byte)(230 + (263.15 - temp) * 2.5);
                }
                else if (temp > 243.15)
                {
                    o = 255;
                }
                else if (temp > 233.15)
                {
                    o = (byte)(127 + (temp - 233.15) * 12.8);
                }
                else if (temp > 223.15)
                {
                    o = (byte)(100 + (temp - 223.15) * 2.8);
                }
                else if (temp > 203.15)
                {
                    o = (byte)((temp - 203.15) * 5);
                }
                return o;
            }
        }
    }
}
