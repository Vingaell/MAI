#include <gtest/gtest.h>
#include "allocator.hpp"
#include "stack.hpp"

TEST(TestS1, Test1) {
    ASSERT_TRUE(1 == 1);
}

TEST(Allocator, Vector_push_back) {
    std::vector<int, mai::Allocator<int>> v;
    v.push_back(42);
    v.push_back(13);
    EXPECT_EQ(v[0], 42);
    EXPECT_EQ(v[1], 13);
}

TEST(Allocator, Vector_deleting_elements) {
    std::vector<int, mai::Allocator<int>> v;
    v.push_back(42);
    v.push_back(13);
    v.pop_back();
    EXPECT_EQ(v[0], 42);
    EXPECT_EQ(v.size(), 1);
}

TEST(Allocator, Vector_changing_elements) {
    std::vector<int, mai::Allocator<int>> v;
    v.push_back(42);
    v.push_back(13);
    v.pop_back();
    v.push_back(5);
    EXPECT_EQ(v[0], 42);
    EXPECT_EQ(v[1], 5);
}

TEST(Stack, push) {
    mai::Stack<int, 100, mai::Allocator<int, 2>> s;
    s.push(42);
    s.push(15);
    EXPECT_EQ(s[0], 42);
    EXPECT_EQ(s[1], 15);
}

TEST(Stack, pop) {
    mai::Stack<int, 2, mai::Allocator<int, 2>> s;
    s.push(42);
    s.push(5);
    int n = s.pop();
    EXPECT_EQ(n, 5);
}

TEST(Stack, pop_and_push) {
    mai::Stack<int, 2, mai::Allocator<int, 2>> s;
    s.push(42);
    s.push(5);
    EXPECT_EQ(s[0], 42);
    EXPECT_EQ(s[1], 5);
    int n = s.pop();
    s.push(67);
    EXPECT_EQ(n, 5);
    EXPECT_EQ(s[0], 42);
    EXPECT_EQ(s[1], 67);
}

TEST(Stack, size) {
    mai::Stack<int, 2, mai::Allocator<int, 2>> s;
    EXPECT_EQ(s.size(), 0);
    s.push(13);
    EXPECT_EQ(s.size(), 1);
    s.push(32);
    EXPECT_EQ(s.size(), 2);
    s.pop();
    s.pop();
    EXPECT_EQ(s.size(), 0);
}

TEST(Stack, empty) {
    mai::Stack<int, 2, mai::Allocator<int, 2>> s;
    EXPECT_TRUE(s.empty());
    s.push(1);
    EXPECT_FALSE(s.empty());
    s.pop();
    EXPECT_TRUE(s.empty());
}

TEST(Stack, copy_operator) {
    mai::Stack<int, 10, mai::Allocator<int, 10>> s1;
    mai::Stack<int, 10, mai::Allocator<int, 10>> s2;
    s1.push(2);
    s1.push(3);
    s2 = s1;
    EXPECT_EQ(s2[0], 2);
    EXPECT_EQ(s2[1], 3);
}

TEST(Iterator, begin) {
    mai::Stack<int, 100, mai::Allocator<int, 2>> s;
    s.push(42);
    s.push(15);
    auto it = s.begin();
    EXPECT_EQ(*it, 42);
}

TEST(Iterator, increment) {
    mai::Stack<int, 100, mai::Allocator<int, 2>> s;
    s.push(42);
    s.push(15);
    auto it = s.begin();
    EXPECT_EQ(*it, 42);
    ++it;
    EXPECT_EQ(*it, 15);
}

TEST(Iterator, change_value) {
    mai::Stack<int, 100, mai::Allocator<int, 2>> s;
    s.push(42);
    s.push(15);
    auto it = s.begin();
    EXPECT_EQ(*it, 42);
    *it = 4;
    EXPECT_EQ(s[0], 4);
}

TEST(ConstIterator, begin) {
    mai::Stack<int, 100, mai::Allocator<int, 2>> s;
    s.push(42);
    s.push(15);
    auto it = s.cbegin();
    EXPECT_EQ(*it, 42);
}

TEST(ConstIterator, increment) {
    mai::Stack<int, 100, mai::Allocator<int, 2>> s;
    s.push(42);
    s.push(15);
    auto it = s.cbegin();
    EXPECT_EQ(*it, 42);
    ++it;
    EXPECT_EQ(*it, 15);
}
