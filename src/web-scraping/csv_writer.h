#ifndef TIMESERIESANALYSIS_CSV_WRITER_H
#define TIMESERIESANALYSIS_CSV_WRITER_H

#include <string>
#include <utility>
#include <iostream>
#include <cstring>
#include <fstream>

class CSVWriter {
public:
    CSVWriter() = default;

    void setHTMLTable(std::string htmlTable) {
        HTMLTable = std::move(htmlTable);
    }

    void extractHeader();

    void extractData();

    // using copy elision
    std::string formatDate();

    // ditto
    std::string writeToCSV(std::size_t dataSourceIdx);

private:
    std::string HTMLTable{};
    std::size_t currPos{};
    std::string header{};
    int numOfCols{};
    std::string data{};
};

#endif //TIMESERIESANALYSIS_CSV_WRITER_H
