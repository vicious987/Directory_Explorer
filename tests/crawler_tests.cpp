#include "crawler.h"

#include <gtest/gtest.h>

namespace {

TEST(count_lines, oneliner) {
    EXPECT_EQ(1, count_lines("tests/files/oneliner.txt"));
}

TEST(count_lines, threeliner) {
    EXPECT_EQ(3, count_lines("tests/files/3liner.txt"));
}

TEST(count_lines, non_existing) {
    EXPECT_EQ(-1, count_lines("tests/files/missing.txt"));
}

} // namespace
