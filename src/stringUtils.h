#ifndef STRINGUTILS_H
#define STRINGUTILS_H

#include <string>
#include <regex>
#include <vector>
#include <unordered_set>

namespace tvnj {
    std::string rotate(std::string str, int n);

    //-------------------------------------------------

    std::string cutOff(std::string str, int charLimit);

    //-------------------------------------------------

    std::string replaceHTMLEntities(std::string str),
        replaceHTMLEntitiesSorted(std::string str);

    //-------------------------------------------------

    std::string escapeRegex(std::string str);

    //-------------------------------------------------

    bool includesPhrase1(std::string str, std::string phrase, bool caseSensitive = true),
        includesPhrase2(std::string str, std::string phrase, bool caseSensitive = true);

    //-------------------------------------------------

    std::string replaceAll1(std::string str, std::string substr, std::string replacement),
        replaceAll2(std::string str, std::string substr, std::string replacement),

        replaceFirst(std::string str, std::string substr, std::string replacement, int index = 0),
        replaceLast(std::string str, std::string substr, std::string replacement, int index = -1),

        replaceNTimesLeft(std::string str, std::string substr, std::string replacement, int n, int index = 0),
        replaceNTimesRight(std::string str, std::string substr, std::string replacement, int n, int index = -1);

    //-------------------------------------------------

    std::vector<std::string> split(std::string str, char delimiter = ' '),
        splitNTimesLeft(std::string str, char delimiter, int n, int index = 0),
        splitNTimesRight(std::string str, char delimiter, int n, int index = -1),

        split(std::string str, std::unordered_set<char> charSet),
        splitNTimesLeft(std::string str, std::unordered_set<char> delimiter, int n, int index = 0),
        splitNTimesRight(std::string str, std::unordered_set<char> delimiter, int n, int index = -1),

        split(std::string str, std::string delimiter),
        splitNTimesLeft(std::string str, std::string delimiter, int n, int index = 0),
        splitNTimesRight(std::string str, std::string delimiter, int n, int index = -1),

        splitWhitespace(std::string str);

    //-------------------------------------------------

    std::string trim(std::string str),
        trimLeft(std::string str),
        trimRight(std::string str),

        trim(std::string str, char trimChar),
        trimLeft(std::string str, char trimChar),
        trimRight(std::string str, char trimChar),

        trim(std::string str, std::string trimSubstr),
        trimLeft(std::string str, std::string trimSubstr),
        trimRight(std::string str, std::string trimSubstr),

        trim(std::string str, std::vector<char> charArr),
        trim(std::string str, std::unordered_set<char> charSet),
        trimLeft(std::string str, std::unordered_set<char> charSet),
        trimRight(std::string str, std::unordered_set<char> charSet),

        trim(std::string str, std::vector<std::string> substrArr),
        trimLeft(std::string str, std::vector<std::string> substrArr),
        trimRight(std::string str, std::vector<std::string> substrArr);

    //-------------------------------------------------

    int indexOf(std::string str, std::string substr, int index = 0),
        indexOfLast(std::string str, std::string substr, int index = -1),

        indexOfTwoWay(std::string str, std::string substr, int index = 0),

        indexOfNaive(std::string str, std::string substr, int index = 0),
        indexOfNaiveLast(std::string str, std::string substr, int index = -1),

        indexOfNaiveSkip(std::string str, std::string substr, int index = 0),
        indexOfNaiveSkipLast(std::string str, std::string substr, int index = -1),

        indexOfChar(std::string str, char substr, int index = 0),
        indexOfCharLast(std::string str, char substr, int index = -1);

    //-------------------------------------------------

    std::vector<int> indexOfAll(std::string str, std::string substr, int index = 0, bool includeOverlap = true);

    //-------------------------------------------------

    /**
     * joins the elements of a vector and returns a string
     * 
     * @param {*} vec 
     * @param {*} separator 
     * @param {*} indexStart inclusive
     * @param {*} indexEnd exclusive
     * @returns 
     */
    template <typename type>
    std::string join(std::vector<type> vec, std::string separator = " ", int indexStart = 0, int indexEnd = -1) {
        int n = vec.size();

        if (indexEnd >= 0 && indexEnd <= n) {
            n = indexEnd;
        }

        if (n == 0 || indexStart < 0 || indexStart >= n) {
            return "";
        }

        n--;

        std::string s = "";

        for (int i = indexStart; i < n; i++) {
            s += std::to_string(vec[i]) + separator;
        }

        return s + std::to_string(vec[n]);
    }

    std::string join(std::vector<std::string> vec, std::string separator = " ", int indexStart = 0, int indexEnd = -1);

    //-------------------------------------------------

    std::vector<std::string> cmdLnToArgArr(std::string cmdLn, bool throwError = true);

    //-------------------------------------------------

    std::string toProperCase(std::string str),
        toLowerCase(std::string str),
        toUpperCase(std::string str);

    //-------------------------------------------------

    bool startsWith(std::string str, std::string substr, int index = 0),
        endsWith(std::string str, std::string substr, int length = -1);

    //-------------------------------------------------

    std::string alternateStrings(std::string str1, std::string str2);

    //-------------------------------------------------

    std::string repeat(std::string str, int n);

    //-------------------------------------------------

    std::string padLeft(std::string str, int len, char c = ' '),
        padRight(std::string str, int len, char c = ' ');
}

#endif
