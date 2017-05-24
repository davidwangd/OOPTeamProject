// coder : gaoj

#include "CPPFileProcessor.h"
#include "utils/dependency.h"

#include <ctime>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <io.h>
#include <cstring>

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

vector<string> GetCertainAttribute(const char* pathname, const char* attrib)
{
	vector<string> res;
	char path[512] = {0};

	strcpy(path, pathname);
	strcat(path, "*");
	strcat(path, attrib);

	long hFile = 0;
	_finddata_t fileInfo;
	if ((hFile = _findfirst(path, &fileInfo)) == -1)
		return;
	do
	{
		if (fileInfo.attrib & _A_SUBDIR)   //这是一个文件夹，跳过
			continue;
		res.emplace_back(fileInfo.name);
	}while (_findnext(hFile, &fileInfo) == 0);
    _findclose(hFile);
	return res;
}
vector<string> GetCPPSources(const char* pathname)
{
	vector<string> sources;
	char path[512] = {0};

	strcpy(path, pathname);
	int len = strlen(path);
	for (int i = 0; i < len; ++i)
		if (path[i] == '\\')
			path[i] = '/';
	if (path[strlen(path) - 1] != '/')
		strcat(path, "/");
	for (int i = 0; i < _AttribsCount; ++i)
	{
		auto res = GetCertainAttribute(path, _Attribs[i].c_str());
		for (string FileName : res)
			sources.push_back(FileName);
	}
	return sources;
}

const char* CPPFileProcessor::process(const char* pathname)
{
	auto FileList = GetCPPSources(pathname);
	auto TmpFile = RandomFileName();

	FileDependencyGraph dg;
	for (string FileName : FileList)
		dg.AddFile(FileName);
	dg.BuildGraph();
	dg.MergeAll(TmpFile);
	return NULL;
}
