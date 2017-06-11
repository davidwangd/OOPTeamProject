#ifndef OOP_TEAMPROJECT_CPPDETECTOR_H
#define OOP_TEAMPROJECT_CPPDETECTOR_H
// coder : davidwang

#include "CPPFileProcessor.h"
#include "CPPToken.h"
#include "Detector.h"

class CPPPlagiarismDetector : public PlagiarismDetector{
public:
	CPPPlagiarismDetector() = default;
	std::pair<double, double> check(const char *path1, const char *path2);
};

#endif

