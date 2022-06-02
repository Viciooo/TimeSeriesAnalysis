#include "curl.h"

size_t Curl::WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    ((std::string *) userp)->append((char *) contents, size * nmemb);
    return size * nmemb;
}

void Curl::inputDataSource() {
    while (true) {
        std::cout << "Pick one of the following data source by entering one of the numbers below:\n";
        for (std::size_t i = 0; i < NumOfDataSources; ++i) {
            std::cout << "(" << i << "): " << AvailableDataSources[i] << "\n";
        }
        std::cin >> dataSourceIdx;
        if (dataSourceIdx >= NumOfDataSources) {
            std::cout << "Data source index out of range. Pick again.\n";
        } else {
            break;
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

        /*
         * Extract table content
         * Normally it would end with </table>, but after <tbody> we have footers which are useless for us
         */
        std::size_t tableStartPos = HTMLTable.find("<table");
        std::size_t tableEndPos = HTMLTable.find("</tbody>", tableStartPos);
        HTMLTable = HTMLTable.substr(tableStartPos, tableEndPos - tableStartPos + 1);
    }
    return HTMLTable;
}
