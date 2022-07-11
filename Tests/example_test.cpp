#include <gtest/gtest.h>

TEST(check_string, check_if_string_is_correct)
{
    std::string a = "Ala";

    EXPECT_EQ(a, "Ala");
}