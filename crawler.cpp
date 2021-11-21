#include <stdio.h>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <optional>
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

//TODO: std::permissions
//std::permissions zwraca tylko flagi, nie możemy zczytać czy mamy również poprawny UID lub GID, nawet jeśli flaga R jest prawdziwa
//alternatywa: zczytać plik io streamem, spojrzeć na iostate, który posiada failbit (input/output operation failed (formatting or extraction error)) 
void directory_crawl(const std::filesystem::path &start_path){
    int total_entries = 0;
    int dircount = 0;
    int filecount = 0;
    int linecount = 0;
    int unreadable = 0;
    for(auto const &d: std::filesystem::recursive_directory_iterator{start_path}){
        //std::filesystem::perms p = std::filesystem::status(d).permissions();
        //bool owner_read = (p & std::filesystem::perms::owner_read) != std::filesystem::perms::none;
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
        //std::cout << d << owner_read << group_read << others_read << "\n";
        //std::cout << d << owner_read << "\n";
        //std::cout << d << "\n";
    }
    printf("total entries: %d, directory count: %d, file count: %d, total line count: %d \n",total_entries, dircount, filecount, linecount); // probably replace it with cout
}
