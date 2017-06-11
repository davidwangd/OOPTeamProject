/*-------------calculate polynomial-------------*/
#include <iostream>
#include <cstdlib>
#include <cstring>
#include "func.h"
using namespace std;

double direct_polynomial(int argc, char* args[]) {
	//double xn = atof(args[argc-1]), x = 1.0;
	double xn = atof(args[argc-1]);
	double sum = 0;
	for (int i=1; i<argc-1; i++) {
		double x = 1.0;
		for (int j=1; j<i; j++)
			x *= xn;
		sum += atof(args[i])*x;
		//x *= xn;
	}
	//cout << "Polynomial Function: " << sum << endl;
	return sum;
}

double qin_polynomial(int argc, char* args[]) {
	double xn = atof(args[argc-1]);
	double sum = 0;
	for (int i=argc-2; i>=1; i--)
		sum = sum*xn+atof(args[i]);
	//cout << "Polynomial Function: " << sum << endl;
	return sum;
}
