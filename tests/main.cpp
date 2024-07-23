#include <iostream>

#include "heapTests.h"
#include "doublyLinkedListTest.h"
#include "stringUtilsTests.h"

int main() {
    maxHeapTests();
    doublyLinkedListTests();
    stringUtilsTests();

    std::cout << "Tests ended";
    return 0;
}
