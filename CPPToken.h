#ifndef OOP_TEAMPROJECT_CPPTOKEN_H
#define OOP_TEAMPROJECT_CPPTOKEN_H

// coder : davidwang

#include "utils/regex.h"
#include "utils/CPP_Language/CppLexer.h"
#include "token_basic.h"
#include <string>
#include <vector>
#include <map>

// CPPToken type.. 
class CPPToken : public Token{
public:
	friend class CPPTokenizer;
#ifdef DEBUG_CPPTOKEN
	// This is TokenTester class..
	friend class TokenTester;
#endif
	// type and id is provided when TokenType is Identifier.. before the first declaration of the identifier..
	CPPToken(std::pair<CPPLanguage::TokenType, std::string> type);
	virtual int Equal(const Token *other) const ;
	virtual int ApproximateEqual(const Token *other) const;
	virtual int Value() const;
	virtual int ApproximateValue() const;
	// This is also returned to help hash usage..
	virtual int MaxValue() const;
	virtual int MaxApproximateValue() const;
	virtual int getType() const{
		return (int)type;
	}
private:
	CPPLanguage::TokenType type;

	static std::map<std::string, int> str2int;
	static int MaxId;
};

class CPPTokenizer : public Tokenizer {
public:
	CPPTokenizer(): Tokenizer(), cntId(0){}
	virtual std::vector<const Token *> process(const char *source);
	virtual std::vector<const Token *> GetTokens() const{
		return tokens;
	}
	virtual int ProcessorInfo(const std::string& info, int valueType = -1);
private:
	int shouldIgnore(CPPLanguage::TokenType type);
	int shouldEmphises(CPPLanguage::TokenType type);
	void reduce();
	void eraseToken(int pos, int cnt);
	std::map<std::string, int> id2int;
	// This stack is to implement a simple Pushdown-automata,
	std::stack<std::pair<CPPLanguage::TokenType, std::string> > Stack;
	CPPLanguage::Lexer lexer;
	std::vector<std::string> idType;
	int cntId;
};

#endif // OOP_TEAMPROJECT_CPPTOKEN_H