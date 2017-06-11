#ifndef OOP_TEAMWORK_ANALYZER_H
#define OOP_TEAMWORK_ANALYZER_H
//coder:jxt

#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<vector>
#include<map>
#include<utility>
#include "CPPToken.h"
typedef pair<double,double> pd;

using namespace std;

class Analyzer{
	private:
	int *HB;
	vector<int> Ha,Hb;
	map<int,int> HH;
	const static int Mo=998244353;
	const static int Ad=131;
	bool 
	int M;//the m in the Greedy-String-Tiling Algorithm,the minimum length that can match
	public:
	Analyzer();
	double Hash(vector<int> &A,vector<int> &B);//Calculate the similarity measure
	pd check(const vector<Token *> &A,const vector<Token *> &B);//Greedy-String-Tiling,
	//return the similarity measure respectively for Value and ApproximateValue
	void set_M(int m){M=m;};//set a M from the information of the keyboard
};

#endif