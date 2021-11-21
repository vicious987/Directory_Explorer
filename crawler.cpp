#include "crawler.h"

#include <cstdio>
#include <iostream>
#include <deque>
#include <thread>
#include <cassert>

//TODO: change counters from int to usigned longs

std::ostream& operator<<(std::ostream& out, const dir_stats& ds) {
    return out << "{"
               << ds.total_entries << ", "
               << ds.dircount << ", "
               << ds.filecount << ", "
               << ds.linecount
               << "}";
}

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

std::vector<std::deque<std::filesystem::path>> split_deque(const std::deque<std::filesystem::path> &in_deq, int n){
    std::vector<std::deque<std::filesystem::path>> ret;
    ret.reserve(n);
    for (int i = 0; i < n; i++){
        ret.push_back(std::deque<std::filesystem::path>());
    }

    int i = 0;
    for (const auto & p : in_deq) {
        ret[i%n].push_back(p);
        i++;
    }
    return ret;
}



std::optional<dir_stats> directory_crawl(const std::filesystem::path &start_path, bool verbose) {
    const int thread_count = 2;
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

    const auto grouped_filepaths = split_deque(filepaths, thread_count);
    assert(grouped_filepaths.size() == thread_count);

    std::vector<std::thread> threads;
    threads.reserve(thread_count);
    for (int i = 0; i< thread_count; i++) {
        const auto &group = grouped_filepaths[i];
        threads.push_back(std::thread([&res](const std::deque<std::filesystem::path> &g) {
            int count = count_lines_in_files(g);
            res.linecount += count;
        }, group));
    }

    for (auto & t : threads){
        t.join();
    }

    if (verbose) {
        printf("total entries: %d, directory count: %d, file count: %d, total line count: %d \n",
            res.total_entries, res.dircount, res.filecount, res.linecount); // probably replace it with cout
    }
    return res;
}