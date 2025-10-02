#include "AhoCorasickFilter.h"

/**
 * time: O(n)
 * returns filtered string
 */
std::string tvnj::AhoCorasickFilter::filter(const std::string& string, const std::string& censoredString) {
    tvnj::AhoCorasick::AhoCorasickNode* node = this->root;
    std::unordered_map<size_t, size_t> indices;

    // empty string case is removed as it does not make sense in a filtering function

    size_t i = 0;

    while (i < string.size()) {
        const char c = string[i];
        if (node->children.contains(c)) {
            node = node->children[c];
            i++;

            if (!node->outputLinks.empty()) {
                for (tvnj::AhoCorasick::AhoCorasickNode* outputNode : node->outputLinks) { // node.outputLinks.values()
                    const size_t startIndex = i - outputNode->length;
                    indices[startIndex] = std::max(indices[startIndex], outputNode->length);
                }
            }
        }
        else if (node == this->root) {
            i++;
        }
        else {
            node = node->suffixLink;
        }
    }

    //---------

    std::string output = "";
    size_t j = 0;
    
    while (j < string.size()) {
        if (indices.contains(j)) {
            // the found longer bound is always in the array bounds because of the DFA
            // loop is unrolled by 1 iteration fo have all loop logic in the required iterations
            // all accept indices will have return lengths greater than 0
            output += censoredString;

            size_t endIndex = j + indices[j];
            j++;

            while (j < endIndex) {
                /*
                intersection case:
                0 * * *
                  1 * * * * *

                subset case:
                0 * * * *
                  1 * *

                disjoint case:
                0 * * * _ _
                            6 * * *
                */

                if (indices.contains(j)) {
                    const size_t secondEndIndex = j + indices[j];
                    endIndex = std::max(secondEndIndex, endIndex);
                }

                output += censoredString;
                j++;
            }
        }
        else {
            output += string[j];
            j++;
        }
    }

    return output;
}
