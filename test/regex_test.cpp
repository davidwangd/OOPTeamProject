// coder : davidwang
#include "../utils/regex.h"
#include "../utils/regex.cpp"

#include <iostream>
#include <string>

using namespace std;
int main(){
	string s, t;
	cin >> s;
	Regex::RE now(s);
	while (cin >> t){
		printf("%d\n", now.match(t));
	}
}