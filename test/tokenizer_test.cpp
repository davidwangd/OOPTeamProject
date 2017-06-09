#define DEBUG_CPPTOKEN
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "../CPPToken.h"
#include "../CPPToken.cpp"
#include "../utils/CPP_Language/CppLexer.h"
#include "../utils/CPP_Language/CppLexer.cpp"
using namespace std;

class TokenTester{
	Tokenizer *tokenizer;
	vector<const Token *> ret;
public:
	TokenTester(const char *ch){
		tokenizer = new CPPTokenizer(); 
		ret = tokenizer -> process(ch);
		for (auto c:ret){
			printf("%s %s\n", c -> str.c_str(), CPPLanguage::cppTokenNames[c -> getType()]);
		}
	}

};
char buff[100000];
int main(){
	freopen("tokenizer_test.hpp", "r", stdin);
	char ch;
	int cnt = 0;
	while (~scanf("%c", &ch)) buff[cnt++] = ch;
	TokenTester cur(buff);
	return 0;
}