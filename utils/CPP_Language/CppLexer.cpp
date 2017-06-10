// coder : davidwang
#include "CppLexer.h"
#include "../../utils/regex.h"
using namespace std;

namespace CPPLanguage{
	int Lexer::matchersOKflag = 0;
	Regex::RE cppTokenMatchers[cppTokenTypeCount];
	const char* cppTokenNames[cppTokenTypeCount + 1] = {
		"IgnoredWord",
		"ControlWord",
		"ConditionWord",
		"LoopWord",
		"TypeDef",
		"Friend",
		"Virtual",
		"Const",
		"Case",
		"Catch",
		"Try",
		"Default",
		"Delete",
		"New",
		"Inline",
		"Private",
		"Public",
		"Protected",
		"Static",
		"Class",
		"This",
		"Register",
		"Identifier",
		"Blank",
		"OpenBrace",
		"CloseBrace",
		"Namespace::",
		"Colon:",
		"Operator",
		"Number",
		"String",
		"Assignment",
		"OpenBracket[",
		"CloseBracket]",
		"OpenParentheses(",
		"CloseParentheses)",
		"Semicolon;",
		"Comma,",
		"Dot.",
		"ErrorType!!"
	};


	Lexer::Lexer(){
		if (matchersOKflag) return;
		matchersOKflag++;
		cppTokenMatchers[IgnoredWord].setPattern(string("`"));
	 	cppTokenMatchers[ControlWord].setPattern(string("return+break+goto+continue")); // Control words
	 	cppTokenMatchers[ConditionWord].setPattern(string("if+else"));
	 	cppTokenMatchers[LoopWord].setPattern(string("do+while+for"));
		cppTokenMatchers[TypeDef].setPattern(string("char+int+float+double+long(@b+@n+@t)!double+long(@b+@n+@t)!long+unsigned(@b+@n+@t)!int+void+unsigned(@b+@n+@t)!long+unsigned(@b+@n+@t)!int+signed(@b+@n+@t)!int+(@b+@n+@t)!long+unsigned(@b+@n+@t)!long(@b+@n+@t)!long"));
		cppTokenMatchers[Identifier].setPattern(string("([a-z]+[A-Z]+_)([a-z]+[A-Z]+[0-9]+_)*")); // Identifier
		cppTokenMatchers[Blank].setPattern(string("(@b+@t+@n)!"));
		cppTokenMatchers[OpenBrace].setPattern(string("{"));
		cppTokenMatchers[CloseBrace].setPattern(string("}")); //Brace
		cppTokenMatchers[Namespace].setPattern(string("::")); // Namespace
		cppTokenMatchers[Operator].setPattern(string("@!=+@!+==+@++@*+@?+@/+->+-+:+%+&&+&+||+|+^+<=+>=+<+>")); // Operator
		cppTokenMatchers[Number].setPattern(string("0+[1-9][0-9]*((e+E)[0-9]!)?(l?+(ll)?+L?+(LL)?+(ld)?+(LD)?+f?+F?)+[0-9]!.[0-9]*((e+E)[0-9]!)?f?+.[0-9]!((e+E)[0-9]!)?f?"));
		cppTokenMatchers[String].setPattern(string("\"([\"]+\\[-])*\"+'([']+\\[-])'"));
		cppTokenMatchers[Assignment].setPattern(string("=+@+=+-=+@*=+@/=+%=")); // Assignment
		cppTokenMatchers[OpenBracket].setPattern(string("["));
		cppTokenMatchers[CloseBracket].setPattern(string("]"));
		cppTokenMatchers[OpenParentheses].setPattern(string("("));
		cppTokenMatchers[CloseParentheses].setPattern(string(")"));
		cppTokenMatchers[Semicolon].setPattern(string(";"));
		cppTokenMatchers[Comma].setPattern(string(","));
		cppTokenMatchers[Dot].setPattern(string("."));
		cppTokenMatchers[Colon].setPattern(string(":"));
		for (int i = Friend; i <= Register; i++){
			if (i == Class){
				cppTokenMatchers[i].setPattern("class+struct");
				continue;
			}
			string cur = cppTokenNames[i];
			cur[0] = cur[0] - 'A' + 'a';
			cppTokenMatchers[i].setPattern(cur);
		}
		position = 0;
	#ifdef DEBUG
		fprintf(stderr, "Build Successfully!\n");
	#endif
	}

	void Lexer::registerTypeDef(const string &info){
		cppTokenMatchers[TypeDef].setPattern(info + "+char+int+float+double+long(@b+@n+@t)!double+long(@b+@n+@t)!long+unsigned(@b+@n+@t)!int+void+unsigned(@b+@n+@t)!long+unsigned(@b+@n+@t)!int+signed(@b+@n+@t)!int+(@b+@n+@t)!long+unsigned(@b+@n+@t)!long(@b+@n+@t)!long");	
	}
	
	void Lexer::Analysis(const char *source){
		str = string(source);
		position = 0;
	}

	pair<TokenType, string> Lexer::GetNextToken(){
		int curMax = -1;
		for (int i = 0;i < cppTokenTypeCount;i++){
		#ifdef DEBUG
			fprintf(stderr, "Matching %s\n", cppTokenMatchers[i].getPattern().c_str());
		#endif
			int x = cppTokenMatchers[i].match(str, position, -1);
		#ifdef DEBUG
			fprintf(stderr, "TokenMatchers[%s] match result %d\n", cppTokenNames[i], x);
		#endif
			curMax = max(curMax, cppTokenMatchers[i].match(str, position, -1));
		}
		if (curMax < position){
			fprintf(stderr, "lexer failed. unable to recognize character %c\n", str[position]);
			position = str.length();
			return make_pair(cppTokenTypeCount, string(""));
		}else{
			for (int i = 0;i < cppTokenTypeCount;i++){
				if (cppTokenMatchers[i].match(str, position, -1) == curMax){
					int cur = position;
					position = curMax + 1;
					return make_pair((TokenType)i, str.substr(cur, position - cur));
				}
			}
		}
	}

	pair<TokenType, string> Lexer::LookAhead() {
		int cur = position;
		auto ret = GetNextToken();
		position = cur;
		return ret;
	}

	int Lexer::finish() const {
		return position == str.length();
	}
}