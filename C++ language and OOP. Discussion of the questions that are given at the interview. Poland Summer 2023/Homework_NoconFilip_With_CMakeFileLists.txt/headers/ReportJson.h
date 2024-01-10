#ifndef REPORTJSON_H
#define REPORTJSON_H

#include "Report.h"
#include <boost/json.hpp>
class ReportJSON : public Report {
public:
    void generate(std::vector<FileInfo>& files) override;
};
#endif 