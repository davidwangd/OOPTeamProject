// coder : davidwang
#include "../utils/regex.h"
#include "../utils/regex.cpp"

#include <iostream>
#include <string>

using namespace std;
int main(){
	char buff[100000];
	string s, t;
	cin >> s;
	Regex::RE now(s);
	while (gets(buff)){
		printf("%d\n", now.match(string(buff)));
	}
}