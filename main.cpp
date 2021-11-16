#include <stdio.h>
#include <iostream>
#include <filesystem>
#include <fstream>

int count_lines(std::fstream &istream, const std::filesystem::path &path){
    int lines = 0;                  //huge files?
    std::string s;
    istream.open(path);             //FIXME what if can't open
    while(std::getline(istream, s)) // is it safe?
        lines++;                    // what if huge 1 liner?
    istream.close();
    return lines;
}

void directory_crawl(const std::filesystem::path &start_path){
    std::fstream fs;                //should be here or as arg?
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
            linecount += count_lines(fs, d.path());
        }
        std::cout << d << "\n";
    }
    printf("total entries: %d, directory count: %d, file count: %d, total line count: %d \n",total_entries, dircount, filecount, linecount); // probably replace it with cout
}

int main() {
    const std::filesystem::path p = "/home/vicious/playground";
    const std::filesystem::path p1 = "/home/vicious/playground/cpp/main.cpp";
    directory_crawl(p);
    return 0;
}