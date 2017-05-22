// coder : davidwang

#include "../utils/regex.h"

#include <queue>
#include <deque>
#include <cctype>

using namespace std;

namespace Regex{
	map<set<NFANode *>, DFANode*> nfa2dfa;
	map<DFANode*, set<NFANode *>> dfa2nfa;
	const char TransCharacter = '@';
	const char alphabeta[] = "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM0123456789[]{}!@#$%^&*()_+-=;':\"\\\n\t/?.,`~|<> ";
	const int errorCode = -1;
	int NFANode::Count = 0;
	int DFANode::Count = 0;

	NFANode::NFANode(int accept){
		this -> accept = accept;
		this -> id = Count++;
	}

	DFANode::DFANode(int accept){
		this -> accept = accept;
		this -> id = Count++;
	}

	NFANode *nullnfa = new NFANode(-1);
	DFANode *nulldfa = new DFANode(-1);

	// for * operation
	NFA& NFA::Iteration(){
		NFANode *st = new NFANode(0);
		NFANode *nd = new NFANode(1);
		end -> accept = 0;
		end -> insertEtrans(st);
		end -> insertEtrans(nd);
		st -> insertEtrans(start);
		st -> insertEtrans(nd);
		start = st;
		end = nd;
		return *this;
	}

	NFA& NFA::Optional(){
		start -> insertEtrans(end);
		return *this;
	}

	NFA& NFA::Addition(){
		NFANode *st = new NFANode(0);
		NFANode *nd = new NFANode(1);
		end -> accept = 0;
		end -> insertEtrans(st);
		end -> insertEtrans(nd);
		st -> insertEtrans(start);
		start = st;
		end = nd;
		return *this;
	}

	// 运算等级  () > *!? > link > +
	NFA& NFA::Link(NFA &other){
		if (start != nullnfa){
			if (other.start != nullnfa){
				end -> accept = 0;
				end -> insertEtrans(other.start);
				end = other.end;
			}
		}
		else
		{
			*this = other;
		}
		return *this;
	}

	NFA& NFA::Union(NFA other){
		NFANode *st = new NFANode(0);
		NFANode *nd = new NFANode(1);
		end -> accept = other.end -> accept = 0;
		st -> insertEtrans(start);
		st -> insertEtrans(other.start);
		end -> insertEtrans(nd);
		other.end -> insertEtrans(nd);
		start = st;
		end = nd;
	}

	NFA::NFA(){
		start = end = nullnfa;
	}

	DFA::DFA(){
		start = nulldfa;
	}

	NFA build(const string &s, int l, int r){
		NFA ret, cur, pre;
		if (r - l + 1 == 1){
			ret.start = new NFANode(0);
			ret.end = new NFANode(1);
			ret.start -> trans[s[l]] = ret.end;
			return ret;
		}
		if (r-l+1 == 2 && s[l] == TransCharacter){
			ret.start = new NFANode(0);
			ret.end = new NFANode(1);
			if (!isalpha(s[l])){
				ret.start -> trans[s[l+1]] = ret.end;
			}else{
				if (s[l] == 't') ret.start -> trans['\t'] = ret.end;
				else if (s[l] == 'n') ret.start -> trans['\n'] = ret.end;
				else if (s[l] == 'b') ret.start -> trans[' '] = ret.end;
			}
			return ret;
		}
		if (r-l+1==3 && s[l]=='[' && s[l+2]==']'){
			ret.start = new NFANode(0);
			ret.end = new NFANode(1);
			for (auto &c:alphabeta){
				if (s[l+1] != '-' && s[l+1] != TransCharacter && c == s[l+1]) continue;
				ret.start -> trans[c] = ret.end;
			}
			return ret;
		}
		if (r-l+1 == 5 && s[l] == '[' && s[l+2] == '-' && s[l+4] == ']'){
			ret.start = new NFANode(0);
			ret.end = new NFANode(1);
			for (char c = s[l+1]; c <= s[l+3];c++){
				ret.start -> trans[c] = ret.end;
			}
			return ret;
		}

		for (int i = l;i <= r;i++){

			if (s[i] == TransCharacter){
				ret.Link(cur);
				cur = build(s, i, i+1);
				i++;
				continue;
			}

			if (s[i] == '['){
				ret.Link(cur);
				if (s[i+2] == ']') cur = build(s, i, i+2), i+=2;
				if (s[i+4] == ']') cur = build(s, i, i+4), i+=4;
				continue;
			}

			if (s[i] == '('){
				ret.Link(cur);
				int num = 1;
				for (int j = i+1;j<=r;j++){
					if (s[j] == '(' && (j==0 || s[j-1] != TransCharacter)) num ++;
					if (s[j] == ')' && (j==0 || s[j-1] != TransCharacter)) num --;
					if (num == 0){
						cur = build(s,i+1,j-1);
						i = j;
						break;
					}
				}
				continue;
			}

			if (s[i] == '*'){
				cur.Iteration();
				continue;
			}

			if (s[i] == '!'){
				cur.Addition();
				continue;
			}

			if (s[i] == '?'){
				cur.Optional();
				continue;
			}

			if (s[i] == '+'){
				cur.Union(build(s, i+1, r));
				i = r;
				continue;
			}else{
				ret.Link(cur);
				cur = build(s, i, i);
			}
		}
		ret.Link(cur);
		return ret;
	}

	std::set<NFANode*> e_clos(std::set<NFANode*>s) {
		std::set<NFANode *> ret;
		std::queue<NFANode *> q;
		ret.clear(); 
		for (auto x:s) q.push(x),ret.insert(x);
		while (!q.empty()){
			NFANode *x = q.front(); q.pop();
			for (auto tr : x -> e_trans){
				if (!ret.count(tr)){
					ret.insert(tr);
					q.push(tr);
				}
			}
		}
		return ret;
	}
	
	// epsilon closure of an NFA node
	inline std::set<NFANode*> e_clos(NFANode *x){
		std::set<NFANode*>s;
		s.clear(); s.insert(x);
		return e_clos(s);
	}
	
	// NFA nodes transation using given character
	std::set<NFANode*> Trans(std::set<NFANode*>s,char c){
		std::set<NFANode*> ret;
		ret.clear();
		for (auto x:s){
			if (x->trans.find(c) != x->trans.end())
				ret.insert(x->trans[c]);
		}
		return ret;
	}
	
	// return a DFA node standing for given set of NFA nodes
	DFANode* DfaNode(std::set<NFANode*> s){
		auto last = nfa2dfa.find(s);
		if (last != nfa2dfa.end()) return last -> second;
		else{
			int accept = 0;
			for (auto x : s){
				accept |= x -> accept;
			}
			DFANode *now = new DFANode(accept);
			nfa2dfa[s] = now;
			dfa2nfa[now] = s;
			return now;
		}
	}
	
	DFA::DFA(NFA &nfa){
		std::set<DFANode*>visit;
		std::queue<DFANode*>q;
		start = DfaNode(e_clos(nfa.start));
		q.push(start);
		while (!q.empty()){
			DFANode *now = q.front(); q.pop();
			for (auto c : alphabeta){
				std::set<NFANode*> cur = Trans(dfa2nfa[now],c);
				if (!cur.empty()){
					DFANode *a = DfaNode(e_clos(cur));
					now->trans[c]=a;
					if (!visit.count(a)){
						q.push(a);
						visit.insert(a);
					}
				}
			}
		}
	}
	
	int DFA::match(const std::string &s){
		DFANode *now = start;
		for (int i = 0;i < s.length();i++){
			if (now->trans.find(s[i]) == now->trans.end()) return 0;
			now = now -> trans[s[i]];
		}
		return now->accept;
	}
	
	int DFA::match(const std::string &s,int l,int r){
		DFANode *now = start;
		int pre = -1;
		for (int i = l;i < r || (r == -1 && i < s.length());i++){
			if (now->trans.find(s[i]) == now -> trans.end()) return pre;
			now = now -> trans[s[i]];
			if (now -> accept) pre = i;
		}
		return now->accept;
	}	

	void NFA::clearMem(){
		queue<NFANode *> q;
		set<NFANode *> s;
		q.push(this -> start);
		s.insert(this -> start);
		while (!q.empty()){
			NFANode *cur = q.front();
			q.pop();
			for (auto &trans : cur -> trans){
				if (!s.count(trans.second)){
					s.insert(trans.second);
					q.push(trans.second);
				}
			}
			for (auto &trans : cur -> e_trans){
				if (!s.count(trans)){
					s.insert(trans);
					q.push(trans);
				}
			}
		}
		for (auto node: s){
			delete node;
		}
		start = end = nullnfa;
	}

	void DFA::clearMem(){
		queue<DFANode *> q;
		set<DFANode *> s;
		q.push(this -> start);
		s.insert(this -> start);
		while (!q.empty()){
			DFANode *cur = q.front();
			q.pop();
			for (auto &trans : cur -> trans){
				if (!s.count(trans.second)){
					s.insert(trans.second);
					q.push(trans.second);
				}
			}
		}
		for (auto node: s){
			delete node;
		}
		start = nulldfa;
	}
	
	RE::RE(const std::string &s){
		orin = s;
		nfa = build(s,0,s.length() - 1);
	#ifdef DEBUG
		nfa.show();
	#endif
		dfa = DFA(nfa);
	#ifdef DEBUG
		dfa.show();
	#endif
		nfa2dfa.clear();
		dfa2nfa.clear();
	}

	RE::~RE(){
		dfa.clearMem();
	}

#ifdef DEBUG
	void NFA::show(){
		printf("Start: %d End %d\n",start -> id,end -> id);
		std::queue<NFANode*> q;
		std::set<NFANode*> visit;
		q.push(start); visit.insert(start);
		while (!q.empty()){
			NFANode *now = q.front(); q.pop();
			printf("{ID:%d(%d) e_trans:[ ",now -> id,now->accept);
			for (auto x:now->e_trans){
				printf(" %d,",x -> id);
				if (!visit.count(x)) q.push(x),visit.insert(x);
			}
			printf("] trans:[");
			for (auto x:now->trans){
				printf(" %c:%d,",x.first,x.second -> id);
				if (!visit.count(x.second)) q.push(x.second),visit.insert(x.second);
			}
			printf("] }\n");
		}
		printf("\n");
	}

	void DFA::show(){
		printf("Start: %d ",start -> id);
		std::queue<DFANode*> q;
		std::set<DFANode*> visit;
		q.push(start); visit.insert(start);
		while (!q.empty()){
			DFANode *now = q.front(); q.pop();
			printf("{ID:%d(%d) trans:[ ",now -> id,now->accept);
			for (auto x:now->trans){
				printf(" %c:%d,",x.first,x.second -> id);
				if (!visit.count(x.second)) q.push(x.second),visit.insert(x.second);
			}
			printf("] }\n");
		}
		printf("\n");
	}
#endif
}