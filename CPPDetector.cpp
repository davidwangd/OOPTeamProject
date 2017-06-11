#include "CPPDetector.h"
#include "analyzer.h"
std::pair<double, double> CPPPlagiarismDetector::check(const char *path1, const char *path2){
	FileProcessor *processor1 = new CPPFileProcessor();
	FileProcessor *processor2 = new CPPFileProcessor();
	Tokenizer *tokenizer1 = new CPPTokenizer();
	Tokenizer *tokenizer2 = new CPPTokenizer();
	
	const char *file1 = processor1 -> process(path1);
	const char *file2 = processor2 -> process(path2);

#ifdef DEBUG
	fprintf(stderr, "Processor Work Finshed!\n");
#endif

	// typedefs in CPPOnly
	const char *def1 = ((CPPFileProcessor *)processor1) -> GetTypedefs();
	const char *def2 = ((CPPFileProcessor *)processor2) -> GetTypedefs();

#ifdef DEBUG
	fprintf(stderr, "GetTypeDefs OK");
#endif

	tokenizer1 -> ProcessorInfo(std::string(def1));
	auto ret1 = tokenizer1 -> process(file1);

#ifdef DEBUG
	fprintf(stderr, "Tokneizer1 Finshed!\n");
#endif

	tokenizer2 -> ProcessorInfo(std::string(def2));
	auto ret2 = tokenizer2 -> process(file2);

#ifdef DEBUG
	fprintf(stderr, "Tokneizer2 Finshed!\n");

	for (int i = 0;i < ret2.size(); i++){
		fprintf(stderr, "%d,%d", ret2[i]->Value(), ret2[i]->ApproximateValue());
	}

	fprintf(stderr, "\n\n");
	for (int i = 0;i < ret1.size();i++){
		fprintf(stderr, "%d,%d\n", ret1[i]->Equal(ret2[i]), ret1[i]->ApproximateEqual(ret2[i]));
	}
#endif

	
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
