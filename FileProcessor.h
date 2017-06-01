#ifndef OOP_TEAMWORK_FILEPROCESSOR_H
#define OOP_TEAMWORK_FILEPROCESSOR_H

// coder : davidwang & gaoj

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
	virtual const char *process(const char *pathname) = 0;
	virtual Language GetLanguage() const = 0;
};

#endif /* end of include guard: OOP_TEAMWORK_FILEPROCESSOR_H */
