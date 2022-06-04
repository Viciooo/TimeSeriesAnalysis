#ifndef TIMESERIESANALYSIS_CURL_H
#define TIMESERIESANALYSIS_CURL_H

#include <cstdio>
#include <curl/curl.h>
#include <string>
#include <iostream>
#include <cstring>
#include <vector>

class Curl {
public:
    static constexpr inline std::size_t NumOfDataSources = 4;
    static constexpr inline char AvailableDataSources[NumOfDataSources][60] = {
            "https://finance.yahoo.com/quote/%5EGSPC/history?p=%5EGSPC",
            "https://finance.yahoo.com/quote/%5EDJI/history?p=%5EDJI",
            "https://finance.yahoo.com/quote/%5EIXIC/history?p=%5EIXIC",
            "https://finance.yahoo.com/quote/CL%3DF/history?p=CL%3DF"
    };

    /*
     * There's basically only one thing to keep in mind when using C++ instead of C when interfacing libcurl:
     * The callbacks CANNOT be non-static class member functions
     * Source: https://curl.se/libcurl/c/libcurl-tutorial.html
     */
    static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp);

    Curl() : curlPtr(curl_easy_init()), curlRes(), dataSourceIdx() {}

    // to get Weffc++ off my back :)
    Curl(const Curl &curl) = delete;
    Curl &operator=(const Curl &other) = delete;

    virtual ~Curl() {
        /* always cleanup */
        curl_easy_cleanup(curlPtr);
    }

    [[nodiscard]] auto getDataSourceIdx() const {
        return dataSourceIdx;
    }

    void inputDataSource(int argc, char *argv[]);

    std::string getHTMLTable();

private:
    CURL *curlPtr;
    CURLcode curlRes;
    std::size_t dataSourceIdx;
};

#endif //TIMESERIESANALYSIS_CURL_H
