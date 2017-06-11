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
	LARGE_INTEGER winFreq;
	LARGE_INTEGER winStart, winNow;
	double polysum_1=0;
	double polysum_2=0;
	double posysum_1=0;
	double posysum_2=0;
	if (!QueryPerformanceFrequency (&winFreq))
		printf ("QueryPerformanceFrequency failed\n");
	if (!QueryPerformanceCounter (&winStart))
		printf ("QueryPerformanceCounter failed\n");
	for (int i = 0; i < 10000; i++)
		for (int j = 0; j < 10000; j++)
			polysum_1=polynomial(argc,argv,true);
	if (!QueryPerformanceCounter (&winNow))
		printf ("QueryPerformanceCounter failed\n");
	double time_poly_new=winNow.QuadPart-winStart.QuadPart;//使用秦九韶算法计算polynomial的时间
	if(!QueryPerformanceCounter(&winStart))
		printf("QueryPerformanceCounter failed\n");
	for(int i=0;i<10000;i++)
		for(int j=0;j<10000;j++)
			posysum_1=posynomial(argc,argv,true);
	if (!QueryPerformanceCounter (&winNow))
		printf ("QueryPerformanceCounter failed\n");
	double time_posy_new=winNow.QuadPart-winStart.QuadPart;//使用秦九韶算法计算posynomial的时间
	if (!QueryPerformanceCounter (&winStart))
		printf ("QueryPerformanceCounter failed\n");
	for (int i = 0; i < 10000; i++)
		for (int j = 0; j < 10000; j++)
			polysum_2=polynomial(argc,argv,false);
	if (!QueryPerformanceCounter (&winNow))
		printf ("QueryPerformanceCounter failed\n");
	double time_poly_old=winNow.QuadPart-winStart.QuadPart;//使用暴力方法计算polynomial的时间
	if(!QueryPerformanceCounter(&winStart))
		printf("QueryPerformanceCounter failed\n");
	for(int i=0;i<10000;i++)
		for(int j=0;j<10000;j++)
			posysum_2=posynomial(argc,argv,false);
	if (!QueryPerformanceCounter (&winNow))
		printf ("QueryPerformanceCounter failed\n");
	double time_posy_old=winNow.QuadPart-winStart.QuadPart;//使用暴力方法计算posynomial的时间
	double poly_imp=(time_poly_old-time_poly_new)/time_poly_old;//polynomial的效率增长
	double posy_imp=(time_posy_old-time_posy_new)/time_posy_old;//posynomial的效率增长
	char buffer[1000];
	sprintf(buffer, "Polysum_1:%g Polysum_2:%g Polysum improvement:%g%%\nPosysum_1:%g Posysum_2:%g Posy improvement:%g%%\n", 
		polysum_1,polysum_2,poly_imp*100,posysum_1,posysum_2,posy_imp*100);
	cout << buffer <<endl;
	return 0;
}
