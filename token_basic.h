#ifndef OOP_TEAMPROJECT_TOKENBASIC_H
#define OOP_TEAMPROJECT_TOKENBASIC_H
// author : davidwang
#include <cstdio>
#include <vector>
#include <string>

class Token{
#ifdef DEBUG
	friend class CPPPlagiarismDetector;
#endif
public:
	virtual ~Token() = default;
	Token() = default;
	Token(char c): str(c, 1){} 
	virtual int ApproximateEqual(const Token *other) const { return this -> str == other -> str; }
	virtual int Equal(const Token *other) const { return this -> str == other -> str;}
	virtual int Value() const { return this -> str[0]; }
	virtual int ApproximateValue() const { return this -> str[0];} 
	virtual int MaxValue() const { return 128; }
	virtual int MaxApproximateValue() const { return 128; }
	virtual int getType() const{
		return (int)str[0];
	}
protected:
	std::string str;
};

class Tokenizer{
public:
	Tokenizer() = default;
	virtual std::vector<const Token *> process(const char *source){
		tokens.clear();
		for (int i = 0; source[i]; i++){
			tokens.push_back(new Token(source[i]));
		}
		return tokens;
	}
	virtual std::vector<const Token *> GetTokens() const{
		return tokens;
	}
	virtual ~Tokenizer(){
		for (auto x : tokens){
			delete x;
		}
	}
	virtual int ProcessorInfo(const std::string& info, int valueType = -1){
		return 1;
	}
protected:
	std::vector<const Token *> tokens;
};

#endif // OOP_TEAMPROJECT_TOKENBASIC_H