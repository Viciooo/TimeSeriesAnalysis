#ifndef TIMESERIESANALYSIS_CURL_H
#define TIMESERIESANALYSIS_CURL_H

#include <cstdio>
#include <curl/curl.h>
#include <string>
#include <iostream>
#include <cstring>

class Curl {
public:
    Curl() : curlPtr(curl_easy_init()), res() {}

    Curl(const Curl &curl) = default; // trivial copy constructor

    virtual ~Curl() {
        /* always cleanup */
        curl_easy_cleanup(curlPtr);
    }

    /*
     * There's basically only one thing to keep in mind when using C++ instead of C when interfacing libcurl:
     * The callbacks CANNOT be non-static class member functions
     * Source: https://curl.se/libcurl/c/libcurl-tutorial.html
     */
    static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp);

    Curl &operator=(const Curl &other);

    [[nodiscard]] void *getCurlPtr() const {
        return curlPtr;
    }

    [[nodiscard]] CURLcode getRes() const {
        return res;
    }

    void setRes(CURLcode res_) {
        res = res_;
    }

private:
    CURL *curlPtr;
    CURLcode res;
};

void getHTMLTable();

#endif //TIMESERIESANALYSIS_CURL_H
