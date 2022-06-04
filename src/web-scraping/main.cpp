#include "curl.h"
#include "csv_writer.h"

int main(int argc, char *argv[]) {
    Curl curl;
    try {
        curl.inputDataSource(argc, argv);
    } catch (const std::exception &exception) {
        std::cout << exception.what() << "\n";
        exit(EXIT_FAILURE);
    }

    std::cout << "The file is being prepared. Please wait...\n";

    CSVWriter csvWriter(curl.getHTMLTable());
    csvWriter.extractHeader();
    csvWriter.extractData();
    std::string fileName;
    try {
        fileName = csvWriter.writeToCSV(curl.getDataSourceIdx());
    } catch (const std::runtime_error &exception) {
        std::cout << exception.what() << "\n";
    }

    std::cout << "\nYour file is ready! File name: " << fileName << "\n";

    return 0;
}
