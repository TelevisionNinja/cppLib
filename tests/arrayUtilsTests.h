#include "../src/unitTest.h"
#include "../src/arrayUtils.h"
#include <vector>

void arrayUtilsTests() {
    std::vector<std::string> testone = {"a","b","c"},
        testtwo = {"b","c"},
        testthree = {"a","a","b","c"},
        testfour = {"b","c","a","a"},
        testfive = {"a"},
        testsix = {"d"};
    UNIT_TEST_EQ(tvnj::indexOfNaiveSkip(testone, testtwo), 1);
    UNIT_TEST_EQ(tvnj::indexOfNaiveSkipLast(testone, testtwo), 1);
    UNIT_TEST_EQ(tvnj::indexOfNaiveSkip(testone, testsix), -1);
    UNIT_TEST_EQ(tvnj::indexOfNaiveSkipLast(testone, testsix), -1);
    UNIT_TEST_EQ(tvnj::indexOfNaiveSkip(testone, testfive), 0);
    UNIT_TEST_EQ(tvnj::indexOfNaiveSkipLast(testone, testfive), 0);
    UNIT_TEST_EQ(tvnj::indexOfNaiveSkip(testone, testone), 0);
    UNIT_TEST_EQ(tvnj::indexOfNaiveSkipLast(testone, testone), 0);
    UNIT_TEST_EQ(tvnj::indexOfNaiveSkip(testthree, testfive), 0);
    UNIT_TEST_EQ(tvnj::indexOfNaiveSkipLast(testthree, testfive), 1);
    UNIT_TEST_EQ(tvnj::indexOfNaiveSkip(testfour, testfive), 2);
    UNIT_TEST_EQ(tvnj::indexOfNaiveSkipLast(testfour, testfive), 3);
}
