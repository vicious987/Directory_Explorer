#include <filesystem>
#include <fstream>

int count_lines(std::fstream &istream, const std::filesystem::path &path);

void directory_crawl(const std::filesystem::path &start_path);
