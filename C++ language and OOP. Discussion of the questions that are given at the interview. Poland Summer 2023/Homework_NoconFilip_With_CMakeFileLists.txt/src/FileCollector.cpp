#include "FileInfo.h"
#include <filesystem>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <iostream>

std::string PermissionsToString(std::filesystem::perms permissions) {
	std::string permsStr;

	permsStr += (permissions & std::filesystem::perms::owner_read) != std::filesystem::perms::none ? "r" : "-";
	permsStr += (permissions & std::filesystem::perms::owner_write) != std::filesystem::perms::none ? "w" : "-";
	permsStr += (permissions & std::filesystem::perms::owner_exec) != std::filesystem::perms::none ? "x" : "-";
	permsStr += (permissions & std::filesystem::perms::group_read) != std::filesystem::perms::none ? "r" : "-";
	permsStr += (permissions & std::filesystem::perms::group_write) != std::filesystem::perms::none ? "w" : "-";
	permsStr += (permissions & std::filesystem::perms::group_exec) != std::filesystem::perms::none ? "x" : "-";
	permsStr += (permissions & std::filesystem::perms::others_read) != std::filesystem::perms::none ? "r" : "-";
	permsStr += (permissions & std::filesystem::perms::others_write) != std::filesystem::perms::none ? "w" : "-";
	permsStr += (permissions & std::filesystem::perms::others_exec) != std::filesystem::perms::none ? "x" : "-";

	return permsStr;
}

std::string fileTimeTypeToString(const std::filesystem::file_time_type& fileTime) {
	auto sctp = std::chrono::time_point_cast<std::chrono::system_clock::duration>(fileTime - std::filesystem::file_time_type::clock::now() + std::chrono::system_clock::now());
	std::time_t tt = std::chrono::system_clock::to_time_t(sctp);

	std::tm gmt;
	gmtime_s(&gmt, &tt);

	std::stringstream buffer;
	buffer << std::put_time(&gmt, "%Y-%m-%d %H:%M:%S ");
	return buffer.str();
}



std::vector<FileInfo> FileCollector::CollectFiles(std::string folderPath) {
	std::vector<FileInfo> files;
	if (!std::filesystem::exists(folderPath)) {
		throw std::runtime_error("Path does not exist!");
	}
	try {
		for (const auto& entry : std::filesystem::directory_iterator(folderPath))
		{
			FileInfo fileInfo;
			if (std::filesystem::is_regular_file(entry)) {
				fileInfo.name = entry.path().filename().string();
				fileInfo.size = std::filesystem::file_size(entry.path());
				fileInfo.modificationTime = fileTimeTypeToString(std::filesystem::last_write_time(entry.path()));
				fileInfo.permissions = PermissionsToString(std::filesystem::status(entry.path()).permissions());


				files.push_back(fileInfo);
			}
		}
	}
	catch (const std::exception& e) {
		std::cerr << "Exception caught: " << e.what() << '\n';
	}



	return files;
}
