// coder : gaoj

#include "../utils/dependency.h"
#include "../utils/FileEnumerator.h"
#include <sstream>
#include <queue>
#include <algorithm>
#include <cstdio>
#include <iostream>

using namespace std;

void FileDependencyGraph::AddFile(const string& FileName)
{
	FileNodes.push_back(FileName);
}
void FileDependencyGraph::AddFile(const char* FileName)
{
	FileNodes.push_back(string(FileName));
}

void FileDependencyGraph::BuildGraph()
{
	int n = FileNodes.size();
	Dependency.resize(n);
	InDeg.assign(n, 0);

	for (int i = 0; i < n; ++i)
	{
		ifstream fin(FileNodes[i]);
		string tmp, buf;
		int j = 0, len = FileNodes[i].size();
		for (; j < len; ++j)
			if (FileNodes[i][len - j - 1] == '/')
				break;
		string Directory = FileNodes[i].substr(0, len - j);

		int Line = 0;
		while (fin)
		{
			getline(fin, buf);
			++Line;
			if (!fin)
				break;
			buf = Trim(buf);
			if (buf.substr(0, 8) == "#include")
			{
				tmp = Trim(buf.substr(8));
				tmp = Trim(tmp.substr(1, tmp.size() - 2));
				// 不考虑存在子目录的情况
				string Depend = Directory + tmp;
				for (j = 0; j < FileNodes.size(); ++j)
					if (FileNodes[j] == Depend)
						break;
				if (j != FileNodes.size())
					AddEdge(i, j, Line);
			}
		}
		fin.close();
	}
}

void FileDependencyGraph::Extend(ofstream& os, int v)
{
	ifstream fin(FileNodes[v]);
	string buf, tmp;

	int Line = 0, i = 0, n = Dependency[v].size();
	while (fin)
	{
		getline(fin, buf);
		buf = Trim(buf);
		++Line;
		if (!fin)
			break;
		if (i < n)
			if (Dependency[v][i].LineNo == Line)
			{
				Extend(os, Dependency[v][i].To);
				++i;
				continue;
			}
		if (buf.substr(0, 8) != "#include")
			os << buf << endl;
	}
	fin.close();
}

void FileDependencyGraph::MergeAll(const char* StoreTo)
{
	ofstream fout(StoreTo);
	for (int i = 0; i < FileNodes.size(); ++i)
		if (InDeg[i] == 0)
			Extend(fout, i);
	fout.close();
}

#ifdef DEBUG

void FileDependencyGraph::PrintGraph()
{
	for (int i = 0; i < FileNodes.size(); ++i)
	{
		cerr << "File #" << i << ": " << FileNodes[i] << endl;
		for (Edge j : Dependency[i])
			cerr << " - (line "<< j.LineNo << ") depends on: " << FileNodes[j.To] << endl;
		cerr << endl;
	}
}
#endif
