#include <iostream>

#include "heapTests.h"
#include "doublyLinkedListTest.h"
#include "stringUtilsTests.h"
#include "arrayUtilsTests.h"
#include "mathUtilsTests.h"
#include "problemsTests.h"

int main() {
    maxHeapTests();
    doublyLinkedListTests();
    stringUtilsTests();
    arrayUtilsTests();
    mathUtilsTests();
    problemsTests();

    std::cout << "Tests ended";
    return 0;
}
