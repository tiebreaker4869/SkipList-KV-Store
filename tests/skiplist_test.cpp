#include <cstdint>
#include <gtest/gtest.h>
#include <map>

#include "skiplist.hpp"

using Key = uint64_t;

using Value = uint64_t;

TEST(SkipTest, Empty) {
  SkipList<Key, Value> skip_list{};
  EXPECT_EQ(skip_list.Get(1), nullptr);
  EXPECT_EQ(skip_list.Contains(1), false);
}

TEST(SkipTest, InsertSimple) {
  // simply test insert functionality
  SkipList<Key, Value> skip_list{};
  skip_list.Insert(1, 1);
  EXPECT_EQ(*skip_list.Get(1), 1);
  EXPECT_EQ(skip_list.Contains(1), true);
}

TEST(SkipTest, DeleteSimple) {
  // simple test delete functionality
  SkipList<Key, Value> skip_list{};
  skip_list.Delete(1);
  EXPECT_EQ(skip_list.Get(1), nullptr);
  skip_list.Insert(1, 4);
  EXPECT_EQ(skip_list.Contains(1), true);
  skip_list.Delete(1);
  EXPECT_EQ(skip_list.Get(1), nullptr);
}

TEST(SkipTest, SizeTest) {
  SkipList<Key, Value> skip_list{};
  for (int i = 0; i < 100; i++) {
    skip_list.Insert(i, i);
    EXPECT_EQ(skip_list.Size(), i + 1);
  }

  for (int i = 0; i < 100; i++) {
    skip_list.Delete(i);
    EXPECT_EQ(skip_list.Size(), 100 - i - 1);
  }
}

TEST(SkipTest, DiffTestAgainstMap) {
  constexpr int N = 1000000;
  std::map<Key, Value> map{};
  SkipList<Key, Value> skip_list{};

  for (int i = 0; i < N; i++) {
    int test_func = rand() % 5;
    Key key = rand();
    Value value = rand();
    // choose tested operation randomly
    // 0 - Insert, 1 - Contains, 2 - Get, 3 - Delete, 4 - Size
    switch (test_func) {
    case 0:
      map[key] = value;
      if (skip_list.Contains(key)) {
        skip_list.Delete(key);
      }
      skip_list.Insert(key, value);
      break;
    case 1:
      EXPECT_EQ(skip_list.Contains(key), map.count(key));
      break;
    case 2:
      if (map.count(key)) {
        EXPECT_EQ(*skip_list.Get(key), map[key]);
      } else {
        EXPECT_EQ(skip_list.Get(key), nullptr);
      }
      break;
    case 3:
      map.erase(key);
      skip_list.Delete(key);
      break;
    case 4:
      EXPECT_EQ(skip_list.Size(), map.size());
      break;
    default:
      break;
    }
  }
}

// start run main
int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}