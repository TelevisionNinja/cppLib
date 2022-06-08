#ifndef ARRAYUTILS_H
#define ARRAYUTILS_H

#include <vector>
#include <unordered_set>

namespace tvnj {
    /**
     * returns a boolean for whether the main vector contains a subset that is in the same order as the sub vector
     * 
     * @param {*} arr 
     * @param {*} subArr 
     * @returns 
     */
    template <typename type>
    bool hasSubArrInOrder(std::vector<type> arr, std::vector<type> subArr) {
        const int subArrLen = subArr.size();

        // empty set
        if (subArrLen == 0) {
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

                    if (indexSkip == 0 && compareElement == firstElement) {
                        indexSkip = j;
                    }

                    if (compareElement == subArr[j]) {
                        j++;
                    }
                    else {
                        if (indexSkip == 0) {
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
     * returns a boolean for whether the sub vector is a subset of the main vector
     * O(n + m)
     * 
     * @param {*} arr 
     * @param {*} subArr 
     * @returns 
     */
    template <typename type>
    bool hasSubArr1(std::vector<type> arr, std::vector<type> subArr) {
        std::unordered_set<type> elementMap(std::make_move_iterator(arr.begin()), std::make_move_iterator(arr.end()));

        const int subArrLen = subArr.size();

        for (int i = 0; i < subArrLen; i++) {
            if (!elementMap.contains(subArr[i])) {
                return false;
            }
        }

        return true;
    }

    /**
     * returns a boolean for whether the sub vector is a subset of the main vector
     * O(nm)
     * 
     * @param {*} arr 
     * @param {*} subArr 
     * @returns 
     */
    template <typename type>
    bool hasSubArr2(std::vector<type> arr, std::vector<type> subArr) {
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

    /**
     * python like array slicing
     * 
     * @param str 
     * @param start inclusive
     * @param end exclusive by default
     * @param step increment
     * @param inclusive bool for making the parameter "end" inclusive
     * @return a new vector
     */
    template <typename type>
    std::vector<type> slice(std::vector<type> vector, int start, int end, int step = 1, bool inclusive = false) {
        const int len = vector.size();

        if (start < 0) {
            start += len;
        }

        if (end < 0) {
            end += len;
        }

        if (step == 0) {
            step = 1;
        }

        std::vector<type> newVector;

        if (step > 0) {
            if (start <= end) {
                if (start < 0) {
                    start = 0;
                }

                if (end > len) {
                    end = len - 1;
                    inclusive = true;
                }

                int i = start;

                while (i < end) {
                    newVector.push_back(vector[i]);
                    i += step;
                }

                if (inclusive && i == end) {
                    newVector.push_back(vector[i]);
                }
            }
        }
        else {
            if (end <= start) {
                if (start >= len) {
                    start = len - 1;
                }

                if (end < 0) {
                    end = 0;
                    inclusive = true;
                }

                int i = start;

                while (i > end) {
                    newVector.push_back(vector[i]);
                    i += step;
                }

                if (inclusive && i == end) {
                    newVector.push_back(vector[i]);
                }
            }
        }

        return newVector;
    }
}

#endif
