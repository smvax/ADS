// Copyright 2026 smvax

#include <gtest/gtest.h>
#include "../lib_multistack_on_mass/multistack_on_mass.h"

TEST(ClassMultiStackOnMass, can_create_with_valid_size_and_parts) {
  TMultiStackOnMass<int> ms(3, 9);

  EXPECT_TRUE(ms.is_empty());
  EXPECT_FALSE(ms.is_full());
}

TEST(ClassMultiStackOnMass, can_throw_when_creating_with_zero_parts) {
  ASSERT_THROW(TMultiStackOnMass<int> ms(0, 5), std::invalid_argument);
}

TEST(ClassMultiStackOnMass, can_throw_when_capacity_less_than_parts_num) {
  ASSERT_THROW(TMultiStackOnMass<int> ms(5, 3), std::invalid_argument);
}

TEST(ClassMultiStackOnMass, can_create_with_copy_cons) {
  TMultiStackOnMass<int> ms1(2, 4);
  ms1.push(0, 10);
  ms1.push(1, 20);
  TMultiStackOnMass<int> ms2(ms1);

  EXPECT_FALSE(ms2.is_empty());
  EXPECT_EQ(ms2.pop(0), 10);
  EXPECT_EQ(ms2.pop(1), 20);
  EXPECT_TRUE(ms2.is_empty());

  EXPECT_FALSE(ms1.is_empty());
  EXPECT_EQ(ms1.pop(0), 10);
}

TEST(ClassMultiStackOnMass, can_get_and_set_top) {
  TMultiStackOnMass<int> ms(2, 4);
  ms.push(0, 42);

  EXPECT_EQ(ms.top(0), 42);

  ms.top(0) = 52;

  EXPECT_EQ(ms.top(0), 52);
  EXPECT_EQ(ms.pop(0), 52);
}

TEST(ClassMultiStackOnMass, can_throw_when_take_top_in_empty_part) {
  TMultiStackOnMass<int> ms(2, 4);

  ASSERT_THROW(ms.top(0), std::underflow_error);
}

TEST(ClassMultiStackOnMass, can_push_and_pop_from_different_parts) {
  TMultiStackOnMass<int> ms(3, 6);
  ms.push(0, 100);
  ms.push(1, 200);
  ms.push(2, 300);

  EXPECT_FALSE(ms.is_empty());
  EXPECT_EQ(ms.pop(2), 300);
  EXPECT_EQ(ms.pop(1), 200);
  EXPECT_EQ(ms.pop(0), 100);
  EXPECT_TRUE(ms.is_empty());
}

TEST(ClassMultiStackOnMass, can_throw_when_pop_in_empty_part) {
  TMultiStackOnMass<int> ms(2, 4);

  ASSERT_THROW(ms.pop(0), std::underflow_error);
}

TEST(ClassMultiStackOnMass,
     can_throw_when_methods_called_with_wrong_part_index) {
  TMultiStackOnMass<int> ms(2, 4);

  ASSERT_THROW(ms.push(2, 10), std::out_of_range);
  ASSERT_THROW(ms.is_empty_part(2), std::out_of_range);
  ASSERT_THROW(ms.is_full_part(2), std::out_of_range);

  ASSERT_THROW(ms.get_left(2), std::out_of_range);
  ASSERT_THROW(ms.get_right(2), std::out_of_range);
  ASSERT_THROW(ms.get_top(2), std::logic_error);
}

TEST(ClassMultiStackOnMass,
     can_trigger_repack_when_part_is_full_but_multistack_is_not) {
  TMultiStackOnMass<int> ms(3, 3);
  ms.push(0, 10);
  EXPECT_TRUE(ms.is_full_part(0));
  EXPECT_FALSE(ms.is_full());
  ASSERT_NO_THROW(ms.push(0, 20));
  EXPECT_EQ(ms.pop(0), 20);
  EXPECT_EQ(ms.pop(0), 10);
}

TEST(ClassMultiStackOnMass, can_throw_when_push_in_completely_full_multistack) {
  TMultiStackOnMass<int> ms(2, 2);
  ms.push(0, 1);
  ms.push(1, 2);

  EXPECT_TRUE(ms.is_full());
  ASSERT_THROW(ms.push(0, 3), std::overflow_error);
}

TEST(ClassMultiStackOnMass, complex_combinate_push_pop_and_repack) {
  TMultiStackOnMass<int> ms(2, 4);
  ms.push(0, 1);
  ms.push(0, 2);
  ms.push(0, 3);
  ms.push(1, 10);

  EXPECT_TRUE(ms.is_full());
  EXPECT_EQ(ms.pop(0), 3);
  EXPECT_EQ(ms.pop(0), 2);
  EXPECT_EQ(ms.pop(0), 1);
  EXPECT_EQ(ms.pop(1), 10);
  EXPECT_TRUE(ms.is_empty());
}

TEST(ClassMultiStackOnMass, constructor_calculates_remainders_correctly) {
  TMultiStackOnMass<int> ms(3, 7);

  EXPECT_EQ(ms.get_left(0), 0);
  EXPECT_EQ(ms.get_right(0), 2);
  EXPECT_EQ(ms.get_top(0), -1);
  EXPECT_EQ(ms.get_left(1), 3);
  EXPECT_EQ(ms.get_right(1), 4);
  EXPECT_EQ(ms.get_left(2), 5);
  EXPECT_EQ(ms.get_right(2), 6);
}