#include "curl.h"
#include "csv_writer.h"

int main() {
    std::cout << "Welcome to the web scraping program.\nFollow the instructions to download a desired CSV file.\n\n";

    Curl curl;
    curl.inputDataSource();

    CSVWriter csvWriter(curl.getHTMLTable());
    csvWriter.extractHeader();
    csvWriter.extractData();
    std::string fileName = csvWriter.writeToCSV(curl.getDataSourceIdx());

    std::cout << "\nYour file is ready! File name: " << fileName << "\n";

    return 0;
}
