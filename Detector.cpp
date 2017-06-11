#include "Detector.h"
#include "analyzer.h"
#include "FileProcessor.h"
#include "token_basic.h"

std::pair<double, double> PlagiarismDetector::check(const char *path1, const char *path2){
	FileProcessor *processor1 = new FileProcessor();
	FileProcessor *processor2 = new FileProcessor();
	Tokenizer *tokenizer1 = new Tokenizer();
	Tokenizer *tokenizer2 = new Tokenizer();
	
	const char *file1 = processor1 -> process(path1);
	const char *file2 = processor2 -> process(path2);

	auto ret1 = tokenizer1 -> process(file1);
	auto ret2 = tokenizer2 -> process(file2);

	Analyzer* analyzer = new Analyzer();
	analyzer -> set_M(m_value);
	auto result = analyzer -> check(ret1, ret2);

	delete processor1;
	delete processor2;
	delete tokenizer1;
	delete tokenizer2;
	delete analyzer;
	
	return result;
}