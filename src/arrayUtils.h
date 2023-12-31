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

    /**
     * @brief in place
     * time O(n / 2) = O(n)
     * space O(1)
     * 
     * @tparam T 
     * @param array 
     * @param start 
     * @param end 
     */
    template<typename T>
    void reverse(std::vector<T> &array, const int &start, const int &end) {
        const int middle = (end - start) / 2;

        for (int i = 0; i <= middle; i++) {
            const int startIndex = start + i,
                lastIndex = end - i;
            T temp = array[startIndex];
            array[startIndex] = array[lastIndex];
            array[lastIndex] = temp;
        }
    }

    /**
     * @brief in place
     * blocks must be equal length
     * time O(n / 2) = O(n)
     * space O(1)
     * 
     * @tparam T 
     * @param array 
     * @param start 
     * @param end 
     */
    template<typename T>
    void blockSwap(std::vector<T> &array, const int &start, const int &end) {
        const int middle = (end - start) / 2;

        for (int i = 0; i <= middle; i++) {
            const int start1Index = start + i,
                start2Index = start1Index + middle + 1;
            T temp = array[start1Index];
            array[start1Index] = array[start2Index];
            array[start2Index] = temp;
        }
    }

    /**
     * @brief in place
     * time O(p * n + (1 - p) * n + n) = O(n)
     * space O(1)
     * 
     * @tparam T 
     * @param array 
     * @param start1 start of subarray 1
     * @param start2 start of subarray 2
     * @param end end of subarray 2
     */
    template<typename T>
    void rotateUsingReverse(std::vector<T> &array, const int &start1, const int &start2, const int &end) {
        const int partition = end - start2;

        reverse(array, start1, end);
        reverse(array, start1, partition);
        reverse(array, partition + 1, end);
    }

    /**
     * @brief in place
     * time O(p * n + (1 - p) * n + n) = O(2n) = O(n)
     *      Omega(n / 2) = Omega(n)
     * space O(1)
     * 
     * @tparam T 
     * @param array 
     * @param start1 start of subarray 1
     * @param start2 start of subarray 2
     * @param end end of subarray 2
     */
    template<typename T>
    void rotate(std::vector<T> &array, const int &start1, const int &start2, const int &end) {
        if (end - start2 + 1 == start2 - start1) {
            blockSwap(array, start1, end);
        }
        else {
            rotateUsingReverse(array, start1, start2, end);
        }
    }

    /**
     * @brief returns the index of where the first occurrence of value is. it will always return a position in the array even if the value if not found
     * time O(log_2(n))
     * space O(1)
     * 
     * @tparam T 
     * @param array 
     * @param value 
     * @param left 
     * @param right 
     * @return const int 
     */
    template<typename T>
    int binarySearchFirst(const std::vector<T> &array, const T &value, int left, int right) {
        while (left < right) {
            const int m = left + (right - left) / 2; // no overflow formula
            T currentValue = array[m];

            // go to the left of the same values for stability
            if (currentValue == value) {
                right = m;
            }
            else if (currentValue < value) {
                left = m + 1;
            }
            else {
                right = m - 1;
            }
        }

        return left;
    }

    /**
     * @brief returns the index of where the last occurrence of value is. it will always return a position in the array even if the value if not found
     * time O(log_2(n))
     * space O(1)
     * 
     * @tparam T 
     * @param array 
     * @param value 
     * @param left 
     * @param right 
     * @return const int 
     */
    template<typename T>
    int binarySearchLast(const std::vector<T> &array, const T &value, int left, int right) {
        right++;

        while (left < right) {
            const int m = left + (right - left) / 2; // no overflow formula

            // go to the right of the same values for stability
            if (array[m] > value) {
                right = m;
            }
            else {
                left = m + 1;
            }
        }

        if (left == 0) {
            return left;
        }

        return left - 1;
    }
}

#endif
