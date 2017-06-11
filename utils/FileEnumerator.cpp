// coder : gaoj

#include "../utils/FileEnumerator.h"
#include <cstring>
#include <io.h>

using namespace std;

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
		return vector<string>();
	do
	{
		if (fileInfo.attrib & _A_SUBDIR)   //这是一个文件夹，跳过
			continue;
		res.emplace_back(fileInfo.name);
	}while (_findnext(hFile, &fileInfo) == 0);
    _findclose(hFile);
	return res;
}
vector<string> GetSources(const char* pathname, const string Attribs[], int Count)
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
	string StrPath(path);
	for (int i = 0; i < Count; ++i)
	{
		auto res = GetCertainAttribute(path, Attribs[i].c_str());
		for (string FileName : res)
			sources.push_back(StrPath + FileName);
	}
	return sources;
}
