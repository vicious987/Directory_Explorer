#include <stdio.h>
#include <iostream>
#include <filesystem>
#include <fstream>

int count_lines(const std::filesystem::path &path){
    std::fstream istream;                
    int lines = 0;                  //huge files?
    std::string s;
    istream.open(path, std::ios::in);             //FIXME what if can't open
    if (!istream.is_open())
        return -1;
    while(std::getline(istream, s)) // is it safe?
        lines++;                    // what if huge 1 liner?
    istream.close();
    return lines;
}

void directory_crawl(const std::filesystem::path &start_path){
    int total_entries = 0;          //move stats to seperate structure?
    int dircount = 0;
    int filecount = 0;
    int linecount = 0;
    for(auto const &d: std::filesystem::recursive_directory_iterator{start_path}){
        total_entries++;
        if (d.is_directory())
            dircount++;
        else {
            filecount++;
            linecount += count_lines(d.path());
        }
        std::cout << d << "\n";
    }
    printf("total entries: %d, directory count: %d, file count: %d, total line count: %d \n",total_entries, dircount, filecount, linecount); // probably replace it with cout
}
