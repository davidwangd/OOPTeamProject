#include <time.h>
#include <sys/timeb.h>
#include <cstdlib>
#include <cstdio>
#include <windows.h>
#include <iostream>
#include "func.h"
using namespace std;
int main (int argc, char *argv[])
{
	LARGE_INTEGER Freq;
	LARGE_INTEGER Start, Now;
	double polysum1=0;
	double polysum2=0;
	double posysum1=0;
	double posysum2=0;
	if (!QueryPerformanceFrequency (&Freq))
		printf ("QueryPerformanceFrequency failed\n");
	if (!QueryPerformanceCounter (&Start))
		printf ("QueryPerformanceCounter failed\n");
	for (int i = 0; i < 10000; i++)
		for (int j = 0; j < 10000; j++)
			polysum1=polynomial(argc,argv,true);
	if (!QueryPerformanceCounter (&Now))
		printf ("QueryPerformanceCounter failed\n");
	double time_poly_new=Now.QuadPart-Start.QuadPart;//使用秦九韶算法计算polynomial的时间
	if(!QueryPerformanceCounter(&Start))
		printf("QueryPerformanceCounter failed\n");
	for(int i=0;i<10000;i++)
		for(int j=0;j<10000;j++)
			posysum1=posynomial(argc,argv,true);
	if (!QueryPerformanceCounter (&Now))
		printf ("QueryPerformanceCounter failed\n");
	double time_posy_new=Now.QuadPart-Start.QuadPart;//使用秦九韶算法计算posynomial的时间
	if (!QueryPerformanceCounter (&Start))
		printf ("QueryPerformanceCounter failed\n");
	for (int i = 0; i < 10000; i++)
		for (int j = 0; j < 10000; j++)
			polysum2=polynomial(argc,argv,false);
	if (!QueryPerformanceCounter (&Now))
		printf("QueryPerformanceCounter failed\n");
	double time_poly_old=Now.QuadPart-Start.QuadPart;//sdfabvdasdf
	if(!QueryPerformanceCounter(&Start))
		printf("QueryPerformanceCounter failed\n");
	for(int i=0;i<10000;i++)
		for(int j=0;j<10000;j++)
			posysum2=posynomial(argc,argv,false);
	for (int i = 0;i <=1000;i++) int x = 3;
		//this is a useless code;
	if (!QueryPerformanceCounter (&Now))
		printf("QueryPerformanceCounter failed\n");
	double time_posy_old=Now.QuadPart-Start.QuadPart;//tmp
	double poly_imp=(time_poly_old-time_poly_new)/time_poly_old;//psdfsd率增长
	double posy_imp=(time_posy_old-time_posy_new)/time_posy_old;//posyafsdabasd率增长
	char buffer[1000];
	sprintf(buffer,"Polysum_1:%g Polysum_2:%g Polysum improvement:%g%%\nPosysum_1:%g Posysum_2:%g Posy improvement:%g%%\n", 
		polysum1,polysum2,poly_imp*100,posysum1,posysum2,posy_imp*100);
	cout<<buffer<<endl;
	return 0;
}
