// Copyright 2024 Marina Usova

#include <gtest/gtest.h>
#include "../lib_queue_on_mass/queue_on_mass.h"

TEST(ClassQueueOnMass, can_create_with_size_cons) {
  TQueueOnMass<int> q(5);

  EXPECT_TRUE(q.is_empty());
  EXPECT_FALSE(q.is_full());
  EXPECT_EQ(q.size(), 5);
}

TEST(ClassQueueOnMass, can_throw_when_creating_with_zero_size) {
  ASSERT_THROW(TQueueOnMass<int> q(0), std::invalid_argument);
}

TEST(ClassQueueOnMass, can_create_with_copy_cons) {
  TQueueOnMass<int> q1(3);
  q1.push(10);
  q1.push(20);
  TQueueOnMass<int> q2(q1);

  EXPECT_EQ(q2.size(), 3);
  EXPECT_FALSE(q2.is_empty());
  EXPECT_FALSE(q2.is_full());
  EXPECT_EQ(q2.pop(), 10);
  EXPECT_EQ(q2.pop(), 20);
  EXPECT_TRUE(q2.is_empty());

  EXPECT_FALSE(q1.is_empty());

  EXPECT_EQ(q1.size(), 3);
  EXPECT_EQ(q1.pop(), 10);
  EXPECT_EQ(q1.pop(), 20);
  EXPECT_TRUE(q1.is_empty());
}

TEST(ClassQueueOnMass, can_get_front) {
  TQueueOnMass<int> q(3);
  q.push(42);

  EXPECT_EQ(q.front(), 42);
  EXPECT_EQ(q.size(), 3);
  EXPECT_FALSE(q.is_empty());
  EXPECT_FALSE(q.is_full());
}

TEST(ClassQueueOnMass, can_set_front) {
  TQueueOnMass<int> q(3);
  q.push(42);

  q.front() = 52;

  EXPECT_EQ(q.front(), 52);
  EXPECT_EQ(q.size(), 3);
  EXPECT_FALSE(q.is_empty());
  EXPECT_FALSE(q.is_full());
  EXPECT_EQ(q.pop(), 52);
  EXPECT_TRUE(q.is_empty());
}

TEST(ClassQueueOnMass, can_throw_when_get_front_in_empty) {
  TQueueOnMass<int> q(3);

  ASSERT_THROW(q.front(), std::underflow_error);
}

TEST(ClassQueueOnMass, can_push) {
  TQueueOnMass<int> q(2);

  EXPECT_TRUE(q.is_empty());

  q.push(1);

  EXPECT_EQ(q.size(), 2);
  EXPECT_FALSE(q.is_empty());
  EXPECT_FALSE(q.is_full());
  EXPECT_EQ(q.front(), 1);

  q.push(2);

  EXPECT_EQ(q.size(), 2);
  EXPECT_FALSE(q.is_empty());
  EXPECT_TRUE(q.is_full());
  EXPECT_EQ(q.front(), 1);
}

TEST(ClassQueueOnMass, can_throw_when_push_in_full) {
  TQueueOnMass<int> q(2);
  q.push(1);
  q.push(2);

  ASSERT_THROW(q.push(3), std::overflow_error);
  
  EXPECT_EQ(q.size(), 2);
  EXPECT_FALSE(q.is_empty());
  EXPECT_TRUE(q.is_full());
  EXPECT_EQ(q.pop(), 1);
  EXPECT_EQ(q.pop(), 2);
}

TEST(ClassQueueOnMass, can_pop) {
  TQueueOnMass<int> q(3);
  q.push(100);
  q.push(200);

  EXPECT_EQ(q.size(), 3);
  EXPECT_FALSE(q.is_empty());
  EXPECT_FALSE(q.is_full());
  EXPECT_EQ(q.pop(), 100);
  EXPECT_EQ(q.front(), 200);

  EXPECT_EQ(q.pop(), 200);
  EXPECT_EQ(q.size(), 3);
  EXPECT_TRUE(q.is_empty());
  EXPECT_FALSE(q.is_full());
}

TEST(ClassQueueOnMass, can_throw_when_pop_in_empty) {
  TQueueOnMass<int> q(3);

  ASSERT_THROW(q.pop(), std::underflow_error);
}

TEST(ClassQueueOnMass, can_combinate_push_and_pop) {
  TQueueOnMass<int> q(3);
  q.push(1);
  q.push(2);
  q.push(3);

  EXPECT_TRUE(q.is_full());
  EXPECT_EQ(q.front(), 1);
  EXPECT_EQ(q.pop(), 1);
  EXPECT_FALSE(q.is_full());
  EXPECT_EQ(q.front(), 2);

  q.push(4);
  EXPECT_TRUE(q.is_full());

  EXPECT_EQ(q.pop(), 2);
  EXPECT_EQ(q.pop(), 3);
  EXPECT_EQ(q.pop(), 4);
  EXPECT_TRUE(q.is_empty());

  q.push(5);
  EXPECT_EQ(q.front(), 5);
  EXPECT_EQ(q.pop(), 5);
  EXPECT_TRUE(q.is_empty());
}
