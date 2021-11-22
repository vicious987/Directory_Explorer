#include "crawler.h"

#include <filesystem>
#include <string>
#include <stdlib.h>

int main(int argc, char** argv) {
    std::filesystem::path p;
    unsigned int thread_number = 1;

    switch(argc){
        case 3:
            thread_number = std::atoi(argv[2]);
            [[fallthrough]];
        case 2:
            p = argv[1];
            break;
        default:
            printf("Bad argument count! Usage:\n"
                   "bcf pathname thread_number\n");
            return 0;
    }

    auto r = directory_crawl(p, thread_number);
    if (r.has_value()){
        pretty_print(r.value());
    }
    return 0;
}
