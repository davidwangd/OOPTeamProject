#ifndef OOP_TEAMPROJECT_DETECTOR_H
#define OOP_TEAMPROJECT_DETECTOR_H
#define OOP_TEAMPROJECT_DETECTOR_H

#include <map>

class PlagiarismDetector{
public:
	PlagiarismDetector() = default;
	virtual std::pair<double, double> check(const char *path1, const char *path2);
	virtual std::map<std::pair<int, int>, double> check(const char *paths[], int sum){}
	void setValue(int value){
		m_value = value;
	}
protected: 
	int m_value;
};

#endif
