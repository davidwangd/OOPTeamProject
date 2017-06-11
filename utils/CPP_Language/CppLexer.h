#ifndef OOP_TEAMPROJECT_CPPLEXER_H
#define OOP_TEAMPROJECT_CPPLEXER_H

// coder : davidwang

#include <stack>
#include <string>
namespace CPPLanguage{
	enum TokenType{
		IgnoredWord = 0,
		ControlWord ,  // break, continue, return
		ConditionWord,  // if else 
		LoopWord, // for do while
		TypeDef,
		Friend,
		Virtual,
		Const,
		Catch,
		Try,
		Default,
		Delete,
		New,
		Inline,
		Private,
		Public,
		Protected,
		Using,
		Namespace,
		Static,
		Class,
		Switch,
		Case,
		This,
		Register,
		Identifier,
		Blank,
		OpenBrace,
		CloseBrace,
		Namespace, // ::
		Colon,
		Operator,
		Number,
		String,
		Assignment,
		OpenBracket,
		CloseBracket,
		OpenParentheses,
		CloseParentheses,
		Semicolon, //; 
		Comma, // ,
		Dot,
		Lemma,
		cppTokenTypeCount
	};

	// coder : davidwang
	class Lexer{
	public:
		// Register a string
		Lexer();
		void Analysis(const char *source);
		std::pair<TokenType, std::string> GetNextToken();
		std::pair<TokenType, std::string> LookAhead();
		int finish() const;
		void registerTypeDef(const std::string& info);
	private:
		// To process the saved tokens
		std::stack<std::pair<TokenType, std::string>> Stack;
		std::string str;
		int position;
		
		static int matchersOKflag;
	};

	
}
#endif // OOP_TEAMPROJECT_CPPLEXER_H