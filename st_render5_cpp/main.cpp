#define WIN32
#include <stdio.h>
#include <stdlib.h>
//#include <errno.h>
#include <Windows.h>
#include "st_render.h"
//extern  int errno;

/*
ATYPHOON and GOESNC under maintenance
*/

LARGE_INTEGER tf,ts,te;
int main(int argc,char **argv)
{
	printf("st_render V5_cpp\n");
	
	QueryPerformanceFrequency(&tf);
	QueryPerformanceCounter(&ts);
	InputArgs args;
	//STdata data;
	//STdata_initialize(&data);
	SplitArgs(&args,argc,argv);
	//printf("%d",args.color);
	//printf(itoc(0));
	switch(args.op)
	{
		case 0:{st_render_help();break;}
		case 1:{/*ATyphoon()*/printf("ATyphoon is under maintenance");break;}
		case 2:{hsdRender(args.filename,args.color,args.outpic,true);break;}
		case 3:{/*goesncRender(args.filename,args.color,args.outpic)*/printf("GOES netcdf render is under maintenance");break;}
	}
	//printf("%x",URLDownloadToFile(0,"https://www.runoob.com/cprogramming/c-file-io.html","c-file-io.html",0,0));
	 	


	/*char* hpc= itoc(1000);
	printf(hpc);
	free(hpc);*/

	//UInt16 a,b,d;//b;
	//byte *c;
	//hsdRender("HS_H08_20160706_0800_B13_R302_R20_S0101.DAT.bz2",1,0,true);
	//goesncRender("OR_ABI-L1b-RadM1-M6C13_G16_s20192441500267_e20192441500336_c20192441500404.nc",1,"t3.png");
	/*const char* file="OR_ABI-L1b-RadM1-M6C01_G16_s20192441500267_e20192441500324_c20192441500383.nc";
	int fileid,xid,yid,dataid;
	UInt16 x,y;
	float t1;
	char* t2;
	UInt16 *pdata;
	int nce;
	size_t st[]={0},ct[]={2};

	//x=(UInt16*)calloc(2,1);
	nce=0;
	nce=nc_open(file,NC_NOWRITE,&fileid);
	printf(nc_strerror(nce));
	nce=nc_inq_varid(fileid,"y",&xid);
	//nce=nc_get_att_text(fileid,xid,"resolution",t2);
	printf(nc_strerror(nce));

	nce=nc_get_var1_short(fileid,xid,st,(short*)&x);
	printf(nc_strerror(nce));
	printf("\n%d\n",x);*/
	//printf(t2);
	//nc_close(fileid);
	QueryPerformanceCounter(&te);
	printf("time:%d ms",((te.QuadPart-ts.QuadPart)*1000/tf.QuadPart));
	system("pause");
	
	return 0;
}