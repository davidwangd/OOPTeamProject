// author : davidawng
#include "../token_basic.h"
using namespace std;
 
char buff[10000];
Tokenizer *tokenizer = new Tokenizer();
int main(){
	scanf("%s", buff);
	tokenizer -> process(buff);
	auto ret = tokenizer -> GetTokens();
	for (int i = 0;i < ret.size();i++){
		printf("%d %d\n", ret[i]->Value(), ret[i] -> ApproximateValue());
	}
	return 0;
}