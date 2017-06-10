double CPPPlagiarismDetector::check(const char *path1, const char *path2){
	CPPFileProcessor *processor1 = new CPPFileProcessor();
	CPPFileProcessor *processor2 = new CPPFileProcessor();
	CPPTokenizer *tokenizer1 = new CPPTokenizer();
	CPPTokenizer *tokenizer2 = new CPPTokenizer();
	
	const char *file1 = processor1 -> process(path1);
	const char *file2 = processor2 -> process(path2);
	const char *def1 = processor1 -> GetTypedefs();
	const char *def2 = processor2 -> GetTypedefs();

	tokenizer1 -> processorInfo(std::string(def1));
	auto ret1 = tokenizer1 -> process(file1);

	tokenizer2 -> processorInfo(std::string(def2));
	auto ret2 = tokenizer2 -> process(file2);

	Analyser analyser = new Analyser();
	double result = analyser -> analysis(ret1, ret2);
	return result;
}
