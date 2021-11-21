#include "crawler.h"

#include <cstdio>
#include <iostream>
#include <deque>


//TODO: change counters from int to usigned longs

std::optional<int> count_lines(const std::filesystem::path &path){
    std::fstream istream;                
    int lines = 0;                  //huge files?
    std::string s;
    istream.open(path, std::ios::in);             //FIXME what if can't open
    if (!istream.is_open())
        return std::nullopt; 
    while(std::getline(istream, s)) // is it safe?
        lines++;                    // what if huge 1 liner?
    istream.close();
    return lines;
}

int count_lines_in_files(const std::deque<std::filesystem::path> &paths){
    int total = 0;
    for (const auto & p: paths) {
        auto cl = count_lines(p);
        total += cl.value_or(0);
    }
    return total;
}

std::optional<dir_stats> directory_crawl(const std::filesystem::path &start_path, bool verbose) {
    if (!std::filesystem::is_directory(start_path)){
        return std::nullopt;
    }
    dir_stats res;
    std::deque<std::filesystem::path> filepaths;

    for(auto const &d: std::filesystem::recursive_directory_iterator{start_path}){
        res.total_entries++;
        if (d.is_directory())
            res.dircount++;
        else {
            filepaths.push_back(d);
            res.filecount++;
        }
        //std::cout << d << "\n";
    }
    res.linecount = count_lines_in_files(filepaths);
    if (verbose) {
        printf("total entries: %d, directory count: %d, file count: %d, total line count: %d \n",
            res.total_entries, res.dircount, res.filecount, res.linecount); // probably replace it with cout
    }
    return res;
}