#ifndef OOP_TEAMPROJECT_UTILS_REGEX_H
#define OOP_TEAMPROJECT_UTILS_REGEX_H

// coder : davidwang
/*
这是一个用于辅助Tokenizer的类，是一个实现简单正则表达式的类
*/

#include <cstdio>
#include <set>
#include <map>
#include <vector>
#include <string>

namespace Regex{
	
	class NFANode{
	public:
		NFANode(int accept = 0);
		int accept, id;
		static int Count;
		std::vector<NFANode *> e_trans;
		std::map<char, NFANode*> trans;
		void insertEtrans(NFANode *node){ e_trans.push_back(node); }	
	};
	
	class NFA{
	public:
		NFA();
		// using a regular expression for the nfa build
		NFA(const std::string &s);
		// Not used when the destructor is called.
		// but when is mannually called
		void clearMem();
		NFANode *start, *end;
		NFA& Iteration(); // for *
		NFA& Addition();  // for !
		NFA& Optional();  // for ?
		NFA& Union(NFA other); // for +
		NFA& Link(NFA& other); // link
	#ifdef DEBUG
		void show();
	#endif
	};

	class DFANode{
	public:
		DFANode(int accept = 0);
		int accept, id;
		static int Count;
		std::map<char, DFANode *> trans;
	};

	class DFA{
	public:
		DFANode *start;
		int match(const std::string &s);
		// 返回从l开始的最长匹配长度， r = -1 表示右端点为字符串末尾
		int match(const std::string &s,int l,int r = -1);
		DFA();
		DFA(NFA& nfa);
		void clearMem();
	#ifdef DEBUG
		void show();
	#endif
	};

	class RE{	
	public:
		RE(const std::string &s);
		~RE();
		int match(const std::string &s){ return dfa.match(s); }
		int match(const std::string &s,int l, int r = -1){ return dfa.match(s,l,r); }
	private:
		std::string orin;
		DFA dfa;
		NFA nfa;
	};
}

#endif // OOP_TEAMPROJECT_UTILS_REGEX_H