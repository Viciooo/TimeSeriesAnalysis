#include "curl.h"
#include "csv_writer.h"

int main() {
    Curl curl;
    CSVWriter csvWriter(curl.getHTMLTable());
    csvWriter.extractHeader();
    csvWriter.extractData();
    csvWriter.writeToCSV();
    return 0;
}
