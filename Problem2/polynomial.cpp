#include<cstdlib>
#include<iostream>
#include "func.h"
#include<math.h>
typedef double ddd;
ddd polynomial(int argc,char* argv[],bool flag)//flag表示算法的选择
{
	if(flag)//使用秦九韶算法
	{
		ddd sum=0;
		ddd x=atof(argv[argc-1]);
		for(int i=argc-2;i>0;i--)
		{
			sum*=x;
			sum+=atof(argv[i]);
		}
		return sum;
	}
	else//使用暴力方法
	{
		ddd sum=0;
		ddd x = atof(argv[argc-1]);
		for(int i = argc - 2 ; i > 0; --i)
			sum += atof(argv[i]) * pow(x, i-1);
		return sum;
	}
	return 0;
}