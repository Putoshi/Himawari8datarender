#include "st_render.h"

byte *BW(UInt16 *data,size_t sdata,UInt16 bit)
{
	byte *o=(byte*)calloc(sdata*3,2);
	byte t;
	if(bit>8){bit=bit-8;}
	for(int i=0;i<sdata;i++)
	{
		t=data[i]>>bit;
		o[i*3] = t;
		o[i*3+1] = t;
		o[i*3+2] = t;
	}
	return o;
}

 byte* TtoBD(double* temp,int length)
        {
            byte *o = (byte*)calloc(length*3,sizeof(byte));
            for (int i = 0; i < length; i++)
            {
                o[i*3] = BD(temp[i]);
				o[i*3+1] = BD(temp[i]);
				o[i*3+2] = BD(temp[i]);
            }
            return o;
        }
         byte* TtoColor2(double* temp,int length)
        {
            byte* o = (byte *)calloc(length * 3,sizeof(byte));
            for (int i = 0; i < length; i++)
            {
                o[i * 3] = color2r(temp[i]);
                o[i * 3 + 1] = color2g(temp[i]);
                o[i * 3 + 2] = color2b(temp[i]);
            }
            return o;
        }
        byte* TtoWVNRL(double* temp,int length)
        {
            byte* o = (byte*)calloc(length*3,sizeof(byte));
            for (int i = 0; i < length; i++)
            {
                o[i*3] = wvnrlr(temp[i]);
                o[i*3+1] = wvnrlg(temp[i]);
                o[i*3+2] = wvnrlb(temp[i]);
            }
            return o;
        }

byte BD(double temp)
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
             byte color2r(double temp)
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
                    o = (byte)((203.15 - temp) * 15 + 100);
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
             byte color2g(double temp)
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
                    o = (byte)((213.15 - temp) * 15 + 100);
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
            byte color2b(double temp)
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
                    o = (byte)((223.15 - temp) * 15 + 100);
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
             byte wvnrlr(double temp)
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
            byte wvnrlg(double temp)
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
             byte wvnrlb(double temp)
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