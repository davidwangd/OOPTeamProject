#include "CPPDetector.h"
#include "analyzer.h"
#ifdef DEBUG
#include "utils/CPP_Language/CppLexer.h"

namespace CPPLanguage{
	extern const char* cppTokenNames[cppTokenTypeCount + 1];
}
#endif
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
	FILE *curr1 = fopen("re1.txt", "w");
	for (auto c: ret1){
		fprintf(curr1, "[%s][%s]", CPPLanguage::cppTokenNames[c->ApproximateValue()], c->str.c_str());
	}
	fclose(curr1);
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
