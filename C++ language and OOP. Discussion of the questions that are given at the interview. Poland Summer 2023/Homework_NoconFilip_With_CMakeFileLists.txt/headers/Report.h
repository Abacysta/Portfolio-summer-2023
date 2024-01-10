#ifndef REPORT_H
#define REPORT_H


#include "FileInfo.h"
#include <memory>


class Report {
public:
    virtual void generate(std::vector<FileInfo>& files) = 0;
};

#endif 