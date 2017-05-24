// coder : gaoj

#define DEBUG
#include "../utils/dependency.cpp"

int main()
{
	FileDependencyGraph gr;

	gr.AddFile("test_project/testmain.cpp");
	gr.AddFile("test_project/testincl0.hpp");
	gr.AddFile("test_project/testincl1.h");
	gr.AddFile("test_project/testincl2.h");

	gr.BuildGraph();
	gr.MergeAll("test_project/testmain.cxx");
	return 0;
}
