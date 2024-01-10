#include "ReportJson.h"
#include <fstream>
#include <stdexcept>
#include <iostream>

void ReportJSON::generate(std::vector<FileInfo>& files) {
	boost::json::array fileArray;

	try {
		for (const auto& file : files) {
			boost::json::object fileObject;

			fileObject["Name"] = file.name;
			fileObject["Size"] = file.size;
			fileObject["Last_Modification"] = file.modificationTime;
			fileObject["Permissions"] = file.permissions;

			fileArray.push_back(fileObject);
		}

		boost::json::object reportObject;
		reportObject["Files"] = fileArray;

		std::ofstream outfile("ReportJSON.json");
		outfile << boost::json::serialize(reportObject);

	}
	catch (const std::exception& e) {
		std::cerr << "Exception caught: " << e.what() << std::endl;;
	}
}