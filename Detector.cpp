#include "Detector.h"

std::pair<double, double> CPPPlagiarismDetector::check(const char *path1, const char *path2){
	FileProcessor *processor1 = new FileProcessor();
	FileProcessor *processor2 = new FileProcessor();
	Tokenizer *tokenizer1 = new Tokenizer();
	Tokenizer *tokenizer2 = new Tokenizer();
	
	const char *file1 = processor1 -> process(path1);
	const char *file2 = processor2 -> process(path2);

	auto ret1 = tokenizer1 -> process(file1);
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