#ifndef OOP_TEAMWORK_UTILS_FILEENUMERATOR_H
#define OOP_TEAMWORK_UTILS_FILEENUMERATOR_H

// coder : gaoj

#include <string>
#include <vector>

std::vector<std::string> GetCertainAttribute(const char* pathname, const char* attrib);
std::vector<std::string> GetSources(const char* pathname, const std::string Attribs[], int Count);
std::string Trim(const std::string& str);


#endif /* end of include guard: OOP_TEAMWORK_UTILS_FILEENUMERATOR_H */
