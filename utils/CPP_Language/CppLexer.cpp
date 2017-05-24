#include "CppLexer.h"
#include "../../utils/regex.h"
using namespace std;

namespace CPPLanguage{
	int Lexer::matchersOKflag = 0;
	Regex::RE cppTokenMatchers[cppTokenTypeCount];
	const char* cppTokenNames[cppTokenTypeCount + 1] = {
		"ControlWord",
		"TypeDef",
		"KeyWord",
		"Identifier",
		"Blank",
		"OpenBrace",
		"CloseBrace",
		"BeginLoop",
		"EndLoop",
		"BeginClass",
		"EndClass",
		"BeginIf",
		"EndIf",
		"BeginFcn",
		"EndFcn",
		"Namespace::",
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
		"ErrorType!!"
	};


	Lexer::Lexer(){
		if (matchersOKflag) return;
		matchersOKflag++;
	 	cppTokenMatchers[ControlWord].setPattern(string("if+else+while+for+class")); // Control words
		cppTokenMatchers[TypeDef].setPattern(string("int+float+double+long(@b+@n+@t)!double+long(@b+@n+@t)!long+unsigned(@b+@n+@t)!int+void"));
	 	cppTokenMatchers[KeyWord].setPattern(string("return+break+continue+const+constptr+virtual+public+private+true+false+friend")); // KeyWord
		cppTokenMatchers[Identifier].setPattern(string("([a-z]+[A-Z]+_)([a-z]+[A-Z]+[0-9]+_)*")); // Identifier
		cppTokenMatchers[Blank].setPattern(string("(@b+@t+@n)!"));
		cppTokenMatchers[OpenBrace].setPattern(string("{"));
		cppTokenMatchers[CloseBrace].setPattern(string("}")); //Brace
		cppTokenMatchers[BeginLoop].setPattern(string("{"));
		cppTokenMatchers[EndLoop].setPattern(string("}")); //Loop
		cppTokenMatchers[BeginClass].setPattern(string("{"));
		cppTokenMatchers[EndClass].setPattern(string("}")); // Class
		cppTokenMatchers[BeginIf].setPattern(string("{"));
		cppTokenMatchers[EndIf].setPattern(string("}")); // If
		cppTokenMatchers[BeginFcn].setPattern(string("{"));
		cppTokenMatchers[EndFcn].setPattern(string("}")); // Fcn
		cppTokenMatchers[Namespace].setPattern(string("::")); // Namespace
		cppTokenMatchers[Operator].setPattern(string("@++@*+@?+@/+->+-+:+%+&&+&+||+|+^")); // Operator
		cppTokenMatchers[Number].setPattern(string("0+[1-9][0-9]*((e+E)[0-9]!)?(l?+(ll)?+L?+(LL)?+(ld)?+(LD)?+f?+F?)+[0-9]*.[0-9]*((e+E)[0-9]!)?f?"));
		cppTokenMatchers[String].setPattern(string("\"[\"]*\"+'[']*'"));
		cppTokenMatchers[Assignment].setPattern(string("=+@+=+-=+@*=+@/=+%=")); // Assignment
		cppTokenMatchers[OpenBracket].setPattern(string("["));
		cppTokenMatchers[CloseBracket].setPattern(string("]"));
		cppTokenMatchers[OpenParentheses].setPattern(string("("));
		cppTokenMatchers[CloseParentheses].setPattern(string(")"));
		cppTokenMatchers[Semicolon].setPattern(string(";"));
		cppTokenMatchers[Comma].setPattern(string(","));
	#ifdef DEBUG
		fprintf(stderr, "Build Successfully!\n");
	#endif
	}
	void Lexer::Register(const char *source){
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

	int Lexer::finish() const {
		return position == str.length();
	}
}