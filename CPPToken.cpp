// coder : davidwang
#include "CPPToken.h"
#include <memory.h>
using namespace std;
using namespace CPPLanguage;

int CPPToken::MaxId = -1;

vector<const Token *> CPPTokenizer::process(const char *source){
	lexer.Register(source);

	while (!lexer.finish()){
		auto ret = lexer.GetNextToken();
		// for Blank, We simply Drop them
		if (ret.first == Blank){
			continue;
		}

		Stack.push(ret);

		// clear () and all the information init
		if (ret.first == CloseParentheses){
			int flag = 0;
			while (Stack.top().first != OpenParentheses){
				Stack.pop();
			}
			Stack.pop();
		}

		// clear [] and all the information init
		if (ret.first == CloseBracket){
			while (Stack.top().first != OpenBracket){
				Stack.pop();
			}
			Stack.pop();
		}

		// for identifiers
		// we discuss whether the first time or not
		if (ret.first == Identifier){
			map<string, int>::iterator it = id2int.find(ret.second);
			
			// updo the pushback/..
			Stack.pop();

			// first declared..
			if (it == id2int.end()){
				int ptr = 0;
				id2int.insert(make_pair(ret.second, cntId++));
				// Not Identifier, KeyWord, TypeDef and ControlWords..
				while (Stack.top().first > Blank){

					if (ptr >= 0 && Stack.top().second == "*") ptr++;
					else{
						ptr = -1;
					}
					if (Stack.top().first == Namespace){
						Stack.pop(); Stack.pop();
					}else{
						Stack.pop();
					}
				}
				string t;
				if (Stack.top().first == TypeDef){
					t = Stack.top().second;
				}else if (Stack.top().second == "class" || Stack.top().second == "struct"){
					// class Name
					t = string("typename");
				}else if (Stack.top().second == "namespace"){
					t = string("namespace");
				}else if (Stack.top().first == Identifier){
					// Identifier, this means that its a class type
					t = to_string(id2int[Stack.top().second]);
				}
				t = t + " ptr" + to_string(ptr) + "ptr";

				while (lexer.LookAhead().first == Blank) lexer.GetNextToken();
				auto nextToken = lexer.LookAhead();
				// function checker...
				if (nextToken.first == OpenParentheses){
					t = t + " fcn";
				}else{
					t = t + " ins";
				}
				idType.push_back(t);
			}	
			else // previous declared here
			{
				// Seem nothing to do currently
			}

			tokens.push_back(new CPPToken(ret, idType[id2int[ret.second]], id2int[ret.second]));
			// Because we have pushed the identifier already 
			continue;
		}

		if (ret.first == CloseBrace){
			while (Stack.top().second != "{") Stack.pop();
			// to the current CloseType.... 
			ret.first = (TokenType)((int)Stack.top().first + 1);
			Stack.pop();
			continue;
		}

		if (ret.first == OpenBrace){
			while (!Stack.empty() && Stack.top().first >= Blank || Stack.top().first == KeyWord) Stack.pop();

			// for none usage- OpenBrace..
			if (Stack.empty()) continue;

			// Begin End for Control words...
			if (Stack.top().first == ControlWord){
				if (Stack.top().second == "if" || Stack.top().second == "switch" || Stack.top().second == "else") ret.first = BeginIf;
				if (Stack.top().second == "for" || Stack.top().second == "do" || Stack.top().second == "while") ret.first = BeginLoop;
				Stack.pop();
				continue;
			}

			// For Identifier..
			if (Stack.top().first == Identifier){
				char buff1[20], buff2[20], buff3[20];

				memset(buff1, 0, sizeof(buff1));
				memset(buff2, 0, sizeof(buff2));
				memset(buff3, 0, sizeof(buff3));
				
				sscanf(idType[id2int[Stack.top().second]].c_str(), "%s%s%s", buff1, buff2, buff3);
				if (!strcmp(buff1, "typename")){
					ret.first = BeginClass;
				}else if (!strcmp(buff3, "fcn")){
					ret.first = BeginFcn;
				}
			}

			if (Stack.top().second == "namespace"){
				ret.first = BeginNamespace;
			}
		}

		tokens.push_back(new CPPToken(ret));
	}
	return tokens;
}