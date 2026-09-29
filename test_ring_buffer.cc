#include "ringBuffer.hpp"
#include "ringBuffer.hpp"

#include <gtest/gtest.h>
#include<stdexcept>

TEST(PushStoresElement, test1){
  RingBuffer<int,5> a;
  a.push(6);
  // Expect equality.
  EXPECT_EQ(a.front(), 6);
}

TEST(PopRemovesOldestElement, test1){
  RingBuffer<int,5> a;
  a.push(6);
  a.push(7);
  a.pop();
  a.push(8);
  // Expect equality.
  EXPECT_EQ(a.front(), 7);
  EXPECT_EQ(a.size(), 2);
}

TEST(WrapAroundPreservesFIFO, test1){
  RingBuffer<int, 3> a;
  a.push(1);
  a.push(2);
  a.push(3);
  a.pop();
  a.pop();
  a.push(4);
  a.push(5);
  EXPECT_EQ(a.front(),3);
  EXPECT_EQ(a.size(),3);
  a.pop();
  a.push(6);
  EXPECT_EQ(a.front(),4);
  EXPECT_EQ(a.size(),3);
  a.pop();
  EXPECT_EQ(a.front(), 5);
  EXPECT_EQ(a.size(), 2);
  a.pop();
  EXPECT_EQ(a.front(),6);
  EXPECT_EQ(a.size(),1);
}
TEST(WrapTest, test1){
  RingBuffer<int,5> a;
  a.push(1);
  a.push(2);
  a.pop();
  a.push(3);
  a.push(4);
  a.push(5);
  a.pop();
  a.pop();
  a.pop();
  a.push(6);
  // Expect equality.
  EXPECT_EQ(a.front(), 5);
  EXPECT_EQ(a.size(), 2);
}

TEST(PushToFullBufferThrows, test1){
  RingBuffer<int,2> a;
  a.push(1);
  a.push(2);
  try{
    a.push(3);
    FAIL() << "Expected std::overflow_error";
  }catch (const std::overflow_error& e){
    EXPECT_STREQ(e.what(),"buffer is full");
  }
}

TEST(FrontFromEmptyBufferThrows, test1){
  RingBuffer <int,2> a;
  try{
    a.front();
    FAIL() << "Expected std::overflow_error";
  }catch (const std::logic_error& e){
    EXPECT_STREQ(e.what(),"buffer is empty");
  }
}

TEST(PopFromEmptyBufferThrows, test1){
  RingBuffer<int,2> a;
  a.push(1);
  a.push(2);
  a.pop();
  a.pop();
  try{
    a.pop();
    FAIL() << "Expected std::overflow_error";
  }catch (const std::logic_error& e){
    EXPECT_STREQ(e.what(),"buffer is empty");
  }
}

TEST(EMPTYFULL, test1){
  RingBuffer<int,2> a;
  EXPECT_EQ(a.empty(), true);
  EXPECT_EQ(a.full(),false);
  a.push(1);
  EXPECT_EQ(a.empty(), false);
  EXPECT_EQ(a.full(), false);
  a.push(2);
  EXPECT_EQ(a.empty(), false);
  EXPECT_EQ(a.full(), true);
}