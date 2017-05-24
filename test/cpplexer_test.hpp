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
			if (!isalpha(s[r])){
				ret.start -> trans[s[l+1]] = ret.end;
			}else{
				if (s[r] == 't') ret.start -> trans['\t'] = ret.end;
				else if (s[r] == 'n') ret.start -> trans['\n'] = ret.end;
				else if (s[r] == 'b') ret.start -> trans[' '] = ret.end;
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
				ret.Link(cur);
				ret.Union(build(s, i+1, r));
				i = r;
				return ret;
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