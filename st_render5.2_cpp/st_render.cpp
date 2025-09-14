/*
2023 @linsanyi031 
st_render{
st_render.h,
colorscale.cpp,
others.cpp,
st_render.cpp(this file)
}
hsdrender() for HSD file;
goesncrender() for GOES16-19 netcdf file;
ATyphoon() for rendering images of a typhoon
*/


#include <math.h>
#include "st_render.h"
//#include <netcdf.h>
//#pragma comment(lib,"netcdf.lib")
 inline HSdata hsdRead(const char* file,bool deleteDAT)
{
	HSdata dt=hsdRead(file,deleteDAT,false);
	return dt;
}
HSdata hsdRead(const char* file,bool deleteDAT,bool doDebug)//e:file HS_H08_20180927_1200_B13_FLDK_R20_S0101.DAT.bz2
{
	//if(dbg){ printf("debughsdReadx\n"); }
	bool dbg=doDebug;
	if(dbg){printf("debughsdRead1\n");}
	char *DAT;
	FILE *fp;
	HSdata dt;
	size_t DATl;
	size_t t;
	//if(GetFileAttributes(file)==INVALID_FILE_ATTRIBUTES){dt.info=1;return dt;}
	
	DATl=strlen(file)-4;
	DAT=(char*)calloc(DATl+1,1);
	if(dbg){printf("%d\n",strlen(file)-4);printf("%d\n",DATl);}
	//strncpy_s(DAT,strlen(file)-4,file,strlen(file)-4);
	strncpy_s(DAT,DATl+1,file,DATl);
	//strcpy(DAT+DATl,0);
	if(dbg){printf("%d\n",strlen(file));printf("%d\n",strlen(DAT));}
	if(dbg){ printf("debughsdRead2\n");printf(file);printf("\n DAT");printf(DAT);printf(" end\n"); }
	//fp=fopen(DAT,"rb+");
	if(GetFileAttributes(DAT)==INVALID_FILE_ATTRIBUTES)
	{
		depress(file);
	}
	fp=fopen(DAT,"rb+");
	if(dbg){ printf("debughsdRead3\nfp%p\n",fp); }
	fseek(fp,6,SEEK_CUR);
	fread(&dt.Satelitename,1,16,fp);
	fseek(fp,260,SEEK_CUR);
	if(dbg){ printf("debughsdRead4\n"); }
	{fread(&t,1,1,fp);
	if(dbg){printf("%d\n",t);}}
	fseek(fp,4,SEEK_CUR);
	if(dbg){ printf("debughsdRead5\n"); }
	fread_s(&dt.w,sizeof(dt.w),sizeof(dt.w),1,fp);
	fread_s(&dt.h,sizeof(dt.h),sizeof(dt.h),1,fp);
	if(dbg){ printf("debughsdRead6\n%d\n%d\n",dt.w,dt.h); }
	//fread(NULL,1,41,fp);
	fseek(fp,41,SEEK_CUR);
	//fread(NULL,1,268,fp);
	fseek(fp,269,SEEK_CUR);
	fread(&dt.band,sizeof(dt.band),1,fp);
	fread(&dt.wl,8,1,fp);
	if(dbg){printf("%f\n",dt.wl);}
	fread(&dt.bitnum,sizeof(dt.bitnum),1,fp);
	if(dbg){printf("bits%d\n",dt.bitnum);}
	//fread(NULL,1,4,fp);
	fseek(fp,4,SEEK_CUR);
	fread(&dt.Slope,sizeof(dt.Slope),1,fp);
	fread(&dt.intc,sizeof(dt.intc),1,fp);
	if (dt.band > 6)
                {
					fread(&dt.c0,sizeof(dt.c0),1,fp);
                    fread(&dt.c1,sizeof(dt.c1),1,fp);
                    fread(&dt.c2,sizeof(dt.c2),1,fp);
                    //fread(NULL,1,24,fp);
					fseek(fp,24,SEEK_CUR);
                    fread(&dt.c,sizeof(dt.c),1,fp);
                    fread(&dt.H,sizeof(dt.H),1,fp);
                    fread(&dt.k,sizeof(dt.k),1,fp);
                    //fread(NULL,1,40,fp);
					fseek(fp,40,SEEK_CUR);
                }
                else
                {
                    //fread(NULL,1,112,fp);
					fseek(fp,112,SEEK_CUR);
                }
	//fread(NULL,1,47+258+1,fp);
	//fread(NULL,1,1,fp);
	fseek(fp,1+47+258+1,SEEK_CUR);
	fread(&dt.len8,sizeof(dt.len8),1,fp);
    //printf("%d",dt.len8);
    //fread(NULL,dt.len8 - 2,1,fp);
	fseek(fp,dt.len8 - 2,SEEK_CUR);
	fread(&dt.len9,sizeof(dt.len9),1,fp);
	//fread(NULL,1,dt.len9-2,fp);
	fseek(fp,dt.len9-2,SEEK_CUR);
	fread(&dt.len10,sizeof(dt.len10),1,fp);
    //for (UInt32 i = 0; i < dt.len10; i++)
    {
		fseek(fp,dt.len10,SEEK_CUR);
    }
    fseek(fp,254,SEEK_CUR);
	int n=dt.w*dt.h;
	dt.data=(UInt16*)malloc(sizeof(UInt16)*n);
	if(dbg){printf("data%d\n",dt.data);}

	fread(dt.data,2,n,fp);//read image data

	if(dbg){printf("data[0]%d\n",*dt.data);}

	free(DAT);
	fclose(fp);
;
	return dt;
}
double* hsdCalibration(HSdata* dt)
{
	return hsdCalibration(dt,false);
}

double* hsdCalibration(HSdata*dt,bool dbg)//if(dbg){printf("hsdClbrtx");}
{
	double wl,wl5,hcIkwl,h2cc,slope,intc,h2ccIwl5,t2;
	UInt16 x,y;
	size_t xy,i;
	double* temp;
	int table1[65536]={0};
	double table2[65536];

	//if(dbg){printf("hsdClbrt1");}
	wl=dt->wl;
	wl=wl*1e-6;
	wl5=wl*wl*wl*wl*wl;
	hcIkwl=((dt->H)*(dt->c))/((dt->k)*(wl));
	h2cc=2*dt->H*dt->c*dt->c;
	h2ccIwl5=h2cc/wl5;
	h2ccIwl5*=1e-6;
	slope=dt->Slope;
	intc=dt->intc;

	if(dbg){printf("hsdClbrt2\n");}
	i=0;
	x=(dt->w);
	y=(dt->h);
	xy=x*y;
	if(dbg){printf("xy%d\n",xy);}
	if(dbg){printf("xy%d\n",*dt->data);}
	dt->temp=(double*)calloc(xy,sizeof(double));
	
	if(dbg){printf("hsdClbrt3\n");}
	while(i<xy)
	{
		if(table1[dt->data[i]]==0)
		{
			t2=slope*dt->data[i]+intc;
			//t2*=1e6;
			table2[dt->data[i]]=hcIkwl/(log((h2ccIwl5/(t2))+1));
			dt->temp[i]=table2[dt->data[i]];
			table1[dt->data[i]]=1;
			//printf("%f\n",dt->temp[i]);
		}
		else
		{
			dt->temp[i]=table2[dt->data[i]];
		}
		i++;
	}
	if(dbg){printf("hsdClbrt4\n");}
	return dt->temp;
}
void hsdRender(const char* file,int color,const char* outputfilename,bool deleteDAT)
{
	char* outpic;
	size_t _outpic;
	byte* pixels;
	if(outputfilename==NULL)
	{
		_outpic=strlen(file)+5;
		outpic=(char*)malloc(_outpic);
		strcpy_s(outpic,_outpic,file);
		strcat_s(outpic,_outpic,".png");
	}
	else
	{
		outpic=(char*)outputfilename;
	}
	HSdata dt=hsdRead(file,deleteDAT,true);
	if(dt.band>3)
	{
	hsdCalibration(&dt,true);
	printf("hsdRenderdbg1\n");
    switch(color)
	{
	case 1:{pixels=TtoBD(dt.temp,dt.w*dt.h);break;}
	case 2:{pixels=TtoColor2(dt.temp,dt.w*dt.h);break;}
	case 3:{pixels=TtoWVNRL(dt.temp,dt.w*dt.h);break;}
	default:{pixels=BW(dt.data,dt.w*dt.h,dt.bitnum);}
	}
	}
	else{
		pixels=BW(dt.data,dt.w*dt.h,dt.bitnum);
	}
	printf("hsdRenderdbg2\n%s\n",outpic);
	lodepng_encode24_file(outpic,pixels,dt.w,dt.h);
	printf("hsdRenderdbg3\n");
	free(dt.data);
	//free(outpic);
	free(dt.temp);
	free(pixels);
}

int goesncReader(const char*file,GOESdata *dt,bool dbg)
{
	int nce,attid;
	size_t s1;
	nce=0;
	nce=nc_open(file,NC_NOWRITE,&dt->fileid);
	printf(nc_strerror(nce));
	nce=nc_inq_varid(dt->fileid,"x",&dt->varid);
	printf(nc_strerror(nce));

	s1=0;
	while(nce==0)
	{
		nce=nc_get_var1_ushort(dt->fileid,dt->varid,&s1,&dt->x);
		s1++;
	}
	s1-=2;
	nce=nc_get_var1_ushort(dt->fileid,dt->varid,&s1,&dt->x);
	printf("\ns1%d\n",s1);
	dt->x+=1;
	printf(nc_strerror(nce));

	nce=nc_inq_varid(dt->fileid,"y",&dt->varid);
	printf(nc_strerror(nce));
	
	s1=0;
	while(nce==0)
	{
		nce=nc_get_var1_ushort(dt->fileid,dt->varid,&s1,&dt->y);
		s1++;
	}
	s1-=2;
	printf("\ns1%d\n",s1);
	nce=nc_get_var1_ushort(dt->fileid,dt->varid,&s1,&dt->y);
	dt->y+=1;
	printf(nc_strerror(nce));
	
	if(dbg){printf("\nx%d\n",dt->x);
	printf("\ny%d\n",dt->y);}

	dt->szdata=(dt->x)*(dt->y);
	dt->hpdata=(UInt16*)malloc(dt->szdata*2);
	nc_inq_varid(dt->fileid,"Rad",&dt->varid);
	nc_get_var_ushort(dt->fileid,dt->varid,dt->hpdata);
	//nc_inq_attid(dt->fileid,dt->varid,"scale_factor",&attid);
	nc_get_att_float(dt->fileid,dt->varid,"scale_factor",&dt->s_f);
	nc_get_att_float(dt->fileid,dt->varid,"add_offset",&dt->add);

	if(dbg){printf("1\n");}
	nce=nc_inq_varid(dt->fileid,"planck_fk1",&dt->varid);
	printf(nc_strerror(nce));
	nce=nc_get_var_float(dt->fileid,dt->varid,&dt->plank_fk1);
	printf(nc_strerror(nce));
	if(dbg){printf("2\n");}
	nce=nc_inq_varid(dt->fileid,"planck_fk2",&dt->varid);
	printf(nc_strerror(nce));
	nce=nc_get_var_float(dt->fileid,dt->varid,&dt->plank_fk2);
	printf(nc_strerror(nce));
	if(dbg){printf("3\n");}
	nce=nc_inq_varid(dt->fileid,"planck_bc1",&dt->varid);
	printf(nc_strerror(nce));
	nce=nc_get_var_float(dt->fileid,dt->varid,&dt->plank_bc1);
	printf(nc_strerror(nce));
	if(dbg){printf("4\n");}
	nce=nc_inq_varid(dt->fileid,"planck_bc2",&dt->varid);
	printf(nc_strerror(nce));
	nce=nc_get_var_float(dt->fileid,dt->varid,&dt->plank_bc2);
	printf(nc_strerror(nce));
	if(dbg){printf("5\n");}
	if(dbg){printf("%f\n%f\n",dt->plank_fk1,dt->plank_fk2);}
	//printf("\nband%d\n",band);
	nc_close(dt->fileid);
	return 0;
}

double *goesncCalibration(GOESdata *dt,bool dbg)
{
	float t1;
	dt->hptemp=(double*)malloc(dt->szdata*sizeof(double));
	for(size_t i=0;i<dt->szdata;i++)
	{
		t1=dt->hpdata[i]*dt->s_f+dt->add;
		dt->hptemp[i]=(dt->plank_fk2/(log((dt->plank_fk1/t1)+1)));//-dt->plank_bc1)/dt->plank_bc2;
	}
	return dt->hptemp;
}

void goesncRender(const char* file,int color,const char* outputfilename)
{
	GOESdata dt;
	byte *hppix;
	char* outfile;
	outfile=(char*)malloc(strlen(file)+4+1);

	goesncReader(file,&dt,true);
	goesncCalibration(&dt,true);
	printf("%f\n%d\n%f\n",dt.plank_fk1,*dt.hpdata,*dt.hptemp);

	switch(color)
	{
	case 1:{hppix=TtoBD(dt.hptemp,dt.szdata);break;}
	case 2:{hppix=TtoColor2(dt.hptemp,dt.szdata);break;}
	case 3:{hppix=TtoWVNRL(dt.hptemp,dt.szdata);break;}
	default:{hppix=BW(dt.hpdata,dt.x*dt.y,14);break;}
	}

	if(outputfilename==NULL)
	{	
		strcpy(outfile,file);
		strcat(outfile,".png");
		lodepng_encode24_file(outfile,hppix,dt.x,dt.y);
	}
	else
	{
		lodepng_encode24_file(outfile,hppix,dt.x,dt.y);
	}
	free(outfile);
	free(hppix);
	free(dt.hpdata);
	free(dt.hptemp);
}
TYinfo newTYinfo(char* filename)
{
	TYinfo ty;
	ty.info=0;
	FILE *f;
	char* hpMes;
	void* pResult;

	f=fopen(filename,"r+");
	if(f==NULL){printf("error maybe file name is wrong\n");ty.error=1;return ty;}
	ty.f=f;
	
	hpMes=(char*)calloc(257,1);
	if(hpMes==NULL){printf("error memory allocation \n");ty.error=2;return ty;}
	ty.hpMessage=hpMes;
	
	pResult=(char*)calloc(257,1);
	if(pResult==NULL){printf("error memory allocation \n");ty.error=2;return ty;}
	ty.hpdFilename[0]=(char*)pResult;
	pResult=(char*)calloc(257,1);
	if(pResult==NULL){printf("error memory allocation \n");ty.error=2;return ty;}
	ty.hpdFilename[1]=(char*)pResult;
	pResult=(char*)calloc(257,1);
	if(pResult==NULL){printf("error memory allocation \n");ty.error=2;return ty;}
	ty.hpdFilename[2]=(char*)pResult;

	pResult=fgets(ty.hpMessage,256,f);
	while((ty.hpMessage[0]==' ')&&(pResult!=NULL))
	{
		pResult=fgets(ty.hpMessage,256,f);
	}
	if(pResult==NULL)
	{
		free(hpMes);
		return ty;
	}

	for (int p = 0; p < 4; p++)
	{
		ty.Ys[p] = ty.hpMessage[p + 8];
	}
    for (int p = 0; p < 2; p++)
    {
        ty.Ms[p] = ty.hpMessage[p + 12];
    }
    for (int p = 0; p < 2; p++)
    {
		ty.Ds[p] = ty.hpMessage[p + 14];
	}
    for (int p = 0; p < 2; p++)
	{
        ty.Hs[p] = ty.hpMessage[p + 16];
	}
    for (int p = 0; p < 3; p++)
	{
        ty.lats[p] = ty.hpMessage[p + 35];
    }
    ty.NS = ty.hpMessage[38];
    for (int p = 0; p < 4; p++)
	{
        ty.lons[p] = ty.hpMessage[p + 41];
    }
    ty.EW = ty.hpMessage[45];

	ty.latd=ctoi(ty.lats,3)/10;
	ty.lond=ctoi(ty.lons,4)/10;
	TYreadNext(&ty);
	return ty;
}
byte TYreadNext(TYinfo* ty)
{
	void* pResult;

	ty->lat=ty->latd;
	ty->lon=ty->lond;
	ty->Y=ctoi(ty->Ys,4);
	ty->M=ctoi(ty->Ms,2);
	ty->D=ctoi(ty->Ds,2);
	ty->H=ctoi(ty->Hs,2);
	ty->MIN=0;

	pResult=fgets(ty->hpMessage,256,ty->f);
	while((ty->hpMessage[0]==' ')&&(pResult!=NULL))
	{
		pResult=fgets(ty->hpMessage,256,ty->f);
	}
	if(pResult==NULL)
	{
		ty->info=1;
		return 1;
	}
	
	for (int p = 0; p < 4; p++)
	{
		ty->Ys[p] = ty->hpMessage[p + 8];
	}
    for (int p = 0; p < 2; p++)
    {
        ty->Ms[p] = ty->hpMessage[p + 12];
    }
    for (int p = 0; p < 2; p++)
    {
		ty->Ds[p] = ty->hpMessage[p + 14];
	}
    for (int p = 0; p < 2; p++)
	{
        ty->Hs[p] = ty->hpMessage[p + 16];
	}
    for (int p = 0; p < 3; p++)
	{
        ty->lats[p] = ty->hpMessage[p + 35];
    }
    ty->NS = ty->hpMessage[38];
    for (int p = 0; p < 4; p++)
	{
        ty->lons[p] = ty->hpMessage[p + 41];
    }
    ty->EW = ty->hpMessage[45];

	ty->latd=ctoi(ty->lats,3)/10;
	ty->lond=ctoi(ty->lons,4)/10;
	ty->dlat=(ty->latd-ty->lat)/360;
	ty->dlon=(ty->lond-ty->lon)/360;

	return 0;
}
void TYnextmin(TYinfo* ty)
{
	ty->lat+=ty->dlat;
	ty->lon+=ty->dlon;
	ty->MIN++;
	if(ty->MIN>=60)
	{
		ty->MIN=0;
		ty->H++;
	}
	if(ty->H>=24)
	{
		ty->H=0;
		ty->D++;
	}
	if(ty->M==2)
	{
		if(ty->D>28)//a bug here
		{
			ty->D-=28;
			ty->M++;
		}
	}
	else if(ty->M==4|ty->M==6|ty->M==9|ty->M==11)
	{
		if(ty->D>30)
		{
			ty->D-=30;
			ty->M++;
		}
	}
	else
	{
		if(ty->D>31)
		{
			ty->D-=31;
			ty->M++;
		}
	}
	if(ty->M>12)
	{
		ty->M=1;
		ty->Y++;
	}
}
byte TYdownloadHimawari89(TYinfo* ty,char* band)
{
	printf("474\n");
	if(ty->Y<2020)
	{
		char url[512]="https://noaa-himawari8.s3.amazonaws.com/AHI-L1b-FLDK/";//2023/05/03/0000/HS_H09_20230503_0000_B01_FLDK_R10_S0110.DAT.bz2"
		ty->x=(int)(5500+5500*sin((PI/180)*(ty->lon-140.7))*cos((PI/180)*ty->lat)/2);
		ty->y=(int)(2750-2750*sin(PI*ty->lat/180));
		
		printf("478\n");
		ty->filecount=1;
		strcat(url,itoc(ty->Y));
		strcat(url,"/");
		if(ty->M<10)
		{
			strcat(url,"0");
		}
		strcat(url,itoc(ty->M));
		strcat(url,"/");
		if(ty->D<10)
		{
			strcat(url,"0");
		}
		strcat(url,itoc(ty->D));
		strcat(url,"/");
		if(ty->H<10)
		{
			strcat(url,"0");
		}
		strcat(url,itoc(ty->H));
		url[strlen(url)] = '\0'; // 文字列の終端を明示的に設定
		if(ty->MIN<10)
		{
			strcat(url,"0");
		}
		strcat(url,itoc(ty->MIN));
		//----path over-----
		printf("505\n");
		strcat(url,"/HS_H08_");
		strcpy(ty->hpdFilename[0],"HS_H08_");
		strcat(url,itoc(ty->Y));
		strcat(ty->hpdFilename[0],itoc(ty->Y));
		if(ty->M<10)
		{
			strcat(url,"0");
			strcat(ty->hpdFilename[0],"0");
		}
		strcat(url,itoc(ty->M));
		strcat(ty->hpdFilename[0],itoc(ty->M));
		printf("518\n");
		if(ty->D<10)
		{
			strcat(url,"0");
			strcat(ty->hpdFilename[0],"0");
		}
		strcat(url,itoc(ty->D));
		strcat(url,"_");
		strcat(ty->hpdFilename[0],itoc(ty->D));
		strcat(ty->hpdFilename[0],"_");
		printf("528\n");
		if(ty->H<10)
		{
			strcat(url,"0");
			strcat(ty->hpdFilename[0],"0");
		}
		strcat(url,itoc(ty->H));
		strcat(ty->hpdFilename[0],itoc(ty->H));
		if(ty->MIN<10)
		{
			strcat(url,"0");
			strcat(ty->hpdFilename[0],"0");
		}
		strcat(url,itoc(ty->MIN));
		strcat(url,"_B");
		strcat(url,band);
		strcat(url,"_FLDK_R20_S0101.DAT.bz2");
		printf("\n");
		printf(url);
		printf("\n");
		strcat(ty->hpdFilename[0],itoc(ty->MIN));
		strcat(ty->hpdFilename[0],"_B");
		strcat(ty->hpdFilename[0],band);
		strcat(ty->hpdFilename[0],"_FLDK_R20_S0101.DAT.bz2");
		printf("\n");
		printf(ty->hpdFilename[0]);
		printf("\n");
		if(GetFileAttributes(ty->hpdFilename[0])==INVALID_FILE_ATTRIBUTES)
		{
			printf("downloading\n");
			int rt;
			//printf("downloading2\n");
			rt=URLDownloadToFileA(NULL,url,ty->hpdFilename[0],0,NULL);
			//printf("downloading3\n");
			printf(itoc(rt));
			//printf("downloading4\n");
		}
		
	}
	else
	{
		printf("560\n");
		int st,ed,x,y;
		char url[72];
		x=(int)(2750+2750*sin((PI/180)*(ty->lon-140.7))*cos((PI/180)*ty->lat));
		y=(int)(2750-2750*sin(PI*ty->lat/180));
		st=(int)((y-499)/550)+1;
		ed=(int)((y+500)/550)+1;
		printf("x:%d\ny:%d\nst:%d\ned:%d\n",x,y,st,ed);
		if(ty->Y>2022){strcpy(url,"https://noaa-himawari9.s3.amazonaws.com/AHI-L1b-FLDK/");}//2023/05/03/0000/HS_H09_20230503_0000_B01_FLDK_R10_S0110.DAT.bz2";}
		else{strcpy(url,"https://noaa-himawari8.s3.amazonaws.com/AHI-L1b-FLDK/");}
		
		char* hpurl=(char*)calloc(256,1);
		printf("567\n");
		char t1[2]={'\0'};
		if(hpurl==NULL){printf("error memory allocation \n");ty->error=2;return 0;}

		strcat(url,itoc(ty->Y));
		strcat(url,"/");
		if(ty->M<10)
		{
			strcat(url,"0");
		}
		strcat(url,itoc(ty->M));
		strcat(url,"/");
		if(ty->D<10)
		{
			strcat(url,"0");
		}
		strcat(url,itoc(ty->D));
		strcat(url,"/");
		if(ty->H<10)
		{
			strcat(url,"0");
		}
		strcat(url,itoc(ty->H));
		strcat(url,"");
		if(ty->MIN<10)
		{
			strcat(url,"0");
		}
		strcat(url,itoc(ty->MIN));
		strcat(url,"/");
		//----path over-----
		printf(url);
		printf("\n");
		
		
		if(ty->Y>2022){strcpy(ty->hpdFilename[0],"HS_H09_");}
		else{strcpy(ty->hpdFilename[0],"HS_H08_");}
		strcat(ty->hpdFilename[0],itoc(ty->Y));
		if(ty->M<10)
		{
			strcat(ty->hpdFilename[0],"0");
		}
		strcat(ty->hpdFilename[0],itoc(ty->M));
		if(ty->D<10)
		{
			strcat(ty->hpdFilename[0],"0");
		}
		strcat(ty->hpdFilename[0],itoc(ty->D));
		strcat(ty->hpdFilename[0],"_");
		printf("616\n");
		printf(url);
		printf("\n");
		if(ty->H<10)
		{
			strcat(ty->hpdFilename[0],"0");
		}
		strcat(ty->hpdFilename[0],itoc(ty->H));
		if(ty->MIN<10)
		{
			strcat(ty->hpdFilename[0],"0");
		}
		printf("626\n");
		printf(url);
		printf("\n");
		strcat(ty->hpdFilename[0],itoc(ty->MIN));
		strcat(ty->hpdFilename[0],"_B");
		strcat(ty->hpdFilename[0],band);
		strcat(ty->hpdFilename[0],"_FLDK_R20_S");
		printf(ty->hpdFilename[0]);
		printf("631\n");
		for(int i=1;i<=ed-st;i++)
		{
			printf("%d\n",i);
			strcpy(ty->hpdFilename[i],ty->hpdFilename[0]);
		}
		printf("636\n");
		printf(ty->hpdFilename[1]);
		//printf(url);
		printf("\n");
		for(int i=st;i<=ed;i++)
		{
			//printf(ty->hpdFilename[1]);
			printf("\n");
			int j=i-st;
			//printf(url);
			printf("\n");
			printf("d4\n");
			printf(ty->hpdFilename[j]);
			printf("d7\n");
			printf(ty->hpdFilename[1]);
			printf("\n");
			
			if(i<10)
			{
				t1[0]='0';
				t1[1]=itoc(i)[0];//bugs that will cause memory problems here
				t1[2]=0;
				printf("d2\n");
				printf(url);
				printf("\n");
			}
			else
			{
				t1[0]=itoc(i)[0];
				t1[1]=itoc(i)[1];
				t1[2]=0;
				printf("d3\n");
				printf(url);
				printf("\n");
			}
		
		strcat(ty->hpdFilename[j],t1);
		strcat(ty->hpdFilename[j],"10.DAT.bz2");
		strcpy(hpurl,url);
		strcat(hpurl,ty->hpdFilename[j]);
		printf("\n");
		printf(ty->hpdFilename[j]);
		printf("\n");
		printf(hpurl);
		int rt;
		rt=URLDownloadToFileA(NULL,hpurl,ty->hpdFilename[j],0,NULL);
		printf(itoc(rt));
		}

	}
	return 0;
}
int TYrender(TYinfo* ty,int color)//unknown bug:crash when start execute->fixed:in stack,dataf is too big 
{
	printf_s("begin TYrender\n");
	byte* hppixels;
	UInt16* hpdataf; 
	char outpic[257];
	
	strcpy(outpic,ty->hpdFilename[0]);
	strcat(outpic,".png");
	
	if((GetFileAttributes(outpic)==INVALID_FILE_ATTRIBUTES)&&(GetFileAttributes(ty->hpdFilename[0])!=INVALID_FILE_ATTRIBUTES))
	{
		
	hpdataf=(UInt16*)calloc(1000*1000,2);
	if(hpdataf==NULL){printf("memory allocation error\n");ty->error=2;}
		printf("begin hsdread\n");
	if(ty->Y<2020)
	{
	
	HSdata dt=hsdRead(ty->hpdFilename[0],false,true);
	printf("hsdreadok\n");
	ty->x=(int)((dt.w+dt.w*sin((PI/180)*(ty->lon-140.7))*cos((PI/180)*ty->lat))/2);
	ty->y=(int)((dt.h-dt.h*sin(PI*ty->lat/180))/2);
	printf("x:%d y:%d\n",ty->x,ty->Y);
	for(int i=0;i<1000;i++)
	{
		//printf("dbgsign%d\n",i);
		for(int j=0;j<1000;j++)
		{
			hpdataf[i*1000+j]=dt.data[(i+ty->y-499)*dt.w+j+ty->x-499];
		}
	}

	dt.w=1000;
	dt.h=1000;
	free(dt.data);
	dt.data=hpdataf;

	printf("begin hsdclb\n");
	if(dt.band>3)
	{
	hsdCalibration(&dt,true);//here bug->ok
	printf("hsdRenderdbg1\n");
    switch(color)
	{
	case 1:{hppixels=TtoBD(dt.temp,dt.w*dt.h);break;}
	case 2:{hppixels=TtoColor2(dt.temp,dt.w*dt.h);break;}
	case 3:{hppixels=TtoWVNRL(dt.temp,dt.w*dt.h);break;}
	default:{hppixels=BW(dt.data,dt.w*dt.h,dt.bitnum);}
	}
	}
	else{
		hppixels=BW(dt.data,dt.w*dt.h,dt.bitnum);
	}
	printf("hsdRenderdbg2\n%s\n",outpic);
	lodepng_encode24_file(outpic,hppixels,dt.w,dt.h);
	printf("hsdRenderdbg3\n");
	free(dt.data);//hpdataf=dt.data
	free(dt.temp);
	free(hppixels);

	}
	}
	return 0;
}
int ATyphoon()
{
	char filename[64];
	char band[2];
	char colorscale;
	int color;

	printf("Enter b-deck file name:");
	// gets(filename);
	if (fgets(filename, sizeof(filename), stdin) != NULL) {
		// 改行文字を除去
		size_t len = strlen(filename);
		if (len > 0 && filename[len - 1] == '\n') {
			filename[len - 1] = '\0';
		}
	}
	printf("Enter band(6-16):");
	// gets(band);
	if (fgets(band, sizeof(band), stdin) != NULL) {
		// 改行文字を除去
		size_t len = strlen(band);
		if (len > 0 && band[len - 1] == '\n') {
			band[len - 1] = '\0';
		}
	}
	printf("Enter colorscale:");
	colorscale=getchar();
	color=ctoibit(colorscale);

	//strcpy(filename,"bwp302018.dat");//for debug
	printf("newty\n");
	TYinfo ty=newTYinfo(filename);
	printf("x:%d y:%d\n",ty.x,ty.Y);
	printf("newtyok,dl\n");
	printf("%d\n",ty.info);
	while(ty.info==0)
	{
		for(int j=0;j<36;j++)
		{
		printf("dl\n");
		TYdownloadHimawari89(&ty,band);
		printf("newtyok,dlok\n");
		//try{               a bug here
		TYrender(&ty,color);
		//}catch(char* e){
			//printf(e);
		//}
		//hsdRender(ty.hpdFilename[0],2,NULL,true);*/
		for(int i=0;i<10;i++)
		{
			TYnextmin(&ty);
		}
		}
		printf("nextline\n");
		TYreadNext(&ty);
	}
	TYclose(&ty);
	printf("ok\n");
	return 0;
}
void TYclose(TYinfo *ty)
{
	if(ty->hpdFilename[2]!=NULL)
	{
		free(ty->hpdFilename[2]);
	}
	if(ty->hpdFilename[1]!=NULL)
	{
		free(ty->hpdFilename[1]);
	}
	if(ty->hpdFilename[0]!=NULL)
	{
		free(ty->hpdFilename[0]);
	}
	if(ty->hpMessage!=NULL)
	{
		free(ty->hpMessage);
	}
}
void addMIN(TIME* t,UInt16 min)//bugs when min is too big 
{
	int t1;
	if(min>=1440)
	{
		t1=min/1440;
		min=min-t1*1440;
		t->D+=t1;
	}
	if(min>=60)
	{
		t1=min/60;
		min=min-t1*60;
		t->H+=t1;
	}
	t->MIN+=min;
	if(t->MIN>=60)
	{
		t->MIN-=60;
		t->H++;
	}
	if(t->H>=24)
	{
		t->H-=24;
		t->D++;
	}
	if(t->M==2)//|M=3|M=5|M=7|M=8|M=10|M=12)
	{
		if(t->D>28)//a bug here
		{
			t->D-=28;
			t->M++;
		}
	}
	else if(t->M==4|t->M==6|t->M==9|t->M==11)
	{
		if(t->D>30)
		{
			t->D-=30;
			t->M++;
		}
	}
	else
	{
		if(t->D>31)
		{
			t->D-=31;
			t->M++;
		}
	}
	if(t->M>12)
	{
		t->M-=12;
		t->Y++;
	}
}
