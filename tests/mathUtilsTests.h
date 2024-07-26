#include "../src/unitTest.h"
#include "../src/mathUtils.h"
#include <cmath>

void mathUtilsTests() {
    UNIT_TEST_EQ(tvnj::exponentiationBySquaring(-1, -2), 1.0);
    UNIT_TEST_EQ(tvnj::exponentiationBySquaring(-1, -1), -1.0);
    UNIT_TEST_EQ(tvnj::exponentiationBySquaring(-1, 0), 1.0);
    UNIT_TEST_EQ(tvnj::exponentiationBySquaring(-1, 1), -1.0);
    UNIT_TEST_EQ(tvnj::exponentiationBySquaring(-1, 2), 1.0);
    UNIT_TEST_EQ(tvnj::exponentiationBySquaring(-1, 3), -1.0);

    UNIT_TEST_EQ(tvnj::exponentiationBySquaring(1, -2), 1.0);
    UNIT_TEST_EQ(tvnj::exponentiationBySquaring(1, -1), 1.0);
    UNIT_TEST_EQ(tvnj::exponentiationBySquaring(1, 0), 1.0);
    UNIT_TEST_EQ(tvnj::exponentiationBySquaring(1, 1), 1.0);
    UNIT_TEST_EQ(tvnj::exponentiationBySquaring(1, 2), 1.0);
    UNIT_TEST_EQ(tvnj::exponentiationBySquaring(1, 3), 1.0);

    UNIT_TEST_EQ(tvnj::exponentiationBySquaring(2, -2), 1.0 / 4.0);
    UNIT_TEST_EQ(tvnj::exponentiationBySquaring(2, -1), 1.0 / 2.0);
    UNIT_TEST_EQ(tvnj::exponentiationBySquaring(2, 0), 1.0);
    UNIT_TEST_EQ(tvnj::exponentiationBySquaring(2, 1), 2.0);
    UNIT_TEST_EQ(tvnj::exponentiationBySquaring(2, 2), 4.0);
    UNIT_TEST_EQ(tvnj::exponentiationBySquaring(2, 3), 8.0);

    UNIT_TEST_EQ(tvnj::exponentiationBySquaring(-1, -2), std::pow(-1, -2));
    UNIT_TEST_EQ(tvnj::exponentiationBySquaring(-1, -1), std::pow(-1, -1));
    UNIT_TEST_EQ(tvnj::exponentiationBySquaring(-1, 0), std::pow(-1, 0));
    UNIT_TEST_EQ(tvnj::exponentiationBySquaring(-1, 1), std::pow(-1, 1));
    UNIT_TEST_EQ(tvnj::exponentiationBySquaring(-1, 2), std::pow(-1, 2));
    UNIT_TEST_EQ(tvnj::exponentiationBySquaring(-1, 3), std::pow(-1, 3));

    UNIT_TEST_EQ(tvnj::exponentiationBySquaring(1, -2), std::pow(1, -2));
    UNIT_TEST_EQ(tvnj::exponentiationBySquaring(1, -1), std::pow(1, -1));
    UNIT_TEST_EQ(tvnj::exponentiationBySquaring(1, 0), std::pow(1, 0));
    UNIT_TEST_EQ(tvnj::exponentiationBySquaring(1, 1), std::pow(1, 1));
    UNIT_TEST_EQ(tvnj::exponentiationBySquaring(1, 2), std::pow(1, 2));
    UNIT_TEST_EQ(tvnj::exponentiationBySquaring(1, 3), std::pow(1, 3));

    UNIT_TEST_EQ(tvnj::exponentiationBySquaring(2, -2), std::pow(2, -2));
    UNIT_TEST_EQ(tvnj::exponentiationBySquaring(2, -1), std::pow(2, -1));
    UNIT_TEST_EQ(tvnj::exponentiationBySquaring(2, 0), std::pow(2, 0));
    UNIT_TEST_EQ(tvnj::exponentiationBySquaring(2, 1), std::pow(2, 1));
    UNIT_TEST_EQ(tvnj::exponentiationBySquaring(2, 2), std::pow(2, 2));
    UNIT_TEST_EQ(tvnj::exponentiationBySquaring(2, 3), std::pow(2, 3));
}
