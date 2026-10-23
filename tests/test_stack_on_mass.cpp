// Copyright 2024 Marina Usova

#include <gtest/gtest.h>
#include "../lib_stack_on_mass/stack_on_mass.h"

TEST(ClassStackOnMass, can_create_with_size_cons) {
  TStackOnMass<int> s(5);

  EXPECT_TRUE(s.is_empty());
  EXPECT_FALSE(s.is_full());
  EXPECT_EQ(s.size(), 5);
}

TEST(ClassStackOnMass, can_throw_when_creating_with_zero_size) {
  ASSERT_THROW(TStackOnMass<int> s(0), std::invalid_argument);
}

TEST(ClassStackOnMass, can_create_with_copy_cons) {
  TStackOnMass<int> s1(3);
  s1.push(10);
  s1.push(20);
  TStackOnMass<int> s2(s1);

  EXPECT_EQ(s2.size(), 3);
  EXPECT_FALSE(s2.is_empty());
  EXPECT_FALSE(s2.is_full());
  EXPECT_EQ(s2.pop(), 20);
  EXPECT_EQ(s2.pop(), 10);
  EXPECT_TRUE(s2.is_empty());

  EXPECT_FALSE(s1.is_empty());

  EXPECT_EQ(s1.size(), 3);
  EXPECT_EQ(s1.pop(), 20);
  EXPECT_EQ(s1.pop(), 10);
  EXPECT_TRUE(s1.is_empty());
}

TEST(ClassStackOnMass, can_get_top) {
  TStackOnMass<int> s(3);
  s.push(42);

  EXPECT_EQ(s.top(), 42);
  EXPECT_EQ(s.size(), 3);
  EXPECT_FALSE(s.is_empty());
  EXPECT_FALSE(s.is_full());
}

TEST(ClassStackOnMass, can_set_top) {
  TStackOnMass<int> s(3);
  s.push(42);

  s.top() = 52;

  EXPECT_EQ(s.top(), 52);
  EXPECT_EQ(s.size(), 3);
  EXPECT_FALSE(s.is_empty());
  EXPECT_FALSE(s.is_full());
  EXPECT_EQ(s.pop(), 52);
  EXPECT_TRUE(s.is_empty());
}

TEST(ClassStackOnMass, can_throw_when_get_top_in_empty) {
  TStackOnMass<int> s(3);

  ASSERT_THROW(s.top(), std::underflow_error);
}

TEST(ClassStackOnMass, can_push) {
  TStackOnMass<int> s(2);

  EXPECT_TRUE(s.is_empty());

  s.push(1);

  EXPECT_EQ(s.size(), 2);
  EXPECT_FALSE(s.is_empty());
  EXPECT_FALSE(s.is_full());
  EXPECT_EQ(s.top(), 1);

  s.push(2);

  EXPECT_EQ(s.size(), 2);
  EXPECT_FALSE(s.is_empty());
  EXPECT_TRUE(s.is_full());
  EXPECT_EQ(s.top(), 2);
}

TEST(ClassStackOnMass, can_throw_when_push_in_full) {
  TStackOnMass<int> s(2);
  s.push(1);
  s.push(2);

  ASSERT_THROW(s.push(3), std::overflow_error);

  EXPECT_EQ(s.size(), 2);
  EXPECT_FALSE(s.is_empty());
  EXPECT_TRUE(s.is_full());
  EXPECT_EQ(s.pop(), 2);
  EXPECT_EQ(s.pop(), 1);
}

TEST(ClassStackOnMass, can_pop) {
  TStackOnMass<int> s(3);
  s.push(100);
  s.push(200);

  EXPECT_EQ(s.size(), 3);
  EXPECT_FALSE(s.is_empty());
  EXPECT_FALSE(s.is_full());
  EXPECT_EQ(s.pop(), 200);
  EXPECT_EQ(s.top(), 100);

  EXPECT_EQ(s.pop(), 100);
  EXPECT_EQ(s.size(), 3);
  EXPECT_TRUE(s.is_empty());
  EXPECT_FALSE(s.is_full());
}

TEST(ClassStackOnMass, can_throw_when_pop_in_empty) {
  TStackOnMass<int> s(3);

  ASSERT_THROW(s.pop(), std::underflow_error);
}

TEST(ClassStackOnMass, can_combinate_push_and_pop) {
  TStackOnMass<int> s(3);
  s.push(1);
  s.push(2);
  s.push(3);

  EXPECT_TRUE(s.is_full());
  EXPECT_EQ(s.top(), 3);
  EXPECT_EQ(s.pop(), 3);
  EXPECT_FALSE(s.is_full());
  EXPECT_EQ(s.top(), 2);

  s.push(4);
  EXPECT_TRUE(s.is_full());

  EXPECT_EQ(s.pop(), 4);
  EXPECT_EQ(s.pop(), 2);
  EXPECT_EQ(s.pop(), 1);
  EXPECT_TRUE(s.is_empty());

  s.push(5);
  EXPECT_EQ(s.top(), 5);
  EXPECT_EQ(s.pop(), 5);
  EXPECT_TRUE(s.is_empty());
}
