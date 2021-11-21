#include "crawler.h"
#include <gtest/gtest.h>
#include <optional>
#include <filesystem>

//test 
namespace {

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
    EXPECT_EQ(false, count_lines("tests/files/missing.txt").has_value());
}


} // namespace
