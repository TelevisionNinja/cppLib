#include "problems.h"

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
