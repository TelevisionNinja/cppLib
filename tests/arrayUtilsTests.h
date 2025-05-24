#ifndef ARRAYUTILSTESTS_H
#define ARRAYUTILSTESTS_H

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

    // binary search leftmost and right most tests
    std::vector<int> array = {1,2,3,3,3,6,7,8,9,10}; // len = 10
    int value = 3;
    int left = 0;
    int right = array.size() - 1;

    UNIT_TEST_EQ(tvnj::binarySearchFirstSwappablePosition(array, value, left, right), 2);
    UNIT_TEST_EQ(tvnj::binarySearchLastSwappablePosition(array, value, left, right), 4);

    array = {1,2,3,4,5,6,7,7,7,10};
    value = 7;
    UNIT_TEST_EQ(tvnj::binarySearchFirstSwappablePosition(array, value, left, right), 6);
    UNIT_TEST_EQ(tvnj::binarySearchLastSwappablePosition(array, value, left, right), 8);

    array = {3,3,3,4,5,6,7,8,9,10};
    value = 3;
    UNIT_TEST_EQ(tvnj::binarySearchFirstSwappablePosition(array, value, left, right), 0);
    UNIT_TEST_EQ(tvnj::binarySearchLastSwappablePosition(array, value, left, right), 2);

    array = {1,2,3,4,5,6,7,8,8,8};
    value = 8;
    UNIT_TEST_EQ(tvnj::binarySearchFirstSwappablePosition(array, value, left, right), 7);
    UNIT_TEST_EQ(tvnj::binarySearchLastSwappablePosition(array, value, left, right), 9);

    array = {1,2,3,4,5,6,7,8,9,10};
    value = 11;
    UNIT_TEST_EQ(tvnj::binarySearchFirstSwappablePosition(array, value, left, right), 9);
    UNIT_TEST_EQ(tvnj::binarySearchLastSwappablePosition(array, value, left, right), 9);

    array = {1,2,3,4,5,6,7,8,9,10};
    value = 0;
    UNIT_TEST_EQ(tvnj::binarySearchFirstSwappablePosition(array, value, left, right), 0);
    UNIT_TEST_EQ(tvnj::binarySearchLastSwappablePosition(array, value, left, right), 0);

    // block swap tests
    array = {1,2,3,4,5,6,7,8,9,10}; // length = 10
    left = 0;
    right = array.size() - 1;
    tvnj::blockSwap(array, left, right);
    UNIT_TEST_EQ(tvnj::join(array, ","), "6,7,8,9,10,1,2,3,4,5");

    array = {1,2,3,4,5,6,7,8,9,10}; // length = 10
    left = 3;
    right = array.size() - 1;
    tvnj::blockSwap(array, left, right);
    UNIT_TEST_EQ(tvnj::join(array, ","), "1,2,3,8,9,10,7,4,5,6");

    array = {1,2,3,4,5,6,7,8,9};
    left = 0;
    right = array.size() - 1;
    tvnj::blockSwap(array, left, right);
    UNIT_TEST_EQ(tvnj::join(array, ","), "6,7,8,9,5,1,2,3,4");

    // block swap separated blocks
    array = {1,2,3,4,5,6,7,8,9,10}; // length = 10
    int start1 = 0;
    int start2 = 5;
    int end1 = 4;
    tvnj::blockSwap(array, start1, end1, start2);
    UNIT_TEST_EQ(tvnj::join(array, ","), "6,7,8,9,10,1,2,3,4,5");

    array = {1,2,3,4,5,6,7,8,9,10};
    start1 = 0;
    start2 = 5;
    end1 = 3;
    tvnj::blockSwap(array, start1, end1, start2);
    UNIT_TEST_EQ(tvnj::join(array, ","), "6,7,8,9,5,1,2,3,4,10");

    array = {1,2,3,4,5,6,7,8,9,10};
    start1 = 0;
    start2 = 6;
    end1 = 3;
    tvnj::blockSwap(array, start1, end1, start2);
    UNIT_TEST_EQ(tvnj::join(array, ","), "7,8,9,10,5,6,1,2,3,4");

    array = {1,2,3,4,5,6,7,8,9};
    start1 = 0;
    start2 = 5;
    end1 = 3;
    tvnj::blockSwap(array, start1, end1, start2);
    UNIT_TEST_EQ(tvnj::join(array, ","), "6,7,8,9,5,1,2,3,4");

    array = {1,2,3,4,5,6,7,8,9};
    start1 = 0;
    start2 = 4;
    end1 = 3;
    tvnj::blockSwap(array, start1, end1, start2);
    UNIT_TEST_EQ(tvnj::join(array, ","), "5,6,7,8,1,2,3,4,9");

    array = {1,2,3,4,5,6,7,8,9,10}; // length = 10
    start1 = 3;
    end1 = 5;
    start2 = 7;
    tvnj::blockSwap(array, start1, end1, start2);
    UNIT_TEST_EQ(tvnj::join(array, ","), "1,2,3,8,9,10,7,4,5,6");
}

#endif
