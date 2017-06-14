// coder : davidwang
#include "libs.h"
#include <cstdio>
#include <algorithm>
#include <ctime>
using namespace std;

char buff1[1000], buff2[1000][1000];
int main(int argc, char *argv[]){
	srand(time(0));
	for (int i = 1;i < argc;i++){
		if (!strcmp(argv[i], "-f")) freopen(argv[++i], "r", stdin);
		if (!strcmp(argv[i], "-o")) freopen(argv[++i], "w", stdout);
	}
	fprintf(stderr, "Please Enter the Language(C++,Java,Python,Ruby,Go)(C++ May Correctly Surported Only, Other Language will only be judged)");
	scanf("%s", buff1);
	PlagiarismDetector *detector = nullptr;
	if (!strcmp(buff1, "C++")){
		detector = new CPPPlagiarismDetector();
	}else{
		detector = new PlagiarismDetector();
	}
	int n;
	fprintf(stderr, "Please Enter the paths which needed detect, in Range[2, 1000]: ");
	scanf("%d", &n);
	for (int i = 1;i <= n;i++){
		printf("Please Enter the %d directory: No spaces and tabs included.", i);
		scanf("%s", buff2[i]);
	}
	int m;
	fprintf(stderr, "Please Enter the Threshold of detector word. 20 is default: ");
	if (scanf("%d", &m) != EOF){
		detector -> setValue(m);
	}else{
		detector -> setValue(20);
	}

	for (int i = 1;i <= n;i++){
		for (int j = i+1;j <= n;j++){
			pair<double, double> ret = detector -> check(buff2[i], buff2[j]);
			printf("[%d, %d] (%.3lf%%%.3lf%%)", i, j, ret.first * 100, ret.second * 100);
		}
	}
	return 0;
}
