#ifndef OOP_TEAMWORK_CLASSDEF_H
#define OOP_TEAMWORK_CLASSDEF_H

// A enumerate type of language
enum Language{
	CPP,
	Java,
	Python,
	LangugeCount
};

class FileProcessor{
public:
	// 注册一个FileProcessor必须提供一个语言
	FileProcessor();
	// 释放所有产生的内存
	virtual ~FileProcessor();
	// 处理一个文件目录下的所有语言认可的文件并合成一个c风格的字符串
	// 该类将持有所有process产生的字符串，函数析构的时候释放所有。
	// 可能会被调用多次。。
	virtual const char *process(const char *pathname) = 0;
	virtual Language GetLanguage() const;
};

class CPPfileProcessor final: public FileProcessor{
public:
	CPPfileProcessor();
	~CPPfileProcessor();
	const char *process(const char *pathname);
	Language GetLanguage() const { return CPP; }

private:
	//TODO
};

class Token{
	// 检测Token是否相同
	virtual ~Token();
	virtual int ApproximateEqual(const Token *other) const;
	virtual int Equal(const Token *other) const;
	// 返回一个可以用于hash的值
	// 如果Equal Value就相同
	// 如果ApproximateEqual, ApproximateValue就相同。
	// 这里是用来帮助hash的
	virtual int Value() const;
	virtual int ApproximateValue() const;
	Language GetLanguage() const;
};
class Tokenizer{
	Tokenizer();
	// 处理经过FileProccessor处理过的源代码
	virtual vector<const Token*> process(const char *source);
	// 获得Tokens
	virtual vector<const Token*> GetTokens() const;	
	// 从 FileProcessor中获得字符串的信息。 value是该类定义的 InfoType中的信息。 -1 表示不会处理更多的信息
	virtual int ProcessorInfo(const std::string &info, int valueType = -1);
	Language GetLanguage() const;
};

class CPPTokenizer : public Tokenizer{

};

class CPPToken : public Token{

};

// 这是一个语言无关类，只考虑处理封装好的Tokens.
class Analyser{
	Analyser();
	// 检验两个Token列表， 返回抄袭可能性
	// 实现见Paper..
	double check(const std::vector<Token *>&, const std::vector<Token *>&);
};

// 一个 Detector
class PlagiarismDetector{
	PlagiarismDector(Language lan);
	double check(const char *path1, const char *path2);
	std::map<std::pair<int, int>, double> check(const char *paths[]);
};

// 使用以上所有类。。最后实现。。。。
class CPPPlagiarismDetector : public PlagiarismDector{

};

#endif /* end of include guard: OOP_TEAMWORK_CLASSDEF_H */

class AClassName{
public:
	AClassName(){}
	int i;
	virtual void func(int i, int j) const;
private:
	static int cnt;
	void *data;
};