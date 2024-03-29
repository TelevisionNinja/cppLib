#include "mathUtils.h"

/**
 * 
 * @param base 
 * @param power 
 * @return float 
 */
float tvnj::exponentiationBySquaring(float base, unsigned int power) {
    float result = 1;
    float exponentiation = base;
    unsigned int i = power;

    while (i != 0) { // i > 0
        if (i % 2 != 0) {
            result *= exponentiation;
        }

        exponentiation *= exponentiation;
        i >>= 1;
    }

    return result;
}

/**
 * 
 * @param base 
 * @param power 
 * @return float 
 */
float tvnj::exponentiationBySquaring(float base, int power) {
    float result = 1;
    float exponentiation = base;
    bool isNegative = power < 0;
    int i = power;

    if (isNegative) {
        i *= -1;
    }

    while (i != 0) { // i > 0
        if (i % 2 != 0) {
            result *= exponentiation;
        }

        exponentiation *= exponentiation;
        i >>= 1;
    }

    if (isNegative) {
        return 1 / result;
    }

    return result;
}
