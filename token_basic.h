#ifndef OOP_TEAMPROJECT_TOKENBASIC_H
#define OOP_TEAMPROJECT_TOKENBASIC_H
// author : davidwang
#include <cstdio>
#include <vector>

class Token{
public:
	virtual ~Token() = default;
	Token() = default;
	Token(char c): c(c){} 
	virtual int ApproximateEqual(const Token *other) const { return this -> c == other -> c; }
	virtual int Equal(const Token *other) const { return this -> c == other -> c;}
	virtual int Value() const { return this -> c; }
	virtual int ApproximateValue() const { return this -> c;} 
	virtual int MaxValue() const { return 128; }
	virtual int MaxApproximateValue() const { return 128; }
private:
	char c;
};

class Tokenizer{
public:
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
protected:
	std::vector<const Token *> tokens;
};

#endif // OOP_TEAMPROJECT_TOKENBASIC_H