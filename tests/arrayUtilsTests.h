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
    UNIT_TEST(tvnj::indexOfNaiveSkip(testone, testtwo), 1);
    UNIT_TEST(tvnj::indexOfNaiveSkipLast(testone, testtwo), 1);
    UNIT_TEST(tvnj::indexOfNaiveSkip(testone, testsix), -1);
    UNIT_TEST(tvnj::indexOfNaiveSkipLast(testone, testsix), -1);
    UNIT_TEST(tvnj::indexOfNaiveSkip(testone, testfive), 0);
    UNIT_TEST(tvnj::indexOfNaiveSkipLast(testone, testfive), 0);
    UNIT_TEST(tvnj::indexOfNaiveSkip(testone, testone), 0);
    UNIT_TEST(tvnj::indexOfNaiveSkipLast(testone, testone), 0);
    UNIT_TEST(tvnj::indexOfNaiveSkip(testthree, testfive), 0);
    UNIT_TEST(tvnj::indexOfNaiveSkipLast(testthree, testfive), 1);
    UNIT_TEST(tvnj::indexOfNaiveSkip(testfour, testfive), 2);
    UNIT_TEST(tvnj::indexOfNaiveSkipLast(testfour, testfive), 3);
}
