// coder : davidwang
#include "CPPToken.h"
#include <memory.h>
#include <iostream>
using namespace std;
using namespace CPPLanguage;

int CPPToken::MaxId = -1;
map<string, int> CPPToken::str2int = map<string, int>();

void CPPTokenizer::eraseToken(int pos, int cnt){
	for (int i = 0;i < cnt;i++){
		delete tokens[pos];
		tokens.erase(tokens.begin() + pos);
	}
}

void CPPTokenizer::reduce(){
	// TODO reduce the some magic work in tokens...
	for (int i = 0;i < tokens.size();i++){
		if ((tokens[i]->getType() == Public || tokens[i]->getType() == Private || tokens[i]->getType() == Protected) && tokens[i+1] -> getType() == Colon){
			eraseToken(i, 2);
			i--;
		}
	}
}

int CPPTokenizer::shouldIgnore(TokenType type){
	if (type == Blank || type == Const || type == Static || type == Operator || type == Inline || type == Register) return 1;
	if (type == Friend || type == Virtual) return 1;
	return 0;
}

int CPPTokenizer::shouldEmphises(TokenType type){
	return type == Assignment || (int)type <= (int)TypeDef;
}

vector<const Token *> CPPTokenizer::process(const char *source){
	lexer.Analysis(source);

	while (!lexer.finish()){
		auto ret = lexer.GetNextToken();
		
		// for Blank, We simply Drop them
		if (shouldIgnore(ret.first)){
			continue;
		}else{
			tokens.push_back(new CPPToken(ret));
			if (shouldEmphises(ret.first)){
				tokens.push_back(new CPPToken(ret));
			}
		}
	}
	reduce();
	return tokens;
}

CPPToken::CPPToken(pair<TokenType, string> type){
	this -> type = type.first;
	this -> str = type.second;
	if (str2int.find(str) == str2int.end()){
		str2int.insert(make_pair(str, ++MaxId));
	}
}

int CPPToken::Equal(const Token *other) const {
	CPPToken *rhs = (CPPToken *) other;
	return this -> type == rhs -> type && this -> str == rhs -> str;
}

int CPPToken::ApproximateEqual(const Token *other) const {
	CPPToken *rhs = (CPPToken *) other;
	return this -> type == rhs -> type;
}

int CPPToken::Value() const {
	return str2int[this -> str];
}

int CPPToken::MaxValue() const{
	return str2int.size();
}

int CPPToken::ApproximateValue() const {
	return (int)type;
}

int CPPToken::MaxApproximateValue() const {
	return (int)CPPLanguage::cppTokenTypeCount;
}

int CPPTokenizer::ProcessorInfo(const string& info, int valueType){
	if (valueType == -1){
		lexer.registerTypeDef(info);
		return 1;
	}

	return 0;
}