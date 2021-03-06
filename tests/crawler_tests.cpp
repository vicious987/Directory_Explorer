#include "crawler.h"
#include <gtest/gtest.h>
#include <optional>
#include <vector>
#include <filesystem>

//test 
//TODO TESTS:
//huge files
//strange files
//'everything is a file' files
namespace {

// some tests operate on files and might yield unintential results if run from bad directory due to relative pathnames
// this function ensures that tests fail if not run from main project directory
bool is_good_working_dir() {
    return std::filesystem::exists(".git");
}

TEST(count_lines, oneliner) {
    ASSERT_TRUE(is_good_working_dir());
    const auto res = count_lines("tests/files/oneliner.txt");
    ASSERT_TRUE(res.has_value());
    EXPECT_EQ(1, res.value());
}

TEST(count_lines, threeliner) {
    ASSERT_TRUE(is_good_working_dir());
    const auto res = count_lines("tests/files/3liner.txt");
    ASSERT_TRUE(res.has_value());
    EXPECT_EQ(3, res.value());
}

TEST(count_lines, lorem_ipsum_28) {
    ASSERT_TRUE(is_good_working_dir());
    const auto res = count_lines("tests/files/lorem_ipsum_28.txt");
    ASSERT_TRUE(res.has_value());
    EXPECT_EQ(28, res.value());
}

TEST(count_lines, lorem_ipsum_10) {
    ASSERT_TRUE(is_good_working_dir());
    const auto res = count_lines("tests/files/lorem_ipsum_10.txt");
    ASSERT_TRUE(res.has_value());
    EXPECT_EQ(10, res.value());
}

TEST(count_lines, non_existing) {
    ASSERT_TRUE(is_good_working_dir());
    EXPECT_EQ(false, count_lines("tests/files/missing.txt").has_value());
}

TEST(count_lines, empty) {
    ASSERT_TRUE(is_good_working_dir());
    const auto res = count_lines("tests/files/empty.txt");
    ASSERT_TRUE(res.has_value());
    EXPECT_EQ(0, res.value());
}

TEST(count_lines, unreadable_empty) {
    ASSERT_TRUE(is_good_working_dir());
    auto filename = "tests/files/unreadable_empty.txt";
    auto old_perms = std::filesystem::status(filename).permissions();
    std::filesystem::permissions(filename, std::filesystem::perms::none, std::filesystem::perm_options::replace);
    const auto res = count_lines(filename);
    EXPECT_EQ(false, res.has_value());
    std::filesystem::permissions(filename, old_perms, std::filesystem::perm_options::replace);
}

TEST(directory_crawl, empty_input){
    ASSERT_TRUE(is_good_working_dir());
    EXPECT_EQ(false, directory_crawl("", 2).has_value());
}

TEST(directory_crawl, non_existing_dir){
    ASSERT_TRUE(is_good_working_dir());
    EXPECT_EQ(false, directory_crawl("test/files/non_existing", 2).has_value());
}

TEST(directory_crawl, lorem_ipsum_28){
    ASSERT_TRUE(is_good_working_dir());
    EXPECT_EQ(false, directory_crawl("tests/files/lorem_ipsum_28.txt", 2).has_value());
}

TEST(directory_crawl, lorem_ipsum_10){
    ASSERT_TRUE(is_good_working_dir());
    EXPECT_EQ(false, directory_crawl("tests/files/lorem_ipsum_10.txt", 2).has_value());
}

//10*10 + 10 directories, 100 empty files
TEST(directory_crawl, wide_dir_only_110) {
    ASSERT_TRUE(is_good_working_dir());
    const auto res = directory_crawl("tests/files/wide_dir_only_110", 2);
    ASSERT_TRUE(res.has_value());
    dir_stats expected = {210, 110, 100, 0, 0};
    EXPECT_EQ(expected, res.value());
}

//2^10-1 directories in binary tree-like form of depth 10, 2^9 empty files
TEST(directory_crawl, deep_dir_only_1023) {
    ASSERT_TRUE(is_good_working_dir());
    const auto res = directory_crawl("tests/files/deep_dir_only_1023", 2);
    ASSERT_TRUE(res.has_value());
    dir_stats expected = {1535, 1023, 512, 0, 0};
    EXPECT_EQ(expected, res.value());
}

//20 directories, 10 text files, 10 lines each
TEST(directory_crawl, wide_dir_100) {
    ASSERT_TRUE(is_good_working_dir());
    const auto res = directory_crawl("tests/files/wide_dir_100", 2);
    ASSERT_TRUE(res.has_value());
    dir_stats expected = {30, 20, 10, 100, 0};
    EXPECT_EQ(expected, res.value());
}

TEST(split_deq, empty){
    auto input = std::deque<std::filesystem::path>();
    auto ret = split_deque(input, 2);
    EXPECT_EQ(ret.size(), 2);
    EXPECT_EQ(ret[0].size(), 0);
    EXPECT_EQ(ret[1].size(), 0);
}

TEST(split_deq, simple_case){
    std::deque<std::filesystem::path> input = {"a", "b", "c", "d"};
    auto ret = split_deque(input, 2);
    EXPECT_EQ(ret.size(), 2);
    EXPECT_EQ(ret[0].size(), 2);
    EXPECT_EQ(ret[1].size(), 2);
}
} // namespace
