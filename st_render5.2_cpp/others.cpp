#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "st_render.h"

void depress(const char* file)
{
	size_t size=strlen(file)+12+1;
	char* com=(char*)malloc(size);
	strcpy_s(com,size,"7z e \"");
	strcat_s(com,size,file);
	strcat_s(com,size,"\"&exit");
	system(com);
	free(com);
}
bool compare(const char* s1,const char* s2)
{
	size_t _s1,_s2;
	_s1=strlen(s1);
	_s2=strlen(s2);
	if(_s1!=_s2)
	{
		return false;
	}
	else
	{
		_s2=0;
		while(_s2<_s1)
		{
			if(s1[_s2]!=s2[_s2])
			{
				return false;
			}
			_s2++;
		}
		return true;
	}
}
void ClearArgs(InputArgs* args)
{
	args->color=NULL;
	args->filename=NULL;
	args->outpic=NULL;
	args->path=NULL;
	args->op=0;
}
void SplitArgs(InputArgs* input,int argc,char** argv)
{
	ClearArgs(input);
	int i=1;
	if(argc<=2)
	{
		input->op=1;
	}
	else
	{
		while(i<argc-1)
		{
			if(compare("hsdfile",argv[i])){input->op=2;}
			else if(compare("goesncfile",argv[i])){input->op=3;}
			else if(compare("file",argv[i])){i++;input->filename=argv[i];}
			else if(compare("color",argv[i])){i++;input->color=ctoi(argv[i],strlen(argv[i]));}
			else if(compare("path",argv[i])){i++;input->path=argv[i];}
			else if(compare("outpic",argv[i])){i++;input->outpic=argv[i];}
			i++;
		}
	}
}
void STdata_initialize(STdata* data)//unfinished
{
	data->errcode=0;
	data->type=0;
	data->progress=0;
	data->hpSTdata=NULL;
	data->args=NULL;
	data->args=malloc(sizeof(InputArgs));
	if(data->args==NULL){data->errcode=1;}
}
int ctoi(char* str,int l)
{
	int o=0;
	for(int i=0;i<l;i++)
	{
		o+=ctoibit(str[i])*power(10,l-i-1);
	}
	return o;
}
int ctoibit(char c)
{
	int o=0;
	switch(c)
	{
	case '0':{o=0;break;}
	case '1':{o=1;break;}
	case '2':{o=2;break;}
	case '3':{o=3;break;}
	case '4':{o=4;break;}
	case '5':{o=5;break;}
	case '6':{o=6;break;}
	case '7':{o=7;break;}
	case '8':{o=8;break;}
	case '9':{o=9;break;}
	}
	return o;
}
int power(int base,int p)
{
	int o=1;
	while(p>0)
	{
		o*=base;
		p--;
	}
	return o;
}
char* itoc(int i)
{
	char* o=NULL;
	if(i>0)
	{
	int j=0,t1,t2;
	while(i>=power(10,j))
	{
		j++;
	}
	//printf("%d",j);
	o=(char*)calloc(j+1,1);
	if(o==NULL){return o;}
	j--;
	t2=j;
	while(j>=0)
	{
		t1=i/power(10,j);
		i-=t1*power(10,j);
		o[t2-j]=itocbit(t1);
		j--;
	}
	}
	else if(i<=0){o=(char*)calloc(2,1);o[0]='0';}
	return o;
}
char itocbit(int i)
{
	char o;
	switch(i)
	{
		case 0:{o='0';break;}
		case 1:{o='1';break;}
		case 2:{o='2';break;}
		case 3:{o='3';break;}
		case 4:{o='4';break;}
		case 5:{o='5';break;}
		case 6:{o='6';break;}
		case 7:{o='7';break;}
		case 8:{o='8';break;}
		case 9:{o='9';break;}
	}
	return o;
}
void st_render_help(){
	printf("this is under maintenance\n");
	system("pause");
}