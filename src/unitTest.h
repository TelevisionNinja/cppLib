#ifndef UNIT_TEST

#include <iostream>

#define UNIT_TEST(x) { if (!(x)) { std::cout << __FUNCTION__ << " failed. Line: " << __LINE__ << "\n"; } }

#endif
