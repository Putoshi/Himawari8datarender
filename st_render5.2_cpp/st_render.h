#pragma once
#ifndef ST_RENDER_H

#define ST_RENDER_H 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <Windows.h>
#include <UrlMon.h>
#include <netcdf.h>
#include  "lodepng.h"
#include <exception>
#pragma comment(lib,"netcdf.lib")
#pragma comment(lib,"UrlMon.lib")
typedef unsigned char byte;
typedef unsigned int UInt32;
typedef unsigned short UInt16;
#define PI 3.1416

//extern int errno;
struct STdata//unfinished
{
	byte errcode;//0 OK|1 initialize memory allocation fail 
	byte type;//0 unknown|1 himwari standard data|2 goes data|
	byte progress;//0 not processed|1 know filename|2 know type|3 allocated memory for STdata
	void *args;
	void* hpSTdata;
};
struct HSdata
        {
		//public:
			char Satelitename[16];
            UInt32 TotalHLenth;
            UInt16 w;
            UInt16 h;
            UInt16 band;
			UInt16 bitnum;
            double wl;
            double Slope;
            double intc;
            double c0;
            double c1;
            double c2;
            double c;
            double H;
            double k;
            UInt16 len8;
            UInt16 len9;
            UInt32 len10;
            UInt16* data;
            double* temp;
            //byte info;
        };
struct GOESdata
{
	UInt16 
		x,
		y,
		band;

	int 
		fileid,
		bandid,
		k0id,
		plkfk1id,
		plkfk2id,
		plkbc1id,
		plkbc2id,
		varid;

	float 
		s_f,
		add,
		kappa0,
		plank_fk1,//plank(no)planck(yes) =)
		plank_fk2,
		plank_bc1,
		plank_bc2;

	size_t 
		szdata,
		sztemp;

	UInt16 
		*hpdata;

	double 
		*hptemp; 
};

struct InputArgs
{
	char *filename,
		*path,
		*outpic;
	int op,
		color;
};

struct TYinfo
{
	double 
		lat,
		lon,
		dlat,
		dlon,
		latd,
		lond;
	char 
		NS,
		EW;
	char
		*hpMessage,
		*hpdFilename[3],//...
		filecount,
		lats[3],
		lons[4],
		Ys[4],
		Ms[2],
		Ds[2],
		Hs[2],
		Ys2[4],
		Ms2[2],
		Ds2[2],
		Hs2[2];
	byte
		error,//1 filename error;2 memory allocation error;	
		info;//0=ok;1=end
	int
		Y,
		M,
		D,
		H,
		MIN,
		x,
		y;
	FILE*
		f;
};
struct TIME
{
	int Y,M,D,H,MIN;
};
TYinfo newTYinfo(char* filename);
byte TYreadNext(TYinfo* ty);
void TYnextmin(TYinfo* ty);
byte TYdownloadHimawari89(TYinfo* ty,char* band);
int TYrender(TYinfo* ty,int color);
void TYclose(TYinfo* ty);
int ATyphoon();
void hsdRender(const char* file,int color,const char* outputfilename,bool deleteDAT);
HSdata hsdRead(const char* file,bool deleteDAT);
HSdata hsdRead(const char* file,bool deleteDAT,bool doDebug);
double* hsdCalibration(HSdata* dt);
double* hsdCalibration(HSdata* dt,bool dbg);
void goesncRender(const char* file,int color,const char* outputfilename);
int goesncReader(const char*file,GOESdata *dt,bool dbg);
double *goesncCalibration(GOESdata *dt,bool dbg);
byte* BW(UInt16 *data,size_t sdata,UInt16 bit);
byte* TtoBD(double* temp,int length);
byte* TtoColor2(double* temp,int length);
byte* TtoWVNRL(double* temp,int length);
byte BD(double temp);
byte color2b(double temp);
byte color2g(double temp);
byte color2r(double temp);
byte wvnrlb(double temp);
byte wvnrlg(double temp);
byte wvnrlr(double temp);
void depress(const char*file);
bool compare(const char* s1,const char* s2);
void ClearArgs(InputArgs* args);
void SplitArgs(InputArgs* input,int argc,char** argv);
void STdata_initialize(STdata* data);
void addMIN(TIME* t,UInt16 min);//bugs when min is too big 
int ctoi(char* str,int l);
int ctoibit(char c);
int power(int base,int p);
char* itoc(int i);
char itocbit(int i);
void st_render_help();
//void strcopy(char* d,size_t dsize,const char* s,size_t count);
#endif