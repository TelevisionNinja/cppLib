#ifndef UNIT_TEST

#include <iostream>

#define UNIT_TEST(value, expected) { if (!(value == expected)) { std::cout << __FUNCTION__ << "() failed at line: " << __LINE__ << "\nValue:\n" << value << "\n\nExpected:\n" << expected << "\n\n"; } }

#endif
