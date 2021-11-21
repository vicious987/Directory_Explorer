#include <stdio.h>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <optional>
#include <vector>
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

std::optional<std::vector<int>> directory_crawl(const std::filesystem::path &start_path, bool verbose=true){
    if (!std::filesystem::is_directory(start_path)){
        return std::nullopt;
    }
    std::vector<int> v = {0, 0, 0, 0, 0};
    int total_entries = 0;
    int dircount = 0;
    int filecount = 0;
    int linecount = 0;
    int unreadable = 0;
    for(auto const &d: std::filesystem::recursive_directory_iterator{start_path}){
        total_entries++;
        if (d.is_directory())
            dircount++;
        else {
            filecount++;
            auto cl = count_lines(d.path());
            if (cl.has_value()){
                linecount += cl.value();
            } else {
                unreadable++;
            }
        }
        //std::cout << d << "\n";
    }
    if (verbose) {
        printf("total entries: %d, directory count: %d, file count: %d, total line count: %d \n",total_entries, dircount, filecount, linecount); // probably replace it with cout
    }
    v[0] = total_entries;
    v[1] = dircount;
    v[2] = filecount;
    v[3] = linecount;
    v[4] = unreadable;
    return v;
}