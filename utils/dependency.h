#ifndef OOP_TEAMWORK_UTILS_DEPENDENCY_H
#define OOP_TEAMWORK_UTILS_DEPENDENCY_H

// coder : gaoj
/*
这个文件里面定义了一个用于处理用户代码依赖关系的类。
实际处理的时候，只展开依赖关系图中的文件。也就是说去掉标准库。
*/

#include <vector>
#include <string>

class FileDependencyGraph
{
public:
	FileDependencyGraph();
	void AddFile(const char* FileName);
	void ComputeDependencies(const char* FileName);
	std::vector<const FileNode*>::const_iterator begin() const {
		return Topological.begin();
	}
	std::vector<const FileNode*>::const_iterator end() const {
		return Topological.end();
	}

private:
	int NodeCount;
	std::vector<std::string> FileNodes;
	std::vector<std::vector<int> > Dependency;
	std::vector<int> InDeg;

	std::vector<const FileNode*> Topological;
};

#endif /* end of include guard: OOP_TEAMWORK_UTILS_DEPENDENCY_H */
