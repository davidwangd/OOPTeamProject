// coder : gaoj

#define DEBUG
#include "../utils/dependency.cpp"

int main()
{
	FileDependencyGraph gr;
	gr.AddFile("E:/Classes & Homework/1-2/OOP/Team Project/OOPTeamProject/test/test_project/testmain.cpp");
	gr.AddFile("E:/Classes & Homework/1-2/OOP/Team Project/OOPTeamProject/test/test_project/testincl0.hpp");
	gr.AddFile("E:/Classes & Homework/1-2/OOP/Team Project/OOPTeamProject/test/test_project/testincl1.h");
	gr.AddFile("E:/Classes & Homework/1-2/OOP/Team Project/OOPTeamProject/test/test_project/testincl2.h");
	gr.BuildGraph();
	gr.PrintGraph();
	return 0;
}
