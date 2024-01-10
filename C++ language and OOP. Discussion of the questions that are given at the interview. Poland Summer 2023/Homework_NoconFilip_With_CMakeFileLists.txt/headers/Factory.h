#ifndef FACTORY_H
#define FACTORY_H

#include "Report.h"
#include "ReportJson.h"
#include "ReportTxt.h"

enum Type { TXT, JSON };

class Factory {
public:
    static std::unique_ptr<Report> generateReport(Type t, std::vector<FileInfo>& files);
};
#endif 