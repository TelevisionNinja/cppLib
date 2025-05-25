#ifndef UNIT_TEST_EQ

#include <iostream>

#define UNIT_TEST_EQ(value, expected) { if (value != expected) { std::cout << __FUNCTION__ << "() failed UNIT_TEST_EQ at line: " << __LINE__ << "\nValue:\n" << value << "\n\nExpected:\n" << expected << "\n\n"; } }

#endif

#ifndef UNIT_TEST_NEQ

#include <iostream>

#define UNIT_TEST_NEQ(value, notExpected) { if (value == notExpected) { std::cout << __FUNCTION__ << "() failed UNIT_TEST_NEQ at line: " << __LINE__ << "\nValue:\n" << value << "\n\nNot Expected:\n" << notExpected << "\n\n"; } }

#endif
