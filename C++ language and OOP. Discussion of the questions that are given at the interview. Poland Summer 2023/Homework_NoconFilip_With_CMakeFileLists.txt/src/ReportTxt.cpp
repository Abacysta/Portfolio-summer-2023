#include "ReportTxt.h"
#include <fstream>
#include <stdexcept>
#include <iostream>

void ReportTxt::generate(std::vector<FileInfo>& files) {
	std::ofstream outfile("ReportTxt.txt");

	try {
		for (const auto& file : files) {
			outfile << "File Name: " << file.name << "\t";
			outfile << "File Size: " << file.size << "\t";
			outfile << "File Last Modification: " << file.modificationTime << "\t";
			outfile << "File Permissions: " << file.permissions << "\t";
			outfile << std::endl;
		}
	}
	catch (const std::exception& e) {
		std::cerr << "Exception caught: " << e.what() << std::endl;
	}
}