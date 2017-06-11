#ifndef OOP_TEAMWORK_FILEPROCESSOR_H
#define OOP_TEAMWORK_FILEPROCESSOR_H

// coder : davidwang & gaoj

#include <vector>
#include <string>

enum Language{
	CPP,
	Java,
	Python,
	LangugeCount
};

class FileProcessor{
public:
	/// 注册一个FileProcessor必须提供一个语言。
	FileProcessor() { }
	/// 释放所有产生的内存。
	virtual ~FileProcessor() { }
	/// 处理一个文件目录下的所有语言认可的文件并合成一个c风格的字符串
	/// 该类将持有所有process产生的字符串，函数析构的时候释放所有。
	/// 可能会被调用多次。
	virtual const char *process(const char *pathname);
	virtual Language GetLanguage() const { return LangugeCount; }

protected:
	// Strings管理类实例持有的所有字符串。注意这字符串使用了std::string而非C风格的。
	// process通过c_str获取指向C风格字符串的指针，并将之返回给用户。
	std::vector<std::string> Strings;
};

#endif /* end of include guard: OOP_TEAMWORK_FILEPROCESSOR_H */
