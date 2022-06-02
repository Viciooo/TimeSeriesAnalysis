#include "csv_writer.h"

void CSVWriter::extractHeader() {
    currPos = HTMLTable.find("<span>", currPos);
    std::size_t headerEndPos = HTMLTable.find("</thead>", currPos);
    while (currPos <= headerEndPos) {
        currPos += 6; // len("<span>") == 6
        while (HTMLTable[currPos] != '<') {
            header.push_back(HTMLTable[currPos++]);
        }
        header.push_back(',');
        ++numOfCols;
        currPos = HTMLTable.find("<span>", currPos);
    }
    header.back() = '\n'; // replace the last comma with a new line
}

void CSVWriter::extractData() {
    while (currPos < HTMLTable.length()) {
        // Date is in the wrong format, so we need to format it first
        currPos += 6;
        data.append(formatDate());
        data.push_back(',');
        currPos = HTMLTable.find("<span>", currPos);

        // the rest of the data
        for (int i = 1; i < numOfCols; ++i) { // from one since we skip the date
            currPos += 6;
            if (HTMLTable[currPos] == '-') {
                data.append("null");
            }
            while (HTMLTable[currPos] != '<') {
                if (HTMLTable[currPos] != ',') { // unfortunately a comma is used to separate digits, so we need to get rid of it
                    data.push_back(HTMLTable[currPos]);
                }
                ++currPos;
            }
            data.push_back(',');
            currPos = HTMLTable.find("<span>", currPos);
        }
        data.back() = '\n';
    }

    data.pop_back();
}

std::string CSVWriter::formatDate() {
    // First three letters - an abbreviation of a month
    // Then we have the day after a space, then a comma and space followed by the year
    char month[4] = {HTMLTable[currPos], HTMLTable[currPos + 1], HTMLTable[currPos + 2], '\0'};
    std::string csvDate = HTMLTable.substr(currPos + 8, 4); // year

    // month
    if (strcmp(month, "Jan") == 0) csvDate.append("-01-");
    else if (strcmp(month, "Feb") == 0) csvDate.append("-02-");
    else if (strcmp(month, "Mar") == 0) csvDate.append("-03-");
    else if (strcmp(month, "Apr") == 0) csvDate.append("-04-");
    else if (strcmp(month, "May") == 0) csvDate.append("-05-");
    else if (strcmp(month, "Jun") == 0) csvDate.append("-06-");
    else if (strcmp(month, "Jul") == 0) csvDate.append("-07-");
    else if (strcmp(month, "Aug") == 0) csvDate.append("-08-");
    else if (strcmp(month, "Sep") == 0) csvDate.append("-09-");
    else if (strcmp(month, "Oct") == 0) csvDate.append("-10-");
    else if (strcmp(month, "Nov") == 0) csvDate.append("-11-");
    else if (strcmp(month, "Dec") == 0) csvDate.append("-12-");
    else throw std::invalid_argument("Date on the website must be a three-letter abbreviation in order to be formatted properly.");

    // day
    csvDate.append(HTMLTable.substr(currPos + 4, 2));

    return csvDate;
}

std::string CSVWriter::writeToCSV(std::size_t dataSourceIdx) {
    std::string fileName("data");
    fileName.append(std::to_string(dataSourceIdx));
    fileName.append(".csv");
    std::ofstream csvFile(fileName);
    if (csvFile.is_open()) {
        csvFile << header;
        csvFile << data;
        csvFile.close();
    } else {
        throw std::runtime_error("Unable to open the file.");
    }

    return fileName;
}
