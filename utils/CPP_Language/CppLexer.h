#ifndef OOP_TEAMPROJECT_CPPLEXER_H
#define OOP_TEAMPROJECT_CPPLEXER_H

#include <stack>
#include <string>

namespace CPPLanguage{
	enum TokenType{
		ControlWord,
		TypeDef,
		KeyWord,
		Identifier,
		Blank,
		// 大括号， 用于模糊匹配
		OpenBrace,
		CloseBrace,
		// 详细大括号
		BeginLoop,
		EndLoop,
		BeginClass,
		EndClass,
		BeginNamespace,
		EndNamespace,
		BeginIf,
		EndIf,
		BeginFcn,
		EndFcn,
		Namespace, // ::
		Operator,
		// += -= *= /=
		Number,
		String,
		Assignment,
		// 中括号
		OpenBracket,
		CloseBracket,
		// 小括号
		OpenParentheses,
		CloseParentheses,
		Semicolon, //; 
		Comma, // ,
		cppTokenTypeCount
	};

	// coder : davidwang
	class Lexer{
	public:
		// Register a string
		Lexer();
		void Register(const char *source);
		std::pair<TokenType, std::string> GetNextToken();
		std::pair<TokenType, std::string> LookAhead();
		int finish() const;
	private:
		// To process the saved tokens
		std::stack<std::pair<TokenType, std::string>> Stack;
		std::string str;
		int position;
		
		static int matchersOKflag;
	};

	
}
#endif // OOP_TEAMPROJECT_CPPLEXER_H