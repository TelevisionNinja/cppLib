#include "problems.h"
#include "arrayUtils.h"
#include <unordered_map>

std::vector<int> tvnj::minimumCoins(const int &price, const std::vector<int> &coinsTypes) {
    if (price == 0) {
        return {};
    }

    std::unordered_map<int, std::vector<int>> memoization;

    for (int i = 1; i <= price; i++) {
        for (int j = 0, n = coinsTypes.size(); j < n; j++) {
            const int currentCoin = coinsTypes[j];

            if (currentCoin < i) {
                const int newPrice = i - currentCoin;

                if (memoization.contains(newPrice)) {
                    std::vector<int> result = memoization[newPrice];

                    if (memoization.contains(i)) {
                        if (result.size() + 1 < memoization[i].size()) {
                            result.push_back(currentCoin);
                            memoization[i] = result;
                        }
                    }
                    else {
                        result.push_back(currentCoin);
                        memoization[i] = result;
                    }
                }
            }
            else if (currentCoin == i) {
                memoization[i] = {currentCoin};
            }
        }
    }

    if (memoization.contains(price)) {
        return memoization[price];
    }

    return {};
}

std::vector<int> tvnj::longestIncreasingSubsequence(const std::vector<int> &sequence) {
    std::vector<int> counts = tvnj::ones<int>(sequence.size());
    std::vector<int> previous;

    for (size_t i = 0; i < sequence.size(); i++) {
        previous.push_back(-1);
    }

    int maxEnding = 0;

    for (size_t i = 0; i < sequence.size() - 1; i++) {
        int current = sequence[i];
        for (size_t j = i + 1; j < sequence.size(); j++) {
            int next = sequence[j];
            if (current < next) {
                if (counts[i] >= counts[j]) {
                    previous[j] = i;
                    counts[j] = counts[i] + 1;

                    if (counts[j] > counts[maxEnding]) {
                        maxEnding = j;
                    }
                }
            }
        }
    }

    std::vector<int> result;

    while (maxEnding != -1) {
        result.push_back(sequence[maxEnding]);
        maxEnding = previous[maxEnding];
    }

    tvnj::reverse(result);

    return result;
}
