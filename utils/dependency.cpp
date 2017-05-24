// coder : gaoj

#include "../utils/dependency.h"
#include <fstream>
#include <sstream>
#include <queue>
#include <algorithm>

#include <iostream>

using namespace std;

void FileDependencyGraph::AddFile(const char* filename)
{
	FileNodes.push_back(string(filename));
}

void FileDependencyGraph::BuildGraph()
{
	int n = FileNodes.size();
	Dependency.resize(n);

	for (int i = 0; i < n; ++i)
	{
		ifstream fin(FileNodes[i]);
		string tmp, buf;
		int j = 0, len = FileNodes[i].size();
		for (; j < len; ++j)
			if (FileNodes[i][len - j - 1] == '/')
				break;
		string Directory = FileNodes[i].substr(0, len - j);
		while (fin)
		{
			getline(fin, buf);
			if (!fin)
				break;
			stringstream ss;
			ss << buf;
			ss >> tmp;
			if (tmp == "#include")
			{
				ss >> tmp;
				if (tmp[0] == '<' && tmp[tmp.size() - 1] == '>')
					continue;
				tmp = tmp.substr(1, tmp.size() - 2);
				// 不考虑存在子目录的情况
				string Depend = Directory + tmp;
				for (j = 0; j < FileNodes.size(); ++j)
					if (FileNodes[j] == Depend)
						break;
				if (j == FileNodes.size())
					throw "gaoj, dependency.cpp: unexpected error at BuildGraph";
				Dependency[i].push_back(j);
			}
		}
		fin.close();
	}
}

void FileDependencyGraph::ComputeDependencies(const char* filename)
{
	Topological.clear();

	string Target(filename);
	int v = 0, n = FileNodes.size();
	for (; v < n; ++v)
		if (FileNodes[v] == Target)
			break;
	if (v == n)
		throw "gaoj, dependency.cpp: unexpected error at ComputeDependencies";

	queue<int> Q;
	vector<bool> vis;
	vis.assign(n, false);
	Q.push(v);
	vis[v] = true;
	while (!Q.empty())
	{
		int u = Q.front();
		Q.pop();
		Topological.push_back(FileNodes[u]);

		for (int w : Dependency[u])
			if (!vis[w])
			{
				Q.push(w);
				vis[w] = true;
			}
	}
	reverse(Topological.begin(), Topological.end());
}

#ifdef DEBUG
void FileDependencyGraph::PrintGraph()
{
	for (int i = 0; i < FileNodes.size(); ++i)
	{
		cerr << "File #" << i << ": " << FileNodes[i] << endl;
		for (int j : Dependency[i])
			cerr << " - depends on: " << FileNodes[j] << endl;
		cerr << endl;
	}
}
#endif
