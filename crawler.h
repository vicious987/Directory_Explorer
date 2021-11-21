#include <filesystem>
#include <fstream>
#include <optional>
#include <vector>

std::optional<int> count_lines(const std::filesystem::path &path);

std::optional<std::vector<int>> directory_crawl(const std::filesystem::path &start_path, bool verbose=true);
