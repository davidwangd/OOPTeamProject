/*-------------calculate posynomial-------------*/
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include "func.h"
using namespace std;
#define eps 1e-9

double direct_posynomial(int argc, char* args[]) {
	//double xn = atof(args[argc-1]), x = 1.0;
	double xn = atof(args[argc-1]);
	if (fabs(xn) < eps) {
		cout << "Polynomial Function: x cannot be equal to 0!" << endl;
		return 0;
	}
	xn = 1/xn;
	double sum = 0;
	for (int i=1; i<argc-1; i++) {
		double x = 1.0;
		for (int j=0; j<i; j++)
			x *= xn;
		sum += atof(args[i])*x;
	}
	//cout << "Polynomial Function: " << sum << endl;
	return sum;
}

double qin_posynomial(int argc, char* args[]) {
	double xn = atof(args[argc-1]);
	if (fabs(xn) < eps) {
		cout << "Polynomial Function: x cannot be equal to 0!" << endl;
		return 0;
	}
	xn = 1/xn;
	double sum = 0;
	for (int i=argc-2; i>=1; i--)
		sum = sum*xn+atof(args[i]);
	//cout << "Polynomial Function: " << sum << endl;
	return sum;
}
