// Copyright 2024 Marina Usova

#include <gtest/gtest.h>
#include "../lib_stack_on_mass/stack_on_mass.h"
#include "../lib_algorithms/easy_example.h"

TEST(TestCheckBrackets, EasyCorrectBrackets) {
    std::string str = "{()}";
    EXPECT_TRUE(check_brackets(str));
}
TEST(TestCheckBrackets, DifficultCorrectBrackets) {
    std::string str = "{(())()[()()]}";
    EXPECT_TRUE(check_brackets(str));
}
TEST(TestCheckBrackets, EasyInorrectBrackets) {
    std::string str = "{((}";
    EXPECT_FALSE(check_brackets(str));
}
TEST(TestCheckBrackets, DifficultInorrectBrackets) {
    std::string str = "{(())()[(){()]}";
    EXPECT_FALSE(check_brackets(str));
}
