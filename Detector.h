#ifndef OOP_TEAMPROJECT_DETECTOR_H
#define OOP_TEAMPROJECT_DETECTOR_H

#include <map>

class PlagiarismDetector{
	PlagiarismDector(Language lan) = default;
	virtual double check(const char *path1, const char *path2) = 0;
	virtual std::map<std::pair<int, int>, double> check(const char *paths[], int sum) = 0;
};

#endif
