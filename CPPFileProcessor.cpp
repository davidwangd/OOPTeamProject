// coder : gaoj

#include "CPPFileProcessor.h"
#include "utils/dependency.h"
#include "utils/FileEnumerator.h"

#include <ctime>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <map>
#include <cstring>
#include <cctype>

using namespace std;

const int FileNameLength = 8;
const string _Attribs[] = {".cpp", ".cxx", ".c", ".cc", ".h", ".hpp", ".hxx"};
const int _AttribsCount = 7;

string RandomFileName()
{
	char selection[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789abcdefghijklmnopqrstuvwxyz";
	int len = strlen(selection);
	srand(time(NULL));

	string res;
	for (int i = 0; i < FileNameLength; ++i)
		res += selection[rand() % len];
	res += ".tmp.cpp";
	return res;
}

string GetTypedefined(string& src)
{
    string t = Trim(src.substr(7));
    t = t.substr(0, t.size() - 1);
    int len = t.size();

    //处理中括号
    int last = len, depth = 0;
    for (int i = len - 1; i >= 0; --i)
	{
		if (t[i] == ']')
            ++depth;
		if (t[i] == '[')
		{
			--depth;
			if (depth == 0)
				last = i;
		}
	}
	t = t.substr(0, last);

	//处理大括号，目的是搞掉typedef struct
    last = len, depth = 0;
    for (int i = len - 1; i >= 0; --i)
	{
		if (t[i] == '}')
            ++depth;
		if (t[i] == '{')
		{
			--depth;
			if (depth == 0)
				last = i;
		}
	}
	t = t.substr(0, last);

	//处理一层小括号，目的是搞掉函数指针
	last = len, depth = 0;
    for (int i = len - 1; i >= 0; --i)
	{
		if (t[i] == ')')
            ++depth;
		if (t[i] == '(')
		{
			--depth;
			if (depth == 0)
			{
				last = i;
				break;
			}
		}
	}
	t = t.substr(0, last);

	//清除所有特殊符号
	string processed("");
	for (char c : t)
		if (c == ' ' || !ispunct(c))
			processed += c;
	processed = Trim(processed);
	len = processed.size();

	for (last = len - 1; last >= 0; --last)
		if (processed[last] == ' ')
			break;
	return processed.substr(last + 1);
}

string DeleteTypedefs(string& source, string& Typedefs)
{
	map<string, bool> existed;
	Typedefs = "";
	string res;
	int len = source.size();
	for (int i = 0, j; i < len; ++i)
		if (source.substr(i, 7) != "typedef")
			res += source[i];
		else
		{
			string cmd;
			int depth = 0;
			for (j = i; j < len; ++j)
			{
				char w = source[j];
				if (w != '\n')
					cmd += source[j];
				if (w == '{') ++depth;
				if (w == '}') --depth;
				if (w == ';' && !depth)
					break;
			}
			string NewType = GetTypedefined(cmd);
			if (!existed[NewType])
			{
				Typedefs += NewType;
				Typedefs += '+';
				existed[NewType] = true;
			}
			i = j;
		}
	Typedefs = Typedefs.substr(0, Typedefs.size() - 1);

#ifdef DEBUG
	ofstream _fout("Processed.cxx");
	_fout << res;
	_fout.close();
#endif

	return res;
}

const char* CPPFileProcessor::process(const char* pathname)
{
	auto FileList = GetSources(pathname, _Attribs, _AttribsCount);
	auto TmpFile = RandomFileName();

	FileDependencyGraph dg;
	for (string FileName : FileList)
		dg.AddFile(FileName);
	dg.BuildGraph();
	dg.MergeAll(TmpFile.c_str());

	string _Command = "g++ -E " + TmpFile;
	FILE* proc = popen(_Command.c_str(), "r");

	char buf[2048] = {0};
	string Processed;
	while (fgets(buf, 2048, proc) != NULL)
		if (buf[0] != '\n' && buf[0] != '#')
			Processed = Processed + buf;
	pclose(proc);
	remove(TmpFile.c_str());

	Processed = DeleteTypedefs(Processed, TypedefRegEx);
	Strings.push_back(Processed);
	return Strings[Strings.size() - 1].c_str();
}
