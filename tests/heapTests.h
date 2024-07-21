#include "../src/unitTest.h"
#include "../src/data structures/MaxBinaryHeap.h"

void maxHeapTests() {
    tvnj::MaxBinaryHeap<int> heapA({1, 3, 5, 4, 6, 13, 10, 9, 8, 15, 17});
    UNIT_TEST(heapA.toString() == "[17, 15, 13, 9, 6, 5, 10, 4, 8, 3, 1]");

    tvnj::MaxBinaryHeap<int> heapB({10, 5, 3, 2, 4});
    heapB.insert(15);
    UNIT_TEST(heapB.toString() == "[15, 5, 10, 2, 4, 3]");

    tvnj::MaxBinaryHeap<int> heapC({ 10, 5, 3, 2, 4});
    int popped = 0;
    heapC.remove(popped);
    UNIT_TEST(popped == 10 && heapC.toString() == "[5, 4, 3, 2]");
}
