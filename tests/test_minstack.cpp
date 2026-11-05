#include <stdexcept>
#include <gtest/gtest.h>
#include "TMinStack.h"

TEST(TMinStack, can_create_empty_stack)
{
    TMinStack<int> s;

    EXPECT_TRUE(s.empty());
    EXPECT_EQ(0u, s.size());
}

TEST(TMinStack, push_and_top_work_like_in_usual_stack)
{
    TMinStack<int> s;
    s.push(5);
    s.push(3);

    EXPECT_EQ(3, s.top());
    EXPECT_EQ(2u, s.size());
}

TEST(TMinStack, min_is_updated_on_push)
{
    TMinStack<int> s;
    s.push(5);
    EXPECT_EQ(5, s.min());
    s.push(3);
    EXPECT_EQ(3, s.min());
    s.push(7);
    EXPECT_EQ(3, s.min());
    s.push(2);
    EXPECT_EQ(2, s.min());
}

TEST(TMinStack, min_is_restored_on_pop)
{
    TMinStack<int> s;
    s.push(5);
    s.push(3);
    s.push(7);
    s.push(2);

    s.pop();
    EXPECT_EQ(3, s.min());
    s.pop();
    EXPECT_EQ(3, s.min());
    s.pop();
    EXPECT_EQ(5, s.min());
}

TEST(TMinStack, min_works_with_equal_elements)
{
    TMinStack<int> s;
    s.push(3);
    s.push(3);

    s.pop();

    EXPECT_EQ(3, s.min());
    EXPECT_EQ(1u, s.size());
}

TEST(TMinStack, throws_when_pop_top_or_min_on_empty_stack)
{
    TMinStack<int> s;

    EXPECT_THROW(s.pop(), std::out_of_range);
    EXPECT_THROW(s.top(), std::out_of_range);
    EXPECT_THROW(s.min(), std::out_of_range);
}

TEST(TMinStack, can_read_min_of_const_stack)
{
    TMinStack<int> s;
    s.push(4);
    s.push(2);
    const TMinStack<int>& cs = s;

    EXPECT_EQ(2, cs.min());
    EXPECT_EQ(2, cs.top());
}

TEST(TMinStack, clear_resets_min)
{
    TMinStack<int> s;
    s.push(5);
    s.push(1);

    s.clear();
    s.push(8);

    EXPECT_EQ(8, s.min());
    EXPECT_EQ(1u, s.size());
}