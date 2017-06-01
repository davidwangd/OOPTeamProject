#include "../utils/CPP_Language/CppLexer.h"
#include "../utils/CPP_Language/CppLexer.cpp"
#include "../utils/regex.h"
#include "../utils/regex.cpp"
#include <cstdio>
#include <cstring>
#include <cstdlib>

using namespace std;
char buff[10000];
using namespace CPPLanguage;
int main(){
	freopen("cpplexer_test.hpp", "r", stdin);
	char ch;
	int cur = 0;
	while (scanf("%c", &ch) != EOF){
		buff[cur++] = ch;
	}
	printf("%s\n", buff);
	buff[cur] = 0;
	Lexer lexer;
	lexer.Analysis(buff);
	while (!lexer.finish()){
		auto cur = lexer.GetNextToken();
		printf("%s, %s\n", cppTokenNames[cur.first], cur.second.c_str());
	}
	return 0;
}