#include "Factory.h"
#include <fstream>
#include <stdexcept>


std::unique_ptr<Report> Factory::generateReport(Type type, std::vector<FileInfo>& files) {

	switch (type)
	{
	case TXT: {
		auto report = std::make_unique<ReportTxt>();
		report->generate(files);
		return report;
	}
	case JSON: {
		auto report = std::make_unique<ReportJSON>();
		report->generate(files);
		return report;
	}
	default:
		throw std::invalid_argument("Invalid report type");
	}

}