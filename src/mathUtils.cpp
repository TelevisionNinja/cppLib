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
