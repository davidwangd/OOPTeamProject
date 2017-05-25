#ifndef OOP_TEAMPROJECT_CPPTOKEN_H
#define OOP_TEAMPROJECT_CPPTOKEN_H

// coder : davidwang

#include "utils/regex.h"
#include "utils/CPP_Language/CppLexer.h"
#include "basic_token.h"

// CPPToken type.. 
class CPPToken : public Token{
public:
	// type and id is provided when TokenType is Identifier.. before the first declaration of the identifier..
	CPPToken(std::pair<CPPLanguage::TokenType, std::string> type, string idtype = string(""), int id = -1);
	virtual int Equal() const ;
	virtual int ApproximateEqual() const;
	virtual int Value() const;
	virtual int ApproximateValue() const;
	// This is also returned to help hash usage..
	virtual int MaxValue() const;
	virtual int MaxApproximateValue() const;
private:
	CPPLanguage::TokenType type;
	std::string str;
	std::string idtype;
	static int MaxId;
	// to reserve the Token type
	int id;
};

class CPPTokenizer : public Tokenizer {
public:
	CPPTokenizer(): Tokenizer(), cntId(0){}
	virtual std::vector<const Token *> process(const char *source);
private:
	std::map<std::string, int> id2int;
	// This stack is to implement a simple Pushdown-automata,
	std::stack<std::pair<CPPLanguage::TokenType, std::string> > Stack;
	CPPLanguage::Lexer lexer;
	std::vector<std::string> idType;
	int cntId;
};

#endif // OOP_TEAMPROJECT_CPPTOKEN_H