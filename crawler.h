#include <filesystem>
#include <fstream>
#include <optional>

std::optional<int> count_lines(const std::filesystem::path &path);

void directory_crawl(const std::filesystem::path &start_path);
