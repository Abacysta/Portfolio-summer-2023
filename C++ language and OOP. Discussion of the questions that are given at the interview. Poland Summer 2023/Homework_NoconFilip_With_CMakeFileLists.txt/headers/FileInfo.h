#ifndef FILEINFO_H
#define FILEINFO_H

#include <string>
#include <ctime>
#include <vector>
#include <filesystem>
struct FileInfo {
	std::string name;
	uintmax_t size;
	std::string modificationTime;
	std::string permissions;
};
class FileCollector {
public:
	std::vector<FileInfo> CollectFiles(std::string folderPath);
};
#endif 