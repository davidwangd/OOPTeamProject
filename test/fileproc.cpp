// coder : gaoj

#define DEBUG
#include "../utils/FileEnumerator.cpp"
#include "../FileProcessor.cpp"
#include <iostream>
using namespace std;

int main()
{
    FileProcessor fp;
	auto z = fp.process("test_project");
	cout << z << endl;
	return 0;
}
