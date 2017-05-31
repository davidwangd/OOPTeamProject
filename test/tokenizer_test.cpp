#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "../CPPToken.h"
using namespace std;
char buff[100000];
int main(){
	freopen("tokenizer_test.hpp", "r", stdin);
	char ch;
	int cnt = 0;
	while (~scanf("%c", &ch)) buff[cnt++] = ch;
	Tokenizer* tokenizer = new CPPTokenizer();
	auto ret = tokenizer -> process(buff);
	for (auto c:ret){
		printf("%d %d\n", c->Value(), c-> ApproximateValue());
	}
	return 0;
}