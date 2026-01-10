#include "AhoCorasickFilter.h"
#include "../stringUtils.h"

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

                    if (indices.contains(startIndex)) {
                        indices[startIndex] = std::max(indices[startIndex], outputNode->length);
                    }
                    else {
                        indices[startIndex] = outputNode->length;
                    }
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
            // loop is unrolled by 1 iteration to have all loop logic in the required iterations
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

/**
 * time: O(n)
 * returns filtered string
 */
std::string tvnj::AhoCorasickFilter::filterAndIgnoreChars(const std::string& string, const std::string& censoredString, std::unordered_set<char> ignoreChars) {
    tvnj::AhoCorasick::AhoCorasickNode* node = this->root;
    std::unordered_map<size_t, size_t> indices;

    // empty string case is removed as it does not make sense in a filtering function

    size_t i = 0;

    while (i < string.size()) {
        const char c = string[i];

        if (ignoreChars.contains(c)) {
            i++;
        }
        else if (node->children.contains(c)) {
            node = node->children[c];

            if (!node->outputLinks.empty()) {
                for (tvnj::AhoCorasick::AhoCorasickNode* outputNode : node->outputLinks) { // node.outputLinks.values()
                    if (outputNode->length != 0) {
                        if (indices.contains(i)) {
                            indices[i] = std::max(indices[i], outputNode->length);
                        }
                        else {
                            indices[i] = outputNode->length;
                        }
                    }
                }
            }

            i++;
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
    size_t j = string.size();
    
    while (j > 0) {
        j--;

        if (ignoreChars.contains(string[j]) || !indices.contains(j)) {
            output += string[j];
        }
        else {
            // the found longer bound is always in the array bounds because of the DFA
            // loop is unrolled by 1 iteration to have all loop logic in the required iterations
            // all accept indices will have return lengths greater than 0
            output += censoredString;

            size_t length = indices[j];
            size_t k = 1;

            while (k < length) {
                j--;

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

                if (ignoreChars.contains(string[j])) {
                    output += string[j];
                }
                else {
                    if (indices.contains(j)) {
                        const size_t otherLength = indices[j];

                        if (length - k < otherLength) {
                            length = otherLength + k; // no minus 1 because k is 1 behind j here
                        }
                    }

                    output += censoredString;
                    k++;
                }
            }
        }
    }

    tvnj::reverse(output);

    return output;
}
