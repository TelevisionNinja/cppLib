#include <iostream>

#include "heapTests.h"
#include "doublyLinkedListTest.h"
#include "stringUtilsTests.h"
#include "arrayUtilsTests.h"

int main() {
    maxHeapTests();
    doublyLinkedListTests();
    stringUtilsTests();
    arrayUtilsTests();

    std::cout << "Tests ended";
    return 0;
}
