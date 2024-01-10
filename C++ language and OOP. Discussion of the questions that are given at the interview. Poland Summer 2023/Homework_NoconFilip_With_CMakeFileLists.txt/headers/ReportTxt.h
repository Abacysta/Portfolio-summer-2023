#ifndef REPORTTXT_H
#define REPORTTXT_H


#include "Report.h"

class ReportTxt : public Report {
public:
    void generate(std::vector<FileInfo>& files) override;
};
#endif 