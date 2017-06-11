#include<cstdlib>
#include<iostream>
#include<exception>
#include "func.h"
#include<math.h>
typedef double ddd;
using namespace std;
ddd posynomial(int argc,char* argv[],bool flag)//flag表示算法选择
{
	if(flag == 1)//使用秦九韶算法
	{
		ddd sum;
		sum = 0;
		ddd x;
		x = atof(argv[argc-1]);
		try//判断分母是否为0
		{
			if(x==0)
				throw "Math Error";
		}
		catch(const char* &e)
		{
			cout << e << endl;
			return 0;
		}
		for(int i=argc-2;i>0;i--)
		{
			sum /= x;
			sum += atof(argv[i]);
		}
		return sum;
	}
	else if(!flag)//使用暴力方法
	{
		ddd sum=0;
		ddd x=atof(argv[argc-1]);
		try
		{
			if(x==0)
				throw "Math Error";
		}
		catch(const char* &e)
		{
			std::cout<<e<<std::endl;
			return 0;
		}
		for(int i=argc-2;i>=1;i--)
			sum+=atof(argv[i])/pow(x,i-1);
		return sum;
	}
	return 0;
}