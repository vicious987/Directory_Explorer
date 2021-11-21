#include "crawler.h"
#include <gtest/gtest.h>
#include <optional>
#include <filesystem>

//test 
//TODO TESTS:
//bad input dir
namespace {

// some tests operate on files and might fail if run from bad directory due to relative pathnames
// this function ensures that tests fail if not ran from main project directory
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

TEST(count_lines, unredable_empty) {
    ASSERT_TRUE(is_good_working_dir());
    auto filename = "tests/files/unreadable_empty.txt";
    auto old_perms = std::filesystem::status(filename).permissions();
    std::filesystem::permissions(filename, std::filesystem::perms::none, std::filesystem::perm_options::replace);
    const auto res = count_lines(filename);
    EXPECT_EQ(false, res.has_value());
    std::filesystem::permissions(filename, old_perms, std::filesystem::perm_options::replace);
}


} // namespace
