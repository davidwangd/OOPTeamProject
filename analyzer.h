#ifndef OOP_TEAMWORK_ANALYZER_H
#define OOP_TEAMWORK_ANALYZER_H
//coder:jxt

#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <vector>
#include <map>
#include <utility>
#include "token_basic.h"
typedef std::pair<double,double> pd;

using namespace std;

struct St{
	int id,hs;
	bool operator < (const St &A) {
		return hs<A.hs;
	}
};

class Analyzer{
	private:
	vector<int> Ha,Hb;
	map<int,int> HH;
	const static int Mo=998244353;
	const static int Ad=131;
	int M;//the m in the Greedy-String-Tiling Algorithm,the minimum length that can match
	public:
	Analyzer() = default;
	double Hash();//Calculate the similarity measure
	pd check(const vector<const Token *> &A,const vector<const Token *> &B);//Greedy-String-Tiling,
	//return the similarity measure respectively for Value and ApproximateValue
	void set_M(int m){M=m;};//set a M from the information of the keyboard
};

#endif