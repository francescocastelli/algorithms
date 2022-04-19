#include "skipList.h"
#include <gtest/gtest.h>

namespace datastruct {
namespace {

class SkipListTest : public ::testing::TestWithParam<int> {

protected:
  SkipListTest() {}

  void SetUp() override 
  {
      key = GetParam();
  }

  int key;
  SkipList s;
};

TEST_P(SkipListTest, Insertion) {
    ASSERT_FALSE(s.search(key));
    s.insert(key);
    ASSERT_TRUE(s.search(key));
}

const int keys[] = {10, 23, 1, 0, 30, 12, 1};

INSTANTIATE_TEST_SUITE_P(SkipListSingleInsertion, 
						 SkipListTest, 
						 testing::ValuesIn(keys));

} // namespace
} // namespace datastruct
