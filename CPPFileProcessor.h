#ifndef OOP_TEAMWORK_CPPFILEPROCESSOR_H
#define OOP_TEAMWORK_CPPFILEPROCESSOR_H

// coder : gaoj

#include "../classDef.h"

#include <set>
#include <vector>
#include <string>

/// 这是用于处理C++源代码的Processor类
class CPPFileProcessor{
public:
	/// 默认构造函数对类进行初始化，实际上不进行任何操作。
    CPPfileProcessor() { }
	/// 析构函数实际上不进行任何操作。
    ~CPPfileProcessor() { }
	/// process函数处理指定目录下的所有C++源文件，并将它们合并为一个C风格字符串。
	/// @param pathname 用户指定的路径。
	/// @return 返回指向由类实例持有的C风格字符串的一个指针。
    const char* process(const char* pathname);
	/// GetLanguage返回枚举类型常量CPP。
	Language GetLanguage() const { return CPP; }

private:
	// Strings管理类实例持有的所有字符串。注意这字符串使用了std::string而非C风格的。
	// process通过c_str获取指向C风格字符串的指针，并将之返回给用户。
	std::set<std::string> Strings;
};

#endif /* end of include guard: OOP_TEAMWORK_CPPFILEPROCESSOR_H */
