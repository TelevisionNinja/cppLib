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

        split(std::string str, std::string delimiter),
        splitNTimesLeft(std::string str, std::string delimiter, int n, int index = 0),
        splitNTimesRight(std::string str, std::string delimiter, int n, int index = -1),

        splitWhitespace(std::string str);

    //-------------------------------------------------

    std::string trim(std::string str),
        trimLeft(std::string str),
        trimRight(std::string str),

        trimChar(std::string str, char trimChar),
        trimCharLeft(std::string str, char trimChar),
        trimCharRight(std::string str, char trimChar),

        trimSubstr(std::string str, std::string trimSubstr),
        trimSubstrLeft(std::string str, std::string trimSubstr),
        trimSubstrRight(std::string str, std::string trimSubstr),

        trimCharArr(std::string str, std::vector<char> charArr),
        trimCharSet(std::string str, std::unordered_set<char> charSet),
        trimCharSetLeft(std::string str, std::unordered_set<char> charSet),
        trimCharSetRight(std::string str, std::unordered_set<char> charSet),

        trimSubstrArr(std::string str, std::vector<std::string> substrArr),
        trimSubstrArrLeft(std::string str, std::vector<std::string> substrArr),
        trimSubstrArrRight(std::string str, std::vector<std::string> substrArr);

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

        n--;

        if (n < 0) {
            return "";
        }

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
