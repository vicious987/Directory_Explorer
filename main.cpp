#include "crawler.h"

#include <filesystem>
#include <string>
#include <stdlib.h>

int main(int argc, char** argv) {
    std::string default_path = "/home/vicious/playground";

    std::filesystem::path p = default_path;
    unsigned int thread_number = 1;

    switch(argc){
        case 3:
            thread_number = std::atoi(argv[2]);
        case 2:
            p = argv[1];
            break;
        default:
            printf("Bad arguments count! Examplary usage:\n./build/bcf pathname thread_number\n");
            return 0;
    }

    auto r = directory_crawl(p, thread_number);
    if (r.has_value()){
        pretty_print(r.value());
    }
    return 0;
}
