#include <deque>
#include <sstream>
#include <stdexcept>
#include <gtest/gtest.h>
#include "TStack.h"

TEST(TStack, can_create_empty_stack)
{
    TStack<int> s;

    EXPECT_TRUE(s.empty());
    EXPECT_EQ(0u, s.size());
}

TEST(TStack, push_adds_element_on_top)
{
    TStack<int> s;
    s.push(1);
    s.push(2);
    s.push(3);

    EXPECT_EQ(3, s.top());
    EXPECT_EQ(3u, s.size());
    EXPECT_FALSE(s.empty());
}

TEST(TStack, pop_removes_top_element)
{
    TStack<int> s;
    s.push(1);
    s.push(2);
    s.push(3);

    s.pop();

    EXPECT_EQ(2, s.top());
    EXPECT_EQ(2u, s.size());
}

TEST(TStack, elements_come_out_in_reverse_order)
{
    TStack<int> s;
    for (int i = 0; i < 100; i++) {
        s.push(i);                       // заставляем вектор несколько раз расшириться
    }

    for (int i = 99; i >= 0; i--) {
        EXPECT_EQ(i, s.top());
        s.pop();
    }
    EXPECT_TRUE(s.empty());
}

TEST(TStack, throws_when_pop_or_top_on_empty_stack)
{
    TStack<int> s;

    EXPECT_THROW(s.pop(), std::out_of_range);
    EXPECT_THROW(s.top(), std::out_of_range);
}

TEST(TStack, can_read_top_of_const_stack)
{
    TStack<int> s;
    s.push(7);
    const TStack<int>& cs = s;

    EXPECT_EQ(7, cs.top());
}

TEST(TStack, can_push_after_clear)
{
    TStack<int> s;
    s.push(1);
    s.push(2);

    s.clear();

    EXPECT_TRUE(s.empty());
    s.push(7);
    EXPECT_EQ(7, s.top());
    EXPECT_EQ(1u, s.size());
}

TEST(TStack, works_with_std_deque_as_container)
{
    TStack<int, std::deque<int>> s;
    s.push(1);
    s.push(2);

    EXPECT_EQ(2, s.top());
    s.pop();
    EXPECT_EQ(1, s.top());
}

TEST(TStack, can_read_stack)
{
    TStack<int> s;
    std::stringstream sstr;
    sstr << "1 2 3\n";

    sstr >> s;

    EXPECT_EQ(3u, s.size());
    EXPECT_EQ(3, s.top());
}

TEST(TStack, can_write_stack)
{
    TStack<int> s;
    s.push(1);
    s.push(2);
    s.push(3);
    std::stringstream sstr;

    sstr << s;

    EXPECT_EQ("1 2 3 ", sstr.str());
}