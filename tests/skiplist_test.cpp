#include <gtest/gtest.h>

#include "skiplist.hpp"

TEST(SkipListTest, Trivial) {
    SkipList<int, int> s{12};
}

// start run main
int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}