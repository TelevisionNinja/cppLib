#include "arrayUtils.h"

/**
 * returns a boolean for whether the main array constains a subset that is in the same order as the sub array
 * 
 * @param {*} arr 
 * @param {*} subArr 
 * @returns 
 */
template <typename type>
bool tvnj::hasSubArrInOrder(std::vector<type> arr, std::vector<type> subArr) {
    const int subArrLen = subArr.size();

    // empty set
    if (!subArrLen) {
        return true;
    }

    const type firstElement = subArr[0];
    int i = 0;
    const int arrLen = arr.size() - subArrLen;

    while (i <= arrLen) {
        if (arr[i] == firstElement) {
            int j = 1,
                indexSkip = 0;

            while (j < subArrLen) {
                const type compareElement = arr[i + j];

                if (!indexSkip && compareElement == firstElement) {
                    indexSkip = j;
                }

                if (compareElement == subArr[j]) {
                    j++;
                }
                else {
                    if (!indexSkip) {
                        i += j + 1;
                    }
                    else {
                        i += indexSkip;
                    }

                    break;
                }
            }

            if (j == subArrLen) {
                return true;
            }
        }
        else {
            i++;
        }
    }

    return false;
}

/**
 * returns a boolean for whether the sub array is a subset of the main array
 * 
 * @param {*} arr 
 * @param {*} subArr 
 * @returns 
 */
template <typename type>
bool tvnj::hasSubArr(std::vector<type> arr, std::vector<type> subArr) {
    const int arrLen = arr.size(),
        subArrLen = subArr.size();

    for (int i = 0; i < subArrLen; i++) {
        const type element = subArr[i];
        int j = 0;

        while (j < arrLen && element != arr[j]) {
            j++;
        }

        if (j == arrLen) {
            return false;
        }
    }

    return true;
}