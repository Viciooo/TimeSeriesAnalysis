#include "curl.h"
#include "csv_writer.h"

int main() {
    std::cout << "Welcome to the web scraping program.\nFollow the instructions to download a desired CSV file.\n\n";

    Curl curl;
    curl.inputDataSource();

    CSVWriter csvWriter(curl.getHTMLTable());
    csvWriter.extractHeader();
    csvWriter.extractData();
    csvWriter.writeToCSV(curl.getDataSourceIdx());

    return 0;
}
