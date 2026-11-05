#include <sstream>
#include <stdexcept>
#include <gtest/gtest.h>
#include "TVector.h"

TEST(TVector, can_create_default_vector)
{
  TVector<int> v;

  EXPECT_EQ(0u, v.size());
  EXPECT_TRUE(v.empty());
}

TEST(TVector, can_create_vector_with_positive_length)
{
  ASSERT_NO_THROW(TVector<int> v(5));
}

TEST(TVector, vector_with_value_is_filled_with_this_value)
{
  TVector<int> v(3, 7);

  EXPECT_EQ(3u, v.size());
  EXPECT_EQ(7, v[0]);
  EXPECT_EQ(7, v[1]);
  EXPECT_EQ(7, v[2]);
}

TEST(TVector, can_set_and_get_element)
{
  TVector<int> v(4);
  v[0] = 4;

  EXPECT_EQ(4, v[0]);
}

TEST(TVector, throws_when_at_with_too_large_index)
{
  TVector<int> v(5);

  EXPECT_THROW(v.at(5), std::out_of_range);
}

TEST(TVector, copied_vector_is_equal_to_source_one)
{
  TVector<int> v(5);
  for (int i = 0; i < 5; i++) {
    v[i] = i;
  }

  TVector<int> v1 = v;

  EXPECT_EQ(v.size(), v1.size());
  for (int i = 0; i < 5; i++) {
    EXPECT_EQ(v[i], v1[i]);
  }
}

TEST(TVector, copied_vector_has_its_own_memory)
{
  TVector<int> v(5);
  v[0] = 1;

  TVector<int> v1 = v;
  v1[0] = 999;

  EXPECT_NE(v[0], v1[0]);
}

TEST(TVector, can_assign_vector_to_itself)
{
  TVector<int> v(5);
  for (int i = 0; i < 5; i++) {
    v[i] = i;
  }

  v = v;

  EXPECT_EQ(0, v[0]);
  EXPECT_EQ(4, v[4]);
}

TEST(TVector, can_assign_vectors_of_different_size)
{
  TVector<int> v(5);
  TVector<int> v1(10);
  for (int i = 0; i < 10; i++) {
    v1[i] = i;
  }

  v = v1;

  EXPECT_EQ(10u, v.size());
  EXPECT_EQ(9, v[9]);
}

TEST(TVector, push_back_adds_element_to_the_end)
{
  TVector<int> v;
  v.push_back(1);
  v.push_back(2);

  EXPECT_EQ(2u, v.size());
  EXPECT_EQ(1, v.front());
  EXPECT_EQ(2, v.back());
}

TEST(TVector, push_back_grows_capacity_and_keeps_elements)
{
  TVector<int> v;
  for (int i = 0; i < 5; i++) {
    v.push_back(i);
  }

  EXPECT_EQ(5u, v.size());
  EXPECT_EQ(8u, v.getCapacity());
  for (int i = 0; i < 5; i++) {
    EXPECT_EQ(i, v[i]);
  }
}

TEST(TVector, pop_back_removes_last_element)
{
  TVector<int> v;
  v.push_back(1);
  v.push_back(2);

  v.pop_back();

  EXPECT_EQ(1u, v.size());
  EXPECT_EQ(1, v.back());
}

TEST(TVector, can_insert_in_the_middle)
{
  TVector<int> v;
  v.push_back(1);
  v.push_back(2);
  v.push_back(3);

  v.insert(1, 99);

  EXPECT_EQ(4u, v.size());
  EXPECT_EQ(1, v[0]);
  EXPECT_EQ(99, v[1]);
  EXPECT_EQ(2, v[2]);
  EXPECT_EQ(3, v[3]);
}

TEST(TVector, can_insert_at_the_end_but_not_further)
{
  TVector<int> v(3, 0);

  EXPECT_NO_THROW(v.insert(3, 5));
  EXPECT_EQ(5, v.back());
  EXPECT_THROW(v.insert(10, 5), std::out_of_range);
}

TEST(TVector, can_erase_element)
{
  TVector<int> v;
  v.push_back(1);
  v.push_back(2);
  v.push_back(3);

  v.erase(0);

  EXPECT_EQ(2u, v.size());
  EXPECT_EQ(2, v[0]);
  EXPECT_EQ(3, v[1]);
}

TEST(TVector, throws_when_erase_with_too_large_index)
{
  TVector<int> v(3);

  EXPECT_THROW(v.erase(3), std::out_of_range);
}

TEST(TVector, can_push_back_after_clear)
{
  TVector<int> v(3, 1);

  v.clear();
  v.push_back(5);

  EXPECT_EQ(1u, v.size());
  EXPECT_EQ(5, v[0]);
}

TEST(TVector, throws_when_front_or_back_of_empty_vector)
{
  TVector<int> v;

  EXPECT_THROW(v.front(), std::out_of_range);
  EXPECT_THROW(v.back(), std::out_of_range);
}

TEST(TVector, can_read_vector)
{
  TVector<int> v;
  std::stringstream sstr;
  sstr << "1 2 3 4 5\n";

  sstr >> v;

  EXPECT_EQ(5u, v.size());
  for (int i = 0; i < 5; i++) {
    EXPECT_EQ(i + 1, v[i]);
  }
}

TEST(TVector, can_write_vector)
{
  TVector<int> v;
  for (int i = 1; i <= 5; i++) {
    v.push_back(i);
  }
  std::stringstream sstr;

  sstr << v;

  EXPECT_EQ("1 2 3 4 5 ", sstr.str());
}