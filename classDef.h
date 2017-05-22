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
	Language GetLanguage() const;
};

class CPPfileProcessor: public FileProcessor{

};

class Token{
	// 检测Token是否相同
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
	void process(const char *source);
	// 获得Tokens
	virtual vector<Token*> GetTokens() const;
	Language GetLanguage() const;
};

class CPPtokenizer : public Tokenizer{

};

// 这是一个语言无关类，只考虑处理封装好的Tokens.
class Analyser{
	Analyser();
	// 检验两个Token列表， 返回抄袭可能性
	// 实现见Papar..
	double check(const vector<Token *>&, const vector<Token *>&);
};

// 一个 Dectectory
class PlagiarismDetector{
	PlagiarismDector(Language lan);
	double check(const char *path1, const char *path2);
	map<pair<int, int>, double> check(const char *paths[]);
};

// 使用以上所有类。。最后实现。。。。
class CPPPlagiarismDetector : public PlagiarismDector{

};