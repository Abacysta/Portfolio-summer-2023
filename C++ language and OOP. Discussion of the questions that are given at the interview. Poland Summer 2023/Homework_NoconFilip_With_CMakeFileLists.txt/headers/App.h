#ifndef APP_H
#define APP_H

#include "FileInfo.h"
#include "Report.h"
#include "Factory.h"
#include <vector>


class App {
public:
	void Run();
private:
	FileCollector collector;
	std::vector<FileInfo> files;

	void CollectFiles();
	int GetUserChoice();
	void HandleUserChoice(int choice);
	void GenerateReport(Type type, const std::string& reportName);
};

#endif
