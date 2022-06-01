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
    res = other.res;
    curl_easy_cleanup(other.curlPtr);

    return *this;
}

void getHTMLTable() {
    Curl curl;
    if (curl.getCurlPtr()) {
        curl_easy_setopt(curl.getCurlPtr(), CURLOPT_URL, "https://finance.yahoo.com/quote/BTC-USD/history?p=BTC-USD");
        /* No redirection follow needed */
        curl_easy_setopt(curl.getCurlPtr(), CURLOPT_WRITEFUNCTION, Curl::WriteCallback);
        std::string buf;
        curl_easy_setopt(curl.getCurlPtr(), CURLOPT_WRITEDATA, &buf);

        /* Perform the request, res will get the return code */
        curl.setRes(curl_easy_perform(curl.getCurlPtr()));
        /* Check for errors */
        if (curl.getRes() != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(curl.getRes()));
        }

        /* Extract <table> tag content */
        std::size_t tablePos = buf.find("<table");
        buf = buf.substr(tablePos);
        tablePos = buf.find("</table>");
        buf = buf.substr(0, tablePos + strlen("</table>"));

        /* Print the HTML table */
        // TODO: remove this later
        std::cout << buf << std::endl;
    }
}