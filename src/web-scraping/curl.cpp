#include "curl.h"

size_t Curl::WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    ((std::string *) userp)->append((char *) contents, size * nmemb);
    return size * nmemb;
}

Curl &Curl::operator=(const Curl &other) {
    // Guard self assignment
    if (this == &other)
        return *this;

    curlPtr = other.curlPtr;
    curlRes = other.curlRes;
    curl_easy_cleanup(other.curlPtr);

    return *this;
}

void Curl::getHTMLTable() {
    if (curlPtr) {
        // TODO: link from the user input
        curl_easy_setopt(curlPtr, CURLOPT_URL, "https://finance.yahoo.com/quote/BTC-USD/history?p=BTC-USD");
        /* No redirection follow needed */
        curl_easy_setopt(curlPtr, CURLOPT_WRITEFUNCTION, Curl::WriteCallback);
        curl_easy_setopt(curlPtr, CURLOPT_WRITEDATA, &HTMLTable);

        /* Perform the request, curlRes will get the return code */
        curlRes = curl_easy_perform(curlPtr);
        /* Check for errors */
        if (curlRes != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(curlRes));
        }

        /* Extract <table> tag content */
        std::size_t tablePos = HTMLTable.find("<table");
        HTMLTable = HTMLTable.substr(tablePos);
        tablePos = HTMLTable.find("</table>");
        HTMLTable = HTMLTable.substr(0, tablePos + strlen("</table>"));
    }
}

std::ostream &operator<<(std::ostream &os, const Curl &curl) {
    os << "HTMLTable: " << curl.HTMLTable;
    return os;
}
