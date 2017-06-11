#include <sys/time.h>
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
  int i, j;

  if (!QueryPerformanceFrequency (&winFreq))
    printf ("QueryPerformanceFrequency failed\n");
    
/*--------------Original algorithm--------------*/
  double direct_polysum = 0;
  double direct_posysum = 0;

  if (!QueryPerformanceCounter (&winStart))
    printf ("QueryPerformanceCounter failed\n");

  for (i = 0; i < 10000; i++)
    for (j = 0; j < 10000; j++)
    {
    	direct_polysum = direct_polynomial(argc, argv);
    	direct_posysum = direct_posynomial(argc, argv);
    }

  if (!QueryPerformanceCounter (&winNow))
    printf ("QueryPerformanceCounter failed\n");

  double direct_time = (double)(winNow.QuadPart - winStart.QuadPart) / (double)winFreq.QuadPart;

  if (!QueryPerformanceFrequency (&winFreq))
    printf ("QueryPerformanceFrequency failed\n");

/*--------------Qin's algorithm--------------*/
  double qin_polysum = 0;
  double qin_posysum = 0;

  if (!QueryPerformanceCounter (&winStart))
    printf ("QueryPerformanceCounter failed\n");

  for (i = 0; i < 10000; i++)
    for (j = 0; j < 10000; j++)
    {
    	qin_polysum = qin_polynomial(argc, argv);
    	qin_posysum = qin_posynomial(argc, argv);
    }

  if (!QueryPerformanceCounter (&winNow))
    printf ("QueryPerformanceCounter failed\n");
  double qin_time = (double)(winNow.QuadPart - winStart.QuadPart) / (double)winFreq.QuadPart;
/*--------------calculate improcement--------------*/
  double imp = (direct_time-qin_time)/direct_time;

/*--------------Qin's algorithm--------------*/

  char buffer[1000];
  sprintf(buffer, "Original method: poly sum %g, posysum:%g, Total runtime of original method %g s\nQin's way: poly sum %g, posysum:%g, Total runtime of qin's method %g s\nImprovement:%g%%\n", direct_polysum, direct_posysum, direct_time, qin_polysum, qin_posysum, qin_time, imp*100);
  cout << buffer <<endl;

  return 0;
}

