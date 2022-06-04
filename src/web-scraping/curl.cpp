#include "curl.h"

size_t Curl::WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    ((std::string *) userp)->append((char *) contents, size * nmemb);
    return size * nmemb;
}

void Curl::inputDataSource(int argc, char *argv[]) {
    if (argc != 2) {
        throw std::domain_error(
                "You must pass exactly one argument to the program. Try running it with 'help' to see available arguments.");
    }
    if (strcmp(argv[1], "help") == 0) {
        std::cout << "Valid command-line arguments:\n";
        std::cout << "list: see available data sources with their indexes in brackets\n";
        std::cout << "[index]: download a CSV file associated with index\n";
        std::cout << "help: list all available command-line arguments (basically this view)\n";
        exit(EXIT_SUCCESS);
    } else if (strcmp(argv[1], "list") == 0) {
        for (std::size_t i = 0; i < NumOfDataSources; ++i) {
            std::cout << "[" << i << "]: " << AvailableDataSources[i] << "\n";
        }
        exit(EXIT_SUCCESS);
    } else {
        char *rem;
        // thankfully passing a negative integer into size_t var isn't undefined in C++, so we don't worry about it too much
        dataSourceIdx = (std::size_t) strtoull(argv[1], &rem, 10);
        if (*rem != '\0') {
            throw std::domain_error("You must pass a data source index which is a non-negative integer.");
        }
        if (dataSourceIdx >= NumOfDataSources) {
            throw std::out_of_range("Data source index out of range.");
        }
    }
}

std::string Curl::getHTMLTable() {
    std::string HTMLTable;
    if (curlPtr) {
        curl_easy_setopt(curlPtr, CURLOPT_URL, AvailableDataSources[dataSourceIdx]);
        /* No redirection follow needed */
        curl_easy_setopt(curlPtr, CURLOPT_WRITEFUNCTION, Curl::WriteCallback);
        curl_easy_setopt(curlPtr, CURLOPT_WRITEDATA, &HTMLTable);

        /* Perform the request, curlRes will get the return code */
        curlRes = curl_easy_perform(curlPtr);
        /* Check for errors */
        if (curlRes != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(curlRes));
        }

        return HTMLTable;
    }
    throw std::runtime_error("Can't access the selected data source.");
}
