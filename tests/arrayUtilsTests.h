#include "../src/unitTest.h"
#include "../src/arrayUtils.h"
#include "../src/stringUtils.h"
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

    std::vector<char> testing2 = {'a', 'b', 'c', 'd', 'e', 'f', 'g'};

    UNIT_TEST_EQ(tvnj::join(tvnj::slice(testing2, 0, 0), ""), "");
    UNIT_TEST_EQ(tvnj::join(tvnj::slice(testing2, 0, 0, -1), ""), "");
    UNIT_TEST_EQ(tvnj::join(tvnj::slice(testing2, 0, 0, 1, true), ""), "a");
    UNIT_TEST_EQ(tvnj::join(tvnj::slice(testing2, 0, 0, -1, true), ""), "a");
    UNIT_TEST_EQ(tvnj::join(tvnj::slice(testing2, 0, testing2.size()), ""), "abcdefg");
    UNIT_TEST_EQ(tvnj::join(tvnj::slice(testing2, -100000, testing2.size(), 1), ""), "abcdefg");
    UNIT_TEST_EQ(tvnj::join(tvnj::slice(testing2, 0, 100000000), ""), "abcdefg");
    UNIT_TEST_EQ(tvnj::join(tvnj::slice(testing2, 0, 100000000, 1, true), ""), "abcdefg");
    UNIT_TEST_EQ(tvnj::join(tvnj::slice(testing2, testing2.size(), 0), ""), "");

    UNIT_TEST_EQ(tvnj::join(tvnj::slice(testing2, -testing2.size(), testing2.size()), ""), "abcdefg");
    UNIT_TEST_EQ(tvnj::join(tvnj::slice(testing2, 1, testing2.size()), ""), "bcdefg");
    UNIT_TEST_EQ(tvnj::join(tvnj::slice(testing2, 0, testing2.size() - 1), ""), "abcdef");
    UNIT_TEST_EQ(tvnj::join(tvnj::slice(testing2, 1, testing2.size() - 1), ""), "bcdef");

    UNIT_TEST_EQ(tvnj::join(tvnj::slice(testing2, testing2.size(), 0, -1), ""), "gfedcb");
    UNIT_TEST_EQ(tvnj::join(tvnj::slice(testing2, testing2.size(), -10000000, -1), ""), "gfedcba");
    UNIT_TEST_EQ(tvnj::join(tvnj::slice(testing2, 0, testing2.size(), -1), ""), "");
    UNIT_TEST_EQ(tvnj::join(tvnj::slice(testing2, testing2.size()-1, 0, -1), ""), "gfedcb");
    UNIT_TEST_EQ(tvnj::join(tvnj::slice(testing2, testing2.size(), 0, -1, true), ""), "gfedcba");
    UNIT_TEST_EQ(tvnj::join(tvnj::slice(testing2, testing2.size()-1, 0, -1, true), ""), "gfedcba");

    UNIT_TEST_EQ(tvnj::join(tvnj::slice(testing2, 0, testing2.size(), 2), ""), "aceg");

    UNIT_TEST_EQ(tvnj::join(tvnj::slice(testing2, testing2.size(), 0, -2), ""), "gec");
    UNIT_TEST_EQ(tvnj::join(tvnj::slice(testing2, testing2.size(), 0, -2, true), ""), "geca");
    UNIT_TEST_EQ(tvnj::join(tvnj::slice(testing2, 0, testing2.size(), -2), ""), "");
}
