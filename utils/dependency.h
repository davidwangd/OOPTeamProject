#ifndef OOP_TEAMWORK_UTILS_DEPENDENCY_H
#define OOP_TEAMWORK_UTILS_DEPENDENCY_H

// coder : gaoj
/*
这个文件里面定义了一个用于处理用户代码依赖关系的类。
实际处理的时候，只展开依赖关系图中的文件。也就是说去掉标准库。
*/

#include <vector>
#include <string>
#include <fstream>

struct Edge
{
	int LineNo, To;
	Edge(int LineNo = -1, int To = -1) : LineNo(LineNo), To(To) { }
};

class FileDependencyGraph
{
public:
	FileDependencyGraph() { }
	void AddFile(const char* FileName);
	void BuildGraph();
	void MergeAll(const char* StoreTo);

#ifdef DEBUG
	void PrintGraph();
#endif

private:
	std::vector<std::string> FileNodes;
	std::vector<std::vector<Edge> > Dependency;
	std::vector<int> InDeg;

	void AddEdge(int u, int v, int Line)
	{
		Dependency[u].push_back(Edge(Line, v));
		++InDeg[v];
	}
	void Extend(std::ofstream& os, int v);
};

#endif /* end of include guard: OOP_TEAMWORK_UTILS_DEPENDENCY_H */
