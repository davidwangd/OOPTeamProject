#include "CPPDetector.h"
std::pair<double, double> CPPPlagiarismDetector::check(const char *path1, const char *path2){
	FileProcessor *processor1 = new CPPFileProcessor();
	FileProcessor *processor2 = new CPPFileProcessor();
	Tokenizer *tokenizer1 = new CPPTokenizer();
	Tokenizer *tokenizer2 = new CPPTokenizer();
	
	const char *file1 = processor1 -> process(path1);
	const char *file2 = processor2 -> process(path2);

	// typedefs in CPPOnly
	const char *def1 = (CPPFileProcessor *)processor1 -> GetTypedefs();
	const char *def2 = (CPPFileProcessor *)processor2 -> GetTypedefs();
	tokenizer1 -> processorInfo(std::string(def1));
	auto ret1 = tokenizer1 -> process(file1);

	tokenizer2 -> processorInfo(std::string(def2));
	auto ret2 = tokenizer2 -> process(file2);

	Analyser* analyser = new Analyser();
	analyser -> set_M(m_value);
	auto result = analyser -> analysis(ret1, ret2);

	delete processor1;
	delete processor2;
	delete tokenizer1;
	delete tokenizer2;
	delete analyser;
	
	return result;
}