#include <filesystem>
#include <fstream>
#include <optional>
#include <vector>
#include <deque>

struct dir_stats {
    int total_entries = 0;
    int dircount = 0;
    int filecount = 0;
    int linecount = 0;
    int unreadable = 0;

    constexpr bool operator==(const dir_stats& other) const {
        return total_entries == other.total_entries &&
                dircount == other.dircount &&
                filecount == other.filecount &&
                linecount == other.linecount &&
                unreadable == other.unreadable;
    }
};

std::ostream& operator<<(std::ostream& out, const dir_stats& ds);

std::optional<int> count_lines(const std::filesystem::path &path);

std::optional<dir_stats> directory_crawl(const std::filesystem::path &start_path, bool verbose=true);

std::vector<std::deque<std::filesystem::path>> split_deque(const std::deque<std::filesystem::path> &in_deq, int n);