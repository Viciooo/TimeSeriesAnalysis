#include "curl.h"

int main() {
    Curl curl;

    curl.getHTMLTable();
    std::cout << curl << std::endl;

    return 0;
}
