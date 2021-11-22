#include "crawler.h"

#include <cstdio>
#include <iostream>
#include <deque>
#include <thread>
#include <mutex>
#include <cassert>
#include <algorithm>

//TODO
// change counters from int to usigned longs
// move verbose from directory_crawl into seperate function 

std::ostream& operator<<(std::ostream& out, const dir_stats& ds) {
    return out << "{"
               << ds.total_entries << ", "
               << ds.dircount << ", "
               << ds.filecount << ", "
               << ds.linecount << ", "
               << ds.unreadable << "}";
}

std::optional<int> count_lines(const std::filesystem::path &path){
    std::fstream istream;
    int lines = 0;
    std::string s;
    istream.open(path, std::ios::in);
    if (!istream.is_open())
        return std::nullopt;
    while(std::getline(istream, s))
        lines++;
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

std::optional<dir_stats> directory_crawl(const std::filesystem::path &start_path, int thread_count, bool verbose) {
    thread_count = std::min(thread_count, int(std::thread::hardware_concurrency()));
    std::mutex mtx;
    dir_stats res;
    std::deque<std::filesystem::path> filepaths;
    std::vector<std::thread> threads;

    if (!std::filesystem::is_directory(start_path)){
        return std::nullopt;
    }

    //gather files to process and divide into equal groups
    for(auto const &d: std::filesystem::recursive_directory_iterator{start_path}){
        res.total_entries++;
        if (d.is_directory())
            res.dircount++;
        else {
            filepaths.push_back(d);
            res.filecount++;
        }
    }
    const auto grouped_filepaths = split_deque(filepaths, thread_count);
    assert(grouped_filepaths.size() == thread_count);

    //appoint each group of files to a thread
    threads.reserve(thread_count);
    for (int i = 0; i< thread_count; i++) {
        const auto &group = grouped_filepaths[i];
        threads.push_back(std::thread([&res, &mtx](const std::deque<std::filesystem::path> &g) {
            const int count = count_lines_in_files(g);
            {
                std::lock_guard<std::mutex> lock(mtx);
                res.linecount += count;
            }
        }, group));
    }

    for (auto & t : threads){
        t.join();
    }

    if (verbose) {
        printf("total entries: %d, directory count: %d, file count: %d, total line count: %d \n",
            res.total_entries, res.dircount, res.filecount, res.linecount);
    }
    return res;
}