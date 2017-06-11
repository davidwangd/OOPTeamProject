// coder : gaoj

#include "FileProcessor.h"
#include "utils/FileEnumerator.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <ctime>
#include <cstdlib>

using namespace std;

const string _AllAttrib[] = { "" };
const int _AllAttribCount = 1;

const char* FileProcessor::process(const char *pathname)
{
	auto FileList = GetSources(pathname, _AllAttrib, _AllAttribCount);

	// 随机化文件连接的顺序
	srand(time(0));
	random_shuffle(FileList.begin(), FileList.end());
	
	string res;
	for (string& file : FileList)
	{
		ifstream fin(file);
		stringstream ss;
		ss << fin.rdbuf();
		fin.close();
		res += ss.str();
		res += '\n';
	}
	Strings.push_back(res);
	return Strings[Strings.size() - 1].c_str();
}
