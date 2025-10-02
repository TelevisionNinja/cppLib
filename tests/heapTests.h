#ifndef HEAPTESTS_H
#define HEAPTESTS_H

#include "../src/unitTest.h"
#include "../src/data_structures/MaxBinaryHeap.h"
#include "../src/data_structures/MinBinaryHeap.h"

void maxHeapTests() {
    tvnj::MaxBinaryHeap<int> heapA({1, 3, 5, 4, 6, 13, 10, 9, 8, 15, 17});
    UNIT_TEST_EQ(heapA.toString(), "[17, 15, 13, 9, 6, 5, 10, 4, 8, 3, 1]");
    UNIT_TEST_NEQ(heapA.toString(), "[1, 3, 5, 4, 6, 13, 10, 9, 8, 15, 17]");

    tvnj::MaxBinaryHeap<int> heapB({10, 5, 3, 2, 4});
    heapB.insert(15);
    UNIT_TEST_EQ(heapB.toString(), "[15, 5, 10, 2, 4, 3]");
    UNIT_TEST_NEQ(heapB.toString(), "[10, 5, 3, 2, 4, 15]");

    tvnj::MaxBinaryHeap<int> heapC({ 10, 5, 3, 2, 4});
    int popped = 0;
    UNIT_TEST_EQ(heapC.remove(popped), true);
    UNIT_TEST_NEQ(heapC.toString(), "[10, 5, 3, 2, 4]");
    UNIT_TEST_EQ(popped, 10);
    UNIT_TEST_EQ(heapC.toString(), "[5, 4, 3, 2]");

    tvnj::MinBinaryHeap<int> heapAmin({1, 3, 5, 4, 6, 13, 10, 9, 8, 15, 17});
    UNIT_TEST_NEQ(heapAmin.toString(), "[17, 15, 13, 9, 6, 5, 10, 4, 8, 3, 1]");
    UNIT_TEST_EQ(heapAmin.toString(), "[1, 3, 5, 4, 6, 13, 10, 9, 8, 15, 17]");

    tvnj::MinBinaryHeap<int> heapBmin({13, 16, 31, 41, 51, 100});
    UNIT_TEST_EQ(heapBmin.toString(), "[13, 16, 31, 41, 51, 100]");
    UNIT_TEST_NEQ(heapBmin.toString(), "[100, 51, 41, 31, 16, 13]");

    popped = 0;
    UNIT_TEST_EQ(heapBmin.remove(popped), true);
    UNIT_TEST_NEQ(heapBmin.toString(), "[13, 16, 31, 41, 51, 100]");
    UNIT_TEST_EQ(popped, 13);
    UNIT_TEST_EQ(heapBmin.toString(), "[16, 41, 31, 100, 51]");
}

#endif
