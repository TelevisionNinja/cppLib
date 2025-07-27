#ifndef PROBLEMSTESTS_H
#define PROBLEMSTESTS_H

#include "../src/unitTest.h"
#include "../src/problems.h"
#include "../src/stringUtils.h"

void problemsTests() {
    UNIT_TEST_EQ(tvnj::join(tvnj::minimumCoins(10, {10,1,5}), ", "), "10");
    UNIT_TEST_EQ(tvnj::join(tvnj::minimumCoins(10, {1,5}), ", "), "5, 5");
    UNIT_TEST_EQ(tvnj::join(tvnj::longestIncreasingSubsequence({5,2,8,6,3,6,9,5})), "2 3 6 9");
    UNIT_TEST_EQ(tvnj::join(tvnj::longestIncreasingSubsequence({3,1,8,2,5})), "1 2 5");
}

#endif
