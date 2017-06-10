#ifndef OOP_TEAMPROJECT_DETECTOR_H
#define OOP_TEAMPROJECT_DETECTOR_H
#include "CPPFileProcessor.h"
#include "CPPToken.h"

class CPPPlagiarismDetector : public PlagiarismDetector{
	CPPPlagiarismDetector() = default;
	double check(const char *path1, const char *path2);
};

#endif

