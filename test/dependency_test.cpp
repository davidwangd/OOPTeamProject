// coder : gaoj

#define DEBUG
#include "../utils/dependency.cpp"
#include "../CPPFileProcessor.cpp"
#include <iostream>
using namespace std;

int main()
{
	CPPFileProcessor cfp;
	auto z = cfp.process("test_project");
	cout << z << endl;
	return 0;
}
