#include <deque>
#include <sstream>
#include <stdexcept>
#include <gtest/gtest.h>
#include "TQueue.h"

TEST(TQueue, can_create_empty_queue)
{
  TQueue<int> q;

  EXPECT_TRUE(q.empty());
  EXPECT_EQ(0u, q.size());
}

TEST(TQueue, can_create_queue_with_zero_capacity_and_push)
{
  TQueue<int> q(0);

  ASSERT_NO_THROW(q.push(1));
  EXPECT_EQ(1, q.front());
}

TEST(TQueue, push_adds_element_to_the_back)
{
  TQueue<int> q;
  q.push(1);
  q.push(2);

  EXPECT_EQ(1, q.front());
  EXPECT_EQ(2, q.back());
  EXPECT_EQ(2u, q.size());
}

TEST(TQueue, pop_removes_element_from_the_front)
{
  TQueue<int> q;
  q.push(1);
  q.push(2);
  q.push(3);

  q.pop();

  EXPECT_EQ(2, q.front());
  EXPECT_EQ(3, q.back());
  EXPECT_EQ(2u, q.size());
}

TEST(TQueue, throws_when_pop_front_or_back_on_empty_queue)
{
  TQueue<int> q;

  EXPECT_THROW(q.pop(), std::out_of_range);
  EXPECT_THROW(q.front(), std::out_of_range);
  EXPECT_THROW(q.back(), std::out_of_range);
}

TEST(TQueue, ring_wraps_around)
{
  TQueue<int> q;                     // 4 ячейки
  for (int i = 1; i <= 4; i++) {
    q.push(i);
  }
  q.pop();
  q.pop();
  q.push(5);                         // пишется в начало массива
  q.push(6);

  EXPECT_EQ(4u, q.size());
  EXPECT_EQ(3, q.front());
  EXPECT_EQ(6, q.back());
}

TEST(TQueue, grows_and_keeps_order)
{
  TQueue<int> q;
  for (int i = 1; i <= 5; i++) {     // пятый элемент не влезает в 4 ячейки
    q.push(i);
  }

  EXPECT_EQ(5u, q.size());
  EXPECT_EQ(1, q.front());
  EXPECT_EQ(5, q.back());
}

TEST(TQueue, grows_when_ring_is_wrapped)
{
  TQueue<int> q;
  for (int i = 1; i <= 4; i++) {
    q.push(i);
  }
  q.pop();
  q.pop();
  q.push(5);
  q.push(6);                         // кольцо полно, head = 2
  q.push(7);                         // перепаковка

  int expected[] = {3, 4, 5, 6, 7};
  for (int x : expected) {
    EXPECT_EQ(x, q.front());
    q.pop();
  }
  EXPECT_TRUE(q.empty());
}

TEST(TQueue, can_push_after_clear)
{
  TQueue<int> q;
  q.push(1);
  q.push(2);

  q.clear();

  EXPECT_TRUE(q.empty());
  q.push(7);
  EXPECT_EQ(7, q.front());
}

TEST(TQueue, copied_queue_is_independent)
{
  TQueue<int> a;
  a.push(1);
  a.push(2);

  TQueue<int> b = a;
  b.pop();

  EXPECT_EQ(2u, a.size());
  EXPECT_EQ(1, a.front());
  EXPECT_EQ(1u, b.size());
}

TEST(TQueue, works_with_std_deque_as_container)
{
  TQueue<int, std::deque<int>> q;
  for (int i = 1; i <= 5; i++) {
    q.push(i);
  }

  EXPECT_EQ(1, q.front());
  EXPECT_EQ(5, q.back());
}

TEST(TQueue, can_read_queue)
{
  TQueue<int> q;
  std::stringstream sstr;
  sstr << "1 2 3\n";

  sstr >> q;

  EXPECT_EQ(3u, q.size());
  EXPECT_EQ(1, q.front());
  EXPECT_EQ(3, q.back());
}

TEST(TQueue, write_prints_elements_in_queue_order)
{
  TQueue<int> q;
  for (int i = 1; i <= 4; i++) {
    q.push(i);
  }
  q.pop();
  q.pop();
  q.push(5);
  q.push(6);
  std::stringstream sstr;

  sstr << q;

  EXPECT_EQ("3 4 5 6 ", sstr.str());
}