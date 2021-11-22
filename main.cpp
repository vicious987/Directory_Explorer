#include <filesystem>
#include <string>
#include "crawler.h"

int main(int argc, char** argv) {
    std::string default_path = "/home/vicious/playground";
    std::filesystem::path p;

    p = argc > 1 ? argv[1] : default_path;
    directory_crawl(p, 2, false);
    return 0;
}
