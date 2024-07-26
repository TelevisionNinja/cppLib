#include <iostream>

#include "heapTests.h"
#include "doublyLinkedListTest.h"
#include "stringUtilsTests.h"
#include "arrayUtilsTests.h"
#include "mathUtilsTests.h"

int main() {
    maxHeapTests();
    doublyLinkedListTests();
    stringUtilsTests();
    arrayUtilsTests();
    mathUtilsTests();

    std::cout << "Tests ended";
    return 0;
}
