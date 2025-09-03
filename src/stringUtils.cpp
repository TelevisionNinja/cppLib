#include "stringUtils.h"
#include <stdexcept> // throw exceptions
#include <regex>
#include "arrayUtils.h"
#include <queue>
#include <stack>

const std::unordered_set<char> whitespaceChars = {
    '\n', // 10, newline
    '\r', // 13, carriage return
    '\t', // 9, tab
    ' ', // 32, space
    '\v', // 11, vertical tab
    '\f' // 12, form feed
};

/**
 * trims a specified character from a string
 * 
 * @param {*} str str to be trimmmed
 * @param {*} trimChar char that will be trimed off of the str
 * @returns 
 */
std::string tvnj::trim(std::string str, char trimChar) {
    int end = str.size();
    while (end != 0) { // end > 0
        end--;

        if (str[end] != trimChar) {
            end++;
            break;
        }
    }

    if (end == 0) { // end <= 0
        return "";
    }

    int start = 0;
    while (str[start] == trimChar) {
        start++;
    }

    return str.substr(start, end - start);
}

/**
 * trims a specified character from the left side of a string
 * 
 * @param {*} str str to be trimmmed
 * @param {*} trimChar char that will be trimed off of the str
 * @returns 
 */
std::string tvnj::trimLeft(std::string str, char trimChar) {
    int start = 0;
    const int len = str.size();

    while (start < len) {
        if (str[start] != trimChar) {
            return str.substr(start);
        }

        start++;
    }

    return "";
}

/**
 * trims a specified character from the right side of a string
 * 
 * @param {*} str str to be trimmmed
 * @param {*} trimChar char that will be trimed off of the str
 * @returns 
 */
std::string tvnj::trimRight(std::string str, char trimChar) {
    int end = str.size();

    while (end != 0) { // end > 0
        end--;

        if (str[end] != trimChar) {
            return str.substr(0, end + 1);
        }
    }

    return "";
}

//-------------------------------------------------

/**
 * trims a substring from a string
 * 
 * @param {*} str str to be trimmmed
 * @param {*} trimSubstr substring that will be trimed off of the str
 * @returns 
 */
std::string tvnj::trim(std::string str, std::string trimSubstr) {
    const int substrLen = trimSubstr.size();
    int end = str.size();

    if (substrLen == 0 || end < substrLen) {
        return str;
    }

    int substrIndex = substrLen;
    do {
        if (substrIndex == 0) { // substrIndex <= 0
            substrIndex = substrLen;
        }

        end--;
        substrIndex--;
    }
    while (end >= 0 && str[end] == trimSubstr[substrIndex]);

    end += substrLen - substrIndex;

    if (end <= 0) {
        return "";
    }

    int strIndex = 0;
    substrIndex = 0;
    while (str[strIndex] == trimSubstr[substrIndex]) {
        strIndex++;
        substrIndex++;

        if (substrIndex == substrLen) { // substrIndex >= substrLen
            substrIndex = 0;
        }
    }

    const int start = strIndex - substrIndex;

    return str.substr(start, end - start);
}

/**
 * trims a substring from the left side of a string
 * 
 * @param {*} str str to be trimmmed
 * @param {*} trimSubstr substring that will be trimed off of the str
 * @returns 
 */
std::string tvnj::trimLeft(std::string str, std::string trimSubstr) {
    const int substrLen = trimSubstr.size(),
        len = str.size();

    if (substrLen == 0 || len < substrLen) {
        return str;
    }

    int strIndex = 0,
        substrIndex = 0;
    while (strIndex < len && str[strIndex] == trimSubstr[substrIndex]) {
        strIndex++;
        substrIndex++;

        if (substrIndex == substrLen) { // substrIndex >= substrLen
            substrIndex = 0;
        }
    }

    return str.substr(strIndex - substrIndex);
}

/**
 * trims a substring from the right side of a string
 * 
 * @param {*} str str to be trimmmed
 * @param {*} trimSubstr substring that will be trimed off of the str
 * @returns 
 */
std::string tvnj::trimRight(std::string str, std::string trimSubstr) {
    const int substrLen = trimSubstr.size();
    int strIndex = str.size();

    if (substrLen == 0 || strIndex < substrLen) {
        return str;
    }

    int substrIndex = substrLen;
    do {
        if (substrIndex == 0) { // substrIndex <= 0
            substrIndex = substrLen;
        }

        strIndex--;
        substrIndex--;
    }
    while (strIndex >= 0 && str[strIndex] == trimSubstr[substrIndex]);

    return str.substr(0, strIndex + substrLen - substrIndex);
}

//-------------------------------------------------

/**
 * postive = to the left
 * negative = to the right
 * 
 * @param {*} str 
 * @param {*} n 
 * @returns 
 */
std::string tvnj::rotate(std::string str, int n) {
    const int length = str.size(),
        index = ((n % length) + length) % length;

    /*
    limit domain to [0, length), because it is redundant to have an 'n' = length * constant + 'a difference'
    this makes 'n' = 'a difference'
    difference = n % length

    add the difference to the length to get a new value to shift the characters by
    the reason for adding is that 'n' can be negative
    shift = difference + length

    limit domain to [0, length) again because 'n' can be positive
    index = shift % length

    ---------------------------
    positive only case

    index = n % length

    ---------------------------
    negative only case

    index = (n % length) + length
    */

    return str.substr(index) + str.substr(0, index);
}

//-------------------------------------------------

/**
 * trim oversized strings
 * 
 * @param {*} str 
 * @param {*} charLimit 
 * @returns 
 */
std::string tvnj::cutOff(std::string str, size_t charLimit) {
    if (str.size() > charLimit) {
        return str.substr(0, charLimit - 3) + "...";
    }

    return str;
}

//-------------------------------------------------

const std::vector<std::string> htmlEntities = {
    "&lt;",
    "&gt;",
    "&amp;",
    "&#39;",
    "&apos;",
    "&quot;"
};
const std::vector<std::string> htmlEntityChars = {
    "<",
    ">",
    "&",
    "'",
    "'",
    "\""
};

/**
 * replaces html entities with their character equivalent
 * 
 * @param {*} str 
 * @returns 
 */
std::string tvnj::replaceHTMLEntities(std::string str) {
    const int entityLen = htmlEntities.size();

    for (int i = 0, strLen = str.size(); i < strLen; i++) {
        if (str[i] == '&') {
            for (int j = 0; j < entityLen; j++) {
                const std::string entity = htmlEntities[j];
                const int len = entity.size(),
                    lowerLen = len - 1;

                if (i + len <= strLen && str[i + lowerLen] == ';') {
                    int k = 1;

                    while (k < lowerLen && str[i + k] == entity[k]) {
                        k++;
                    }

                    if (k == lowerLen) { // k >= lowerLen
                        str.replace(i, len, htmlEntityChars[j]);
                        strLen -= lowerLen;
                        break;
                    }
                }
            }
        }
    }

    return str;
}

/**
 * replaces html entities with their character equivalent
 * 
 * the list of html entites must be sorted by increasing length
 * 
 * @param {*} str 
 * @returns 
 */
std::string tvnj::replaceHTMLEntitiesSorted(std::string str) {
    const int entityLen = htmlEntities.size();

    for (int i = 0, strLen = str.size(); i < strLen; i++) {
        if (str[i] == '&') {
            int previousLen = 0;

            for (int j = 0; j < entityLen; j++) {
                const std::string entity = htmlEntities[j];
                const int len = entity.size();

                if (i + len <= strLen) {
                    /*
                    X = entities of length n
                    if the substring of length n does not end with ';'
                    skip all X entities
                    */
                    if (len > previousLen) {
                        const int lowerLen = len - 1;

                        if (str[i + lowerLen] == ';') {
                            int k = 1;

                            while (k < lowerLen && str[i + k] == entity[k]) {
                                k++;
                            }

                            if (k == lowerLen) { // k >= lowerLen
                                str.replace(i, len, htmlEntityChars[j]);
                                strLen -= lowerLen;
                                break;
                            }
                        }
                        else {
                            previousLen = len;
                        }
                    }
                }
                else {
                    return str;
                }
            }
        }
    }

    return str;
}

//-------------------------------------------------

/**
 * escapes regex using regex
 * 
 * @param {*} str 
 */
std::string tvnj::escapeRegex(std::string str) {
    return std::regex_replace(str, std::regex("[.*+?^${}()|[\\]\\\\]"), "\\$&");
}

//-------------------------------------------------

/**
 * check if a phrase appears in a string
 * 
 * @param {*} str 
 * @param {*} phrase string with no leading or trailing whitespace
 * @param {*} caseSensitive 
 * @returns 
 */
bool tvnj::includesPhrase(std::string str, std::string phrase, bool caseSensitive) {
    if (!caseSensitive) {
        str = tvnj::toLowerCase(str);
        phrase = tvnj::toLowerCase(phrase);
    }

    const int substrLen = phrase.size(),
        limit = str.size() - substrLen;

    bool isWhitespace = true;

    for (int i = 0; i <= limit; i++) {
        if (whitespaceChars.contains(str[i])) {
            isWhitespace = true;
        }
        else if (isWhitespace) {
            isWhitespace = false;

            // avoid accessing beyond the end of the string by first checking if the iteration is at the last possible location of the string being search
            if (i == limit || whitespaceChars.contains(str[i + substrLen])) { // i >= limit
                int j = 0;

                while (j < substrLen && str[i + j] == phrase[j]) {
                    j++;
                }

                if (j == substrLen) { // j >= substrLen
                    return true;
                }
            }
        }
    }

    return false;
}

/**
 * check if a phrase appears in a string
 * 
 * uses regex
 * 
 * @param {*} str 
 * @param {*} phrase 
 * @param {*} caseSensitive 
 * @returns 
 */
bool tvnj::includesPhrase2(std::string str, std::string phrase, bool caseSensitive) {
    std::string escapedWord = "\\b" + tvnj::escapeRegex(phrase) + "\\b";

    if (caseSensitive) {
        return std::regex_search(str, std::regex(escapedWord));
    }

    return std::regex_search(str, std::regex(escapedWord, std::regex_constants::ECMAScript | std::regex_constants::icase));
}

//-------------------------------------------------

/**
 * replaces all instances of the substring
 * 
 * @param {*} str 
 * @param {*} substr 
 * @param {*} replacement 
 * @returns 
 */
std::string tvnj::replaceAll(std::string str, std::string substr, std::string replacement) {
    const int substrLen = substr.size();
    int strLen = str.size();

    if (substrLen == 0 || strLen == 0) {
        return str;
    }

    const char firstChar = substr[0];
    int i = 0;
    strLen -= substrLen;
    const int replacementLen = replacement.size(),
        lenIncrement = replacementLen - substrLen;

    while (i <= strLen) {
        if (str[i] == firstChar) {
            int j = 1,
                indexSkip = 0;

            while (j < substrLen) {
                const char compareChar = str[i + j];

                if (indexSkip == 0 && compareChar == firstChar) {
                    indexSkip = j;
                }

                if (compareChar == substr[j]) {
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

            if (j == substrLen) { // j >= substrLen
                str.replace(i, substrLen, replacement);
                i += replacementLen;
                strLen += lenIncrement;
            }
        }
        else {
            i++;
        }
    }

    return str;
}

/**
 * replaces all instances of the character
 * 
 * @param {*} str 
 * @param {*} c 
 * @param {*} replacement 
 * @returns  
 */
std::string tvnj::replaceAll(std::string str, char c, char replacement) {
    const int strLen = str.size();
    int i = 0;

    while (i < strLen) {
        if (str[i] == c) {
            str[i] = replacement;
        }

        i++;
    }

    return str;
}

/**
 * replaces all instances of the char set
 * 
 * @param {*} str 
 * @param {*} charSet 
 * @param {*} replacement 
 * @returns  
 */
std::string tvnj::replaceAll(std::string str, std::unordered_set<char> charSet, char replacement) {
    const int strLen = str.size();
    int i = 0;

    while (i < strLen) {
        if (charSet.contains(str[i])) {
            str[i] = replacement;
        }

        i++;
    }

    return str;
}

/**
 * replaces all instances of the substring using c++ functions
 * 
 * @param {*} str 
 * @param {*} substr 
 * @param {*} replacement 
 * @returns 
 */
std::string tvnj::replaceAll2(std::string str, std::string substr, std::string replacement) {
    const size_t substrLen = substr.size();

    if (substrLen == 0 || str.size() == 0) {
        return str;
    }

    const size_t replacementLen = replacement.size();
    size_t i = str.find(substr, 0);

    while (i != std::string::npos) {
        str.replace(i, substrLen, replacement);
        i = str.find(substr, i + replacementLen);
    }

    return str;
}

//-------------------------------------------------

/**
 * replaces the 1st instance of the substring (starting from the left side)
 * 
 * @param {*} str 
 * @param {*} substr 
 * @param {*} replacement 
 * @param {*} index inclusive
 * @returns 
 */
std::string tvnj::replaceFirst(std::string str, std::string substr, std::string replacement, int index) {
    const int substrLen = substr.size();
    int strLen = str.size();

    if (substrLen == 0 || strLen == 0) {
        return str;
    }

    if (index < 0) {
        index = 0;
    }

    const char firstChar = substr[0];
    int i = index;
    strLen -= substrLen;

    while (i <= strLen) {
        if (str[i] == firstChar) {
            int j = 1,
                indexSkip = 0;

            while (j < substrLen) {
                const char compareChar = str[i + j];

                if (indexSkip == 0 && compareChar == firstChar) {
                    indexSkip = j;
                }

                if (compareChar == substr[j]) {
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

            if (j == substrLen) { // j >= substrLen
                str.replace(i, substrLen, replacement);
                return str;
            }
        }
        else {
            i++;
        }
    }

    return str;
}

/**
 * replaces the 1st instance of the character (starting from the left side)
 * 
 * @param {*} str 
 * @param {*} c 
 * @param {*} replacement 
 * @param {*} index inclusive
 * @returns  
 */
std::string tvnj::replaceFirst(std::string str, char c, char replacement, int index) {
    if (index < 0) {
        index = 0;
    }

    const int strLen = str.size();
    int i = index;

    while (i < strLen) {
        if (str[i] == c) {
            str[i] = replacement;
            return str;
        }

        i++;
    }

    return str;
}

/**
 * replaces the 1st instance of the char set (starting from the left side)
 * 
 * @param {*} str 
 * @param {*} charSet 
 * @param {*} replacement 
 * @param {*} index inclusive
 * @returns  
 */
std::string tvnj::replaceFirst(std::string str, std::unordered_set<char> charSet, char replacement, int index) {
    if (index < 0) {
        index = 0;
    }

    const int strLen = str.size();
    int i = index;

    while (i < strLen) {
        if (charSet.contains(str[i])) {
            str[i] = replacement;
            return str;
        }

        i++;
    }

    return str;
}

/**
 * replaces the last instance of the substring (starting from the right side)
 * 
 * @param {*} str 
 * @param {*} substr 
 * @param {*} replacement 
 * @param {*} index inclusive
 * @returns 
 */
std::string tvnj::replaceLast(std::string str, std::string substr, std::string replacement, int index) {
    int substrLen = substr.size(),
        i = str.size();

    if (substrLen == 0 || i == 0) {
        return str;
    }

    substrLen--;
    i--;

    const char lastChar = substr[substrLen];

    if (index >= 0 && index <= i) {
        i = index;
    }

    while (i >= substrLen) {
        if (str[i] == lastChar) {
            int j = 1,
                indexSkip = 0;

            while (j <= substrLen) {
                const char compareChar = str[i - j];

                if (indexSkip == 0 && compareChar == lastChar) {
                    indexSkip = j;
                }

                if (compareChar == substr[substrLen - j]) {
                    j++;
                }
                else {
                    if (indexSkip == 0) {
                        i -= j + 1;
                    }
                    else {
                        i -= indexSkip;
                    }

                    break;
                }
            }

            if (j > substrLen) {
                str.replace(i - substrLen, j, replacement);
                return str;
            }
        }
        else {
            i--;
        }
    }

    return str;
}

/**
 * replaces the last instance of the character (starting from the right side)
 * 
 * @param {*} str 
 * @param {*} c 
 * @param {*} replacement 
 * @param {*} index inclusive
 * @returns 
 */
std::string tvnj::replaceLast(std::string str, char c, char replacement, int index) {
    int i = str.size() - 1;

    if (index >= 0 && index <= i) {
        i = index;
    }

    while (i >= 0) { // i != -1
        if (str[i] == c) {
            str[i] = replacement;
            return str;
        }

        i--;
    }

    return str;
}

/**
 * replaces the last instance of the char set (starting from the right side)
 * 
 * @param {*} str 
 * @param {*} charSet 
 * @param {*} replacement 
 * @param {*} index inclusive
 * @returns 
 */
std::string tvnj::replaceLast(std::string str, std::unordered_set<char> charSet, char replacement, int index) {
    int i = str.size() - 1;

    if (index >= 0 && index <= i) {
        i = index;
    }

    while (i >= 0) { // i != -1
        if (charSet.contains(str[i])) {
            str[i] = replacement;
            return str;
        }

        i--;
    }

    return str;
}

/**
 * replaces n instances of the substring starting from the left side
 * 
 * @param {*} str 
 * @param {*} substr 
 * @param {*} replacement 
 * @param {*} n 
 * @param {*} index inclusive
 * @returns 
 */
std::string tvnj::replaceNTimesLeft(std::string str, std::string substr, std::string replacement, int n, int index) {
    const int substrLen = substr.size();
    int strLen = str.size();

    if (substrLen == 0 || strLen == 0 || n <= 0) {
        return str;
    }

    if (index < 0) {
        index = 0;
    }

    const char firstChar = substr[0];
    int i = index,
        count = 0;
    strLen -= substrLen;
    const int replacementLen = replacement.size(),
        lenIncrement = replacementLen - substrLen;

    while (i <= strLen) {
        if (str[i] == firstChar) {
            int j = 1,
                indexSkip = 0;

            while (j < substrLen) {
                const char compareChar = str[i + j];

                if (indexSkip == 0 && compareChar == firstChar) {
                    indexSkip = j;
                }

                if (compareChar == substr[j]) {
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

            if (j == substrLen) { // j >= substrLen
                str.replace(i, substrLen, replacement);

                count++;
                if (count == n) { // count >= n
                    return str;
                }

                i += replacementLen;
                strLen += lenIncrement;
            }
        }
        else {
            i++;
        }
    }

    return str;
}

/**
 * replaces n instances of the character starting from the left side
 * 
 * @param {*} str 
 * @param {*} c 
 * @param {*} replacement 
 * @param {*} n 
 * @param {*} index inclusive
 * @returns  
 */
std::string tvnj::replaceNTimesLeft(std::string str, char c, char replacement, int n, int index) {
    const int strLen = str.size();

    if (strLen == 0 || n <= 0) {
        return str;
    }

    if (index < 0) {
        index = 0;
    }

    int i = index,
        count = 0;

    while (i < strLen) {
        if (str[i] == c) {
            str[i] = replacement;

            count++;
            if (count == n) { // count >= n
                return str;
            }
        }

        i++;
    }

    return str;
}

/**
 * replaces n instances of the char set starting from the left side
 * 
 * @param {*} str 
 * @param {*} charSet 
 * @param {*} replacement 
 * @param {*} n 
 * @param {*} index inclusive
 * @returns  
 */
std::string tvnj::replaceNTimesLeft(std::string str, std::unordered_set<char> charSet, char replacement, int n, int index) {
    const int strLen = str.size();

    if (strLen == 0 || n <= 0) {
        return str;
    }

    if (index < 0) {
        index = 0;
    }

    int i = index,
        count = 0;

    while (i < strLen) {
        if (charSet.contains(str[i])) {
            str[i] = replacement;

            count++;
            if (count == n) { // count >= n
                return str;
            }
        }

        i++;
    }

    return str;
}

/**
 * replaces n instances of the substring starting from the right side
 * 
 * @param {*} str 
 * @param {*} substr 
 * @param {*} replacement 
 * @param {*} n 
 * @param {*} index inclusive
 * @returns 
 */
std::string tvnj::replaceNTimesRight(std::string str, std::string substr, std::string replacement, int n, int index) {
    int substrLen = substr.size(),
        i = str.size();

    if (substrLen == 0 || i == 0 || n <= 0) {
        return str;
    }

    substrLen--;
    i--;

    const char lastChar = substr[substrLen];
    int count = 0;

    if (index >= 0 && index <= i) {
        i = index;
    }

    while (i >= substrLen) {
        if (str[i] == lastChar) {
            int j = 1,
                indexSkip = 0;

            while (j <= substrLen) {
                const char compareChar = str[i - j];

                if (indexSkip == 0 && compareChar == lastChar) {
                    indexSkip = j;
                }

                if (compareChar == substr[substrLen - j]) {
                    j++;
                }
                else {
                    if (indexSkip == 0) {
                        i -= j + 1;
                    }
                    else {
                        i -= indexSkip;
                    }

                    break;
                }
            }

            if (j > substrLen) {
                i -= substrLen;
                str.replace(i, j, replacement);

                count++;
                if (count == n) { // count >= n
                    return str;
                }

                i--;
            }
        }
        else {
            i--;
        }
    }

    return str;
}

/**
 * replaces n instances of the character starting from the right side
 * 
 * @param {*} str 
 * @param {*} c 
 * @param {*} replacement 
 * @param {*} n 
 * @param {*} index inclusive
 * @returns 
 */
std::string tvnj::replaceNTimesRight(std::string str, char c, char replacement, int n, int index) {
    int i = str.size();

    if (i == 0 || n <= 0) {
        return str;
    }

    int count = 0;
    i--;

    if (index >= 0 && index <= i) {
        i = index;
    }

    while (i >= 0) { // i != -1
        if (str[i] == c) {
            str[i] = replacement;

            count++;
            if (count == n) { // count >= n
                return str;
            }
        }

        i--;
    }

    return str;
}

/**
 * replaces n instances of the char set starting from the right side
 * 
 * @param {*} str 
 * @param {*} charSet 
 * @param {*} replacement 
 * @param {*} n 
 * @param {*} index inclusive
 * @returns 
 */
std::string tvnj::replaceNTimesRight(std::string str, std::unordered_set<char> charSet, char replacement, int n, int index) {
    int i = str.size();

    if (i == 0 || n <= 0) {
        return str;
    }

    int count = 0;
    i--;

    if (index >= 0 && index <= i) {
        i = index;
    }

    while (i >= 0) { // i != -1
        if (charSet.contains(str[i])) {
            str[i] = replacement;

            count++;
            if (count == n) { // count >= n
                return str;
            }
        }

        i--;
    }

    return str;
}

//-------------------------------------------------

/**
 * splits strings by a specified delimiter
 * 
 * @param {*} str 
 * @param {*} delimiter default is a space
 * @returns 
 */
std::vector<std::string> tvnj::split(std::string str, char delimiter) {
    std::vector<std::string> words;
    std::string word = "";
    const int len = str.size();
    int i = 0;

    while (i < len) {
        const char current = str[i];

        if (current == delimiter) {
            words.push_back(word);
            word = "";
        }
        else {
            word += current;
        }

        i++;
    }

    words.push_back(word);

    return words;
}

/**
 * splits strings by a specified delimiter starting from the left side
 * 
 * @param {*} str 
 * @param {*} delimiter 
 * @param {*} n 
 * @param {*} index starting index (inclusive)
 * @returns 
 */
std::vector<std::string> tvnj::splitNTimesLeft(std::string str, char delimiter, int n, int index) {
    std::vector<std::string> words;

    if (n <= 0) {
        words.push_back(str);
        return words;
    }

    if (index < 0) {
        index = 0;
    }

    std::string word = str.substr(0, index);
    const int len = str.size();
    int i = index,
        count = 0;

    while (i < len) {
        const char current = str[i];

        if (current == delimiter) {
            words.push_back(word);

            count++;
            if (count == n) { // count >= n
                words.push_back(str.substr(i + 1));
                return words;
            }

            word = "";
        }
        else {
            word += current;
        }

        i++;
    }

    words.push_back(word);

    return words;
}

/**
 * splits strings by a specified delimiter starting from the left side
 * 
 * @param {*} str 
 * @param {*} delimiter 
 * @param {*} index starting index (inclusive)
 * @returns 
 */
std::vector<std::string> tvnj::splitLeft(std::string str, char delimiter, int index) {
    std::vector<std::string> words;

    if (index < 0) {
        index = 0;
    }

    std::string word = str.substr(0, index);
    const int len = str.size();
    int i = index;

    while (i < len) {
        const char current = str[i];

        if (current == delimiter) {
            words.push_back(word);
            word = "";
        }
        else {
            word += current;
        }

        i++;
    }

    words.push_back(word);

    return words;
}

/**
 * splits strings by a specified delimiter starting from the right side
 * 
 * @param {*} str 
 * @param {*} delimiter 
 * @param {*} n 
 * @param {*} index starting index (inclusive)
 * @returns 
 */
std::vector<std::string> tvnj::splitNTimesRight(std::string str, char delimiter, int n, int index) {
    std::vector<std::string> words;

    if (n <= 0) {
        words.push_back(str);
        return words;
    }

    int i = str.size() - 1,
        count = 0;

    if (index >= 0 && index <= i) {
        i = index;
    }

    std::string word = str.substr(i + 1);

    while (i >= 0) {
        const char current = str[i];

        if (current == delimiter) {
            words.push_back(word);

            count++;
            if (count == n) { // count >= n
                words.push_back(str.substr(0, i));
                tvnj::reverse(words);
                return words;
            }

            word = "";
        }
        else {
            word = current + word;
        }

        i--;
    }

    words.push_back(word);
    tvnj::reverse(words);
    return words;
}

/**
 * splits strings by a specified delimiter starting from the right side
 * 
 * @param {*} str 
 * @param {*} delimiter 
 * @param {*} index starting index (inclusive)
 * @returns 
 */
std::vector<std::string> tvnj::splitRight(std::string str, char delimiter, int index) {
    std::vector<std::string> words;
    int i = str.size() - 1;

    if (index >= 0 && index <= i) {
        i = index;
    }

    std::string word = str.substr(i + 1);

    while (i >= 0) {
        const char current = str[i];

        if (current == delimiter) {
            words.push_back(word);
            word = "";
        }
        else {
            word = current + word;
        }

        i--;
    }

    words.push_back(word);
    tvnj::reverse(words);
    return words;
}

/**
 * splits strings by specified delimiters
 * 
 * @param {*} str 
 * @param {*} delimiters set of delimiters
 * @returns 
 */
std::vector<std::string> tvnj::split(std::string str, std::unordered_set<char> delimiters) {
    std::vector<std::string> words;
    std::string word = "";
    const int len = str.size();
    int i = 0;

    while (i < len) {
        const char current = str[i];

        if (delimiters.contains(current)) {
            words.push_back(word);
            word = "";
        }
        else {
            word += current;
        }

        i++;
    }

    words.push_back(word);

    return words;
}

/**
 * splits strings by a specified delimiters starting from the left side
 * 
 * @param {*} str 
 * @param {*} delimiters set of delimiters
 * @param {*} n 
 * @param {*} index starting index (inclusive)
 * @returns 
 */
std::vector<std::string> tvnj::splitNTimesLeft(std::string str, std::unordered_set<char> delimiters, int n, int index) {
    std::vector<std::string> words;

    if (n <= 0) {
        words.push_back(str);
        return words;
    }

    if (index < 0) {
        index = 0;
    }

    std::string word = str.substr(0, index);
    const int len = str.size();
    int i = index,
        count = 0;

    while (i < len) {
        const char current = str[i];

        if (delimiters.contains(current)) {
            words.push_back(word);

            count++;
            if (count == n) { // count >= n
                words.push_back(str.substr(i + 1));
                return words;
            }

            word = "";
        }
        else {
            word += current;
        }

        i++;
    }

    words.push_back(word);

    return words;
}

/**
 * splits strings by a specified delimiters starting from the left side
 * 
 * @param {*} str 
 * @param {*} delimiters set of delimiters
 * @param {*} index starting index (inclusive)
 * @returns 
 */
std::vector<std::string> tvnj::splitLeft(std::string str, std::unordered_set<char> delimiters, int index) {
    std::vector<std::string> words;

    if (index < 0) {
        index = 0;
    }

    std::string word = str.substr(0, index);
    const int len = str.size();
    int i = index;

    while (i < len) {
        const char current = str[i];

        if (delimiters.contains(current)) {
            words.push_back(word);
            word = "";
        }
        else {
            word += current;
        }

        i++;
    }

    words.push_back(word);

    return words;
}

/**
 * splits strings by a specified delimiters starting from the right side
 * 
 * @param {*} str 
 * @param {*} delimiters set of delimiters
 * @param {*} n 
 * @param {*} index starting index (inclusive)
 * @returns 
 */
std::vector<std::string> tvnj::splitNTimesRight(std::string str, std::unordered_set<char> delimiters, int n, int index) {
    std::vector<std::string> words;

    if (n <= 0) {
        words.push_back(str);
        return words;
    }

    int i = str.size() - 1,
        count = 0;

    if (index >= 0 && index <= i) {
        i = index;
    }

    std::string word = str.substr(i + 1);

    while (i >= 0) {
        const char current = str[i];

        if (delimiters.contains(current)) {
            words.push_back(word);

            count++;
            if (count == n) { // count >= n
                words.push_back(str.substr(0, i));
                tvnj::reverse(words);
                return words;
            }

            word = "";
        }
        else {
            word = current + word;
        }

        i--;
    }

    words.push_back(word);
    tvnj::reverse(words);
    return words;
}

/**
 * splits strings by a specified delimiters starting from the right side
 * 
 * @param {*} str 
 * @param {*} delimiters set of delimiters
 * @param {*} index starting index (inclusive)
 * @returns 
 */
std::vector<std::string> tvnj::splitRight(std::string str, std::unordered_set<char> delimiters, int index) {
    std::vector<std::string> words;
    int i = str.size() - 1;

    if (index >= 0 && index <= i) {
        i = index;
    }

    std::string word = str.substr(i + 1);

    while (i >= 0) {
        const char current = str[i];

        if (delimiters.contains(current)) {
            words.push_back(word);
            word = "";
        }
        else {
            word = current + word;
        }

        i--;
    }

    words.push_back(word);
    tvnj::reverse(words);
    return words;
}

/**
 * splits strings by a specified delimiter
 * 
 * @param {*} str 
 * @param {*} delimiter 
 * @returns 
 */
std::vector<std::string> tvnj::split(std::string str, std::string delimiter) {
    std::vector<std::string> words;
    const int delimiterLen = delimiter.size();

    if (delimiterLen == 0) {
        words.push_back(str);
        return words;
    }

    std::string word = "";
    const char firstChar = delimiter[0];
    int i = 0;
    const int limit = str.size() - delimiterLen;

    while (i <= limit) {
        const char current = str[i];

        if (current == firstChar) {
            int j = 1,
                indexSkip = 0;

            while (j < delimiterLen) {
                const char compareChar = str[i + j];

                if (indexSkip == 0 && compareChar == firstChar) {
                    indexSkip = j;
                }

                if (compareChar == delimiter[j]) {
                    j++;
                }
                else {
                    word += str.substr(i, j);

                    if (indexSkip == 0) {
                        i += j + 1;
                    }
                    else {
                        i += indexSkip;
                    }

                    break;
                }
            }

            if (j == delimiterLen) { // j >= delimiterLen
                words.push_back(word);
                word = "";
                i += delimiterLen;
            }
        }
        else {
            word += current;
            i++;
        }
    }

    words.push_back(word + str.substr(i));

    return words;
}

/**
 * splits strings by a specified delimiter starting from the left side
 * 
 * @param {*} str 
 * @param {*} delimiter 
 * @param {*} n 
 * @param {*} index starting index (inclusive)
 * @returns 
 */
std::vector<std::string> tvnj::splitNTimesLeft(std::string str, std::string delimiter, int n, int index) {
    std::vector<std::string> words;
    const int delimiterLen = delimiter.size();

    if (delimiterLen == 0 || n <= 0) {
        words.push_back(str);
        return words;
    }

    if (index < 0) {
        index = 0;
    }

    std::string word = str.substr(0, index);
    const char firstChar = delimiter[0];
    int i = index,
        count = 0;
    const int limit = str.size() - delimiterLen;

    while (i <= limit) {
        const char current = str[i];

        if (current == firstChar) {
            int j = 1,
                indexSkip = 0;

            while (j < delimiterLen) {
                const char compareChar = str[i + j];

                if (indexSkip == 0 && compareChar == firstChar) {
                    indexSkip = j;
                }

                if (compareChar != delimiter[j]) {
                    break;
                }

                j++;
            }

            if (j == delimiterLen) { // j >= delimiterLen
                words.push_back(word);
                i += delimiterLen;

                count++;
                if (count == n) { // count >= n
                    words.push_back(str.substr(i));
                    return words;
                }

                word = "";
            }
            else if (indexSkip == 0) {
                j++;
                word += str.substr(i, j);
                i += j;
            }
            else {
                word += str.substr(i, indexSkip);
                i += indexSkip;
            }
        }
        else {
            word += current;
            i++;
        }
    }

    words.push_back(word + str.substr(i));

    return words;
}

/**
 * splits strings by a specified delimiter starting from the left side
 * 
 * @param {*} str 
 * @param {*} delimiter 
 * @param {*} index starting index (inclusive)
 * @returns 
 */
std::vector<std::string> tvnj::splitLeft(std::string str, std::string delimiter, int index) {
    std::vector<std::string> words;
    const int delimiterLen = delimiter.size();

    if (delimiterLen == 0) {
        words.push_back(str);
        return words;
    }

    if (index < 0) {
        index = 0;
    }

    std::string word = str.substr(0, index);
    const char firstChar = delimiter[0];
    int i = index;
    const int limit = str.size() - delimiterLen;

    while (i <= limit) {
        const char current = str[i];

        if (current == firstChar) {
            int j = 1,
                indexSkip = 0;

            while (j < delimiterLen) {
                const char compareChar = str[i + j];

                if (indexSkip == 0 && compareChar == firstChar) {
                    indexSkip = j;
                }

                if (compareChar != delimiter[j]) {
                    break;
                }

                j++;
            }

            if (j == delimiterLen) { // j >= delimiterLen
                words.push_back(word);
                i += delimiterLen;
                word = "";
            }
            else if (indexSkip == 0) {
                j++;
                word += str.substr(i, j);
                i += j;
            }
            else {
                word += str.substr(i, indexSkip);
                i += indexSkip;
            }
        }
        else {
            word += current;
            i++;
        }
    }

    words.push_back(word + str.substr(i));

    return words;
}

/**
 * splits strings by a specified delimiter starting from the right side
 * 
 * @param {*} str 
 * @param {*} delimiter 
 * @param {*} n 
 * @param {*} index starting index (inclusive)
 * @returns 
 */
std::vector<std::string> tvnj::splitNTimesRight(std::string str, std::string delimiter, int n, int index) {
    std::vector<std::string> words;
    int delimiterLen = delimiter.size();

    if (delimiterLen == 0 || n <= 0) {
        words.push_back(str);
        return words;
    }

    delimiterLen--;

    const char lastChar = delimiter[delimiterLen];
    int i = str.size() - 1,
        count = 0;

    if (index >= 0 && index <= i) {
        i = index;
    }

    std::string word = str.substr(i + 1);

    while (i >= delimiterLen) {
        const char current = str[i];

        if (current == lastChar) {
            int j = 1,
                indexSkip = 0;

            while (j <= delimiterLen) {
                const char compareChar = str[i - j];

                if (indexSkip == 0 && compareChar == lastChar) {
                    indexSkip = j;
                }

                if (compareChar != delimiter[delimiterLen - j]) {
                    break;
                }

                j++;
            }

            if (j > delimiterLen) {
                words.push_back(word);

                count++;
                if (count == n) { // count >= n
                    words.push_back(str.substr(0, i - delimiterLen));
                    tvnj::reverse(words);
                    return words;
                }

                i -= delimiterLen + 1;
                word = "";
            }
            else if (indexSkip == 0) {
                j++;
                i -= j;
                word = str.substr(i + 1, j) + word;
            }
            else {
                i -= indexSkip;
                word = str.substr(i + 1, indexSkip) + word;
            }
        }
        else {
            word = current + word;
            i--;
        }
    }

    if (i > 0) { // 'i' can be negative so 'i > 0' is used instead of 'i != 0'
        words.push_back(str.substr(0, i) + word);
    }
    else {
        words.push_back(word);
    }

    tvnj::reverse(words);
    return words;
}

/**
 * splits strings by a specified delimiter starting from the right side
 * 
 * @param {*} str 
 * @param {*} delimiter 
 * @param {*} index starting index (inclusive)
 * @returns 
 */
std::vector<std::string> tvnj::splitRight(std::string str, std::string delimiter, int index) {
    std::vector<std::string> words;
    int delimiterLen = delimiter.size();

    if (delimiterLen == 0) {
        words.push_back(str);
        return words;
    }

    delimiterLen--;

    const char lastChar = delimiter[delimiterLen];
    int i = str.size() - 1;

    if (index >= 0 && index <= i) {
        i = index;
    }

    std::string word = str.substr(i + 1);

    while (i >= delimiterLen) {
        const char current = str[i];

        if (current == lastChar) {
            int j = 1,
                indexSkip = 0;

            while (j <= delimiterLen) {
                const char compareChar = str[i - j];

                if (indexSkip == 0 && compareChar == lastChar) {
                    indexSkip = j;
                }

                if (compareChar != delimiter[delimiterLen - j]) {
                    break;
                }

                j++;
            }

            if (j > delimiterLen) {
                words.push_back(word);
                i -= delimiterLen + 1;
                word = "";
            }
            else if (indexSkip == 0) {
                j++;
                i -= j;
                word = str.substr(i + 1, j) + word;
            }
            else {
                i -= indexSkip;
                word = str.substr(i + 1, indexSkip) + word;
            }
        }
        else {
            word = current + word;
            i--;
        }
    }

    if (i > 0) { // 'i' can be negative so 'i > 0' is used instead of 'i != 0'
        words.push_back(str.substr(0, i) + word);
    }
    else {
        words.push_back(word);
    }

    tvnj::reverse(words);
    return words;
}

/**
 * splits strings by whitespace
 * 
 * @param {*} str 
 * @returns 
 */
std::vector<std::string> tvnj::splitWhitespace(std::string str) {
    std::vector<std::string> words;
    std::string word = "";
    bool isWhitespace = false;
    const int n = str.size();
    int i = 0;

    while (i < n) {
        char c = str[i];

        if (whitespaceChars.contains(c)) {
            if (!isWhitespace) {
                words.push_back(word);
                word = "";
            }

            isWhitespace = true;
        }
        else {
            isWhitespace = false;
            word += c;
        }

        i++;
    }

    words.push_back(word);

    return words;
}

//-------------------------------------------------

/**
 * trims a list of characters from a string
 * 
 * @param {*} str 
 * @param {*} charArr chars that will be trimed off of the str
 * @returns 
 */
std::string tvnj::trim(std::string str, std::vector<char> charArr) {
    const int charsLen = charArr.size();
    int end = str.size();

    while (end != 0) { // end > 0
        end--;
        const char current = str[end];
        int i = 0;

        while (i < charsLen && current != charArr[i]) {
            i++;
        }

        if (i == charsLen) { // i >= charsLen
            end++;
            break;
        }
    }

    if (end == 0) { // end <= 0
        return "";
    }

    int start = 0;

    while (true) {
        const char current = str[start];
        int i = 0;

        while (i < charsLen && current != charArr[i]) {
            i++;
        }

        if (i == charsLen) { // i >= charsLen
            break;
        }

        start++;
    }

    return str.substr(start, end - start);
}

/**
 * trims a set of characters from a string
 * 
 * @param {*} str str to be trimmmed
 * @param {*} charSet chars that will be trimed off of the str
 * @returns 
 */
std::string tvnj::trim(std::string str, std::unordered_set<char> charSet) {
    int end = str.size();

    while (end != 0) { // end > 0
        end--;

        if (!charSet.contains(str[end])) {
            end++;
            break;
        }
    }

    if (end == 0) { // end <= 0
        return "";
    }

    int start = 0;

    while (charSet.contains(str[start])) {
        start++;
    }

    return str.substr(start, end - start);
}

/**
 * trims a set of characters from the left side of a string
 * 
 * @param {*} str str to be trimmmed
 * @param {*} charSet chars that will be trimed off of the str
 * @returns 
 */
std::string tvnj::trimLeft(std::string str, std::unordered_set<char> charSet) {
    int start = 0;
    const int len = str.size();

    while (start < len) {
        if (!charSet.contains(str[start])) {
            return str.substr(start);
        }

        start++;
    }

    return "";
}

/**
 * trims a set of characters from the right side of a string
 * 
 * @param {*} str str to be trimmmed
 * @param {*} charSet chars that will be trimed off of the str
 * @returns 
 */
std::string tvnj::trimRight(std::string str, std::unordered_set<char> charSet) {
    int end = str.size();

    while (end != 0) { // end > 0
        end--;

        if (!charSet.contains(str[end])) {
            return str.substr(0, end + 1);
        }
    }

    return "";
}

//-------------------------------------------------

/**
 * trims a list of substrings from a string
 * 
 * @param {*} str 
 * @param {*} substrArr substrings that will be trimed off of the str, must be sorted from longest to shortest
 * @returns 
 */
std::string tvnj::trim(std::string str, std::vector<std::string> substrArr) {
    const int substrsLen = substrArr.size();

    if (substrsLen == 0 || substrArr[substrsLen - 1].size() == 0) {
        return str;
    }

    int end = str.size(),
        i = 0;

    while (i < substrsLen) {
        const std::string substr = substrArr[i];
        int substrIndex = substr.size();

        if (substrIndex <= end) {
            int strIndex = end;

            while (substrIndex != 0) { // substrIndex > 0
                strIndex--;
                substrIndex--;

                if (str[strIndex] != substr[substrIndex]) {
                    substrIndex++;
                    break;
                }
            }

            if (substrIndex == 0) { // substrIndex <= 0
                end = strIndex;
                i = 0;
            }
            else {
                i++;
            }
        }
        else {
            i++;
        }
    }

    if (end == 0) { // end <= 0
        return "";
    }

    int start = 0,
        len = end;

    i = 0;

    while (i < substrsLen) {
        const std::string substr = substrArr[i];
        const int substrLen = substr.size();

        i++;

        if (substrLen < len) {
            int strIndex = start,
                substrIndex = 0;

            while (str[strIndex] == substr[substrIndex]) {
                strIndex++;
                substrIndex++;

                if (substrIndex == substrLen) { // substrIndex >= substrLen
                    start = strIndex;
                    len = end - start;
                    i = 0;
                    break;
                }
            }
        }
    }

    return str.substr(start, len);
}

/**
 * trims a list of substrings from the left side of a string
 * 
 * @param {*} str 
 * @param {*} substrArr substrings that will be trimed off of the str, must be sorted from longest to shortest
 * @returns 
 */
std::string tvnj::trimLeft(std::string str, std::vector<std::string> substrArr) {
    const int substrsLen = substrArr.size();

    if (substrsLen == 0 || substrArr[substrsLen - 1].size() == 0) {
        return str;
    }

    const int end = str.size();
    int start = 0,
        len = end,
        i = 0;

    while (i < substrsLen) {
        const std::string substr = substrArr[i];
        const int substrLen = substr.size();

        i++;

        if (substrLen <= len) {
            int strIndex = start,
                substrIndex = 0;

            while (str[strIndex] == substr[substrIndex]) {
                strIndex++;
                substrIndex++;

                if (substrIndex == substrLen) { // substrIndex >= substrLen
                    start = strIndex;
                    len = end - start;
                    i = 0;
                    break;
                }
            }
        }
    }

    return str.substr(start);
}

/**
 * trims a list of substrings from the right side of a string
 * 
 * @param {*} str 
 * @param {*} substrArr substrings that will be trimed off of the str, must be sorted from longest to shortest
 * @returns 
 */
std::string tvnj::trimRight(std::string str, std::vector<std::string> substrArr) {
    const int substrsLen = substrArr.size();

    if (substrsLen == 0 || substrArr[substrsLen - 1].size() == 0) {
        return str;
    }

    int end = str.size(),
        i = 0;

    while (i < substrsLen) {
        const std::string substr = substrArr[i];
        int substrIndex = substr.size();

        if (substrIndex <= end) {
            int strIndex = end;

            while (substrIndex != 0) { // substrIndex > 0
                strIndex--;
                substrIndex--;

                if (str[strIndex] != substr[substrIndex]) {
                    substrIndex++;
                    break;
                }
            }

            if (substrIndex == 0) { // substrIndex <= 0
                end = strIndex;
                i = 0;
            }
            else {
                i++;
            }
        }
        else {
            i++;
        }
    }

    return str.substr(0, end);
}

//-------------------------------------------------

/**
 * trim whitespace
 * 
 * @param {*} str 
 * @returns 
 */
std::string tvnj::trim(std::string str) {
    return tvnj::trim(str, whitespaceChars);
}

/**
 * trim whitespace on the left side
 * 
 * @param {*} str 
 * @returns 
 */
std::string tvnj::trimLeft(std::string str) {
    return tvnj::trimLeft(str, whitespaceChars);
}

/**
 * trim whitespace on the right side
 * 
 * @param {*} str 
 * @returns 
 */
std::string tvnj::trimRight(std::string str) {
    return tvnj::trimRight(str, whitespaceChars);
}

//-------------------------------------------------

/**
 * finds the first instance of the substring
 * 
 * this implementation jumps to the second occurance of the substring's first char when a comparison failed in the substring comparison loop
 * 
 * @param {*} str 
 * @param {*} substr 
 * @param {*} index starting index (inclusive)
 * @returns index of the substring, returns -1 if not found
 */
int tvnj::indexOfNaiveSkip(std::string str, std::string substr, int index) {
    if (index < 0) {
        index = 0;
    }

    const int substrLen = substr.size();
    int strLen = str.size();

    if (substrLen == 0) {
        if (index < strLen) {
            return index;
        }

        return 0;
    }

    const char firstChar = substr[0];
    int i = index;
    strLen -= substrLen;

    while (i <= strLen) {
        if (str[i] == firstChar) {
            int j = 1,
                indexSkip = 0;

            while (j < substrLen) {
                const char compareChar = str[i + j];

                if (indexSkip == 0 && compareChar == firstChar) {
                    indexSkip = j;
                }

                if (compareChar == substr[j]) {
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

            if (j == substrLen) { // j >= substrLen
                return i;
            }
        }
        else {
            i++;
        }
    }

    return -1;
}

/**
 * finds the last instance of the substring
 * 
 * this implementation jumps to the second occurance of the substring's first char when a comparison failed in the substring comparison loop
 * 
 * @param {*} str 
 * @param {*} substr 
 * @param {*} index starting index from the right (inclusive)
 * @returns index of the substring, returns -1 if not found
 */
int tvnj::indexOfNaiveSkipLast(std::string str, std::string substr, int index) {
    int substrLen = substr.size(),
        i = str.size();

    if (substrLen == 0) {
        if (i == 0) {
            return 0;
        }

        if (index >= 0 && index < i) {
            return index;
        }

        return i - 1;
    }

    substrLen--;
    i--;

    const char lastChar = substr[substrLen];

    if (index >= 0 && index <= i) {
        i = index;
    }

    while (i >= substrLen) {
        if (str[i] == lastChar) {
            int j = 1,
                indexSkip = 0;

            while (j <= substrLen) {
                const char compareChar = str[i - j];

                if (indexSkip == 0 && compareChar == lastChar) {
                    indexSkip = j;
                }

                if (compareChar == substr[substrLen - j]) {
                    j++;
                }
                else {
                    if (indexSkip == 0) {
                        i -= j + 1;
                    }
                    else {
                        i -= indexSkip;
                    }

                    break;
                }
            }

            if (j > substrLen) { // 'j == substrLen + 1' bc of the above 'substrLen--;'
                return i - substrLen;
            }
        }
        else {
            i--;
        }
    }

    return -1;
}

/**
 * finds the first instance of the substring
 * 
 * uses a combination of different algorithms
 * 
 * @param {*} str 
 * @param {*} substr 
 * @param {*} index starting index (inclusive)
 * @returns index of the substring, returns -1 if not found
 */
int tvnj::indexOf(std::string str, std::string substr, int index) {
    const int strLen = str.size(),
        substrLen = substr.size();

    if (substrLen == 0) {
        if (index > 0 && index < strLen) { // 'index >= 0' was not used bc 'return 0;' is the same as if index = 0
            return index;
        }

        return 0;
    }

    if (substrLen == 1) {
        return tvnj::indexOfChar(str, substr[0], index);
    }

    if (strLen <= 8192) {
        return tvnj::indexOfNaiveSkip(str, substr, index);
    }

    return tvnj::indexOfTwoWay(str, substr, index);
}

/**
 * finds the last instance of the substring
 * 
 * uses a combination of different algorithms
 * 
 * @param {*} str 
 * @param {*} substr 
 * @param {*} index starting index (inclusive)
 * @returns index of the substring, returns -1 if not found
 */
int tvnj::indexOfLast(std::string str, std::string substr, int index) {
    const int substrLen = substr.size();

    if (substrLen == 0) {
        const int strLen = str.size();

        if (strLen == 0) {
            return 0;
        }

        if (index >= 0 && index < strLen) {
            return index;
        }

        return strLen - 1;
    }

    if (substrLen == 1) {
        return tvnj::indexOfCharLast(str, substr[0], index);
    }

    return tvnj::indexOfNaiveSkipLast(str, substr, index);
}

//-------------------------------------------------

void maxSuffix(std::string substr, int len, int *maxSuffix, int *p) {
    int j = 0,
        k = 1;

    *maxSuffix = -1;
    *p = 1;

    while (j + k < len) {
        char a = substr[j + k],
            b = substr[*maxSuffix + k];

        if (a < b) {
            j += k;
            k = 1;
            *p = j - *maxSuffix;
        }
        else if (a == b) {
            if (k == *p) {
                j += *p;
                k = 1;
            }
            else {
                k++;
            }
        }
        else { // a > b
            *maxSuffix = j;
            j++;
            k = 1;
            *p = 1;
        }
    }
}

void maxSuffixReverse(std::string substr, int len, int *maxSuffix, int *p) {
    int j = 0,
        k = 1;

    *maxSuffix = -1;
    *p = 1;

    while (j + k < len) {
        char a = substr[j + k],
            b = substr[*maxSuffix + k];

        if (a > b) {
            j += k;
            k = 1;
            *p = j - *maxSuffix;
        }
        else if (a == b) {
            if (k == *p) {
                j += *p;
                k = 1;
            }
            else {
                k++;
            }
        }
        else { // a < b
            *maxSuffix = j;
            j++;
            k = 1;
            *p = 1;
        }
    }
}

/**
 * finds the first instance of the substring
 * 
 * uses the two way algorithm
 * 
 * only works on an ordered alphabet
 * 
 * time complexity:
 *      prepocessing phase: O(m)
 *      searching phase: O(n)
 * 
 * space complexity: O(1)
 * 
 * comparisons: 2n-m
 * 
 * @param {*} str 
 * @param {*} substr 
 * @param {*} index starting index (inclusive)
 * @returns index of the substring, returns -1 if not found
 */
int tvnj::indexOfTwoWay(std::string str, std::string substr, int index) {
    if (index < 0) {
        index = 0;
    }

    const int substrLen = substr.size(),
        limit = str.size() - substrLen;

    int p,
        q,
        i,
        j,
        suffix,
        period;

    maxSuffix(substr, substrLen, &i, &p);
    maxSuffixReverse(substr, substrLen, &j, &q);

    //-------------------
    // critical factorization

    if (i > j) {
        suffix = i;
        period = p;
    }
    else {
        suffix = j;
        period = q;
    }

    //-------------------
    // set starting position

    j = index;

    //-------------------
    // compare the right half first

    bool match = true;

    for (int idx = 0; idx <= suffix; idx++) {
        if (substr[idx] != substr[idx + period]) {
            match = false;
            break;
        }
    }

    //-------------------
    // search

    if (match) {
        int memory = -1;

        while (j <= limit) {
            if (suffix > memory) {
                i = suffix;
            }
            else {
                i = memory;
            }

            i++;

            //-------------------
            // scan for matches in the right half

            while (i < substrLen && substr[i] == str[i + j]) {
                i++;
            }

            if (i >= substrLen) {
                // scan for matches in the left half

                i = suffix;

                while (i > memory && substr[i] == str[i + j]) {
                    i--;
                }

                // since the decrement is by 1, 'i == memory' can be used instead of 'i <= memory'
                if (i <= memory) {
                    return j;
                }

                j += period;
                memory = substrLen - period - 1;
            }
            else {
                j += i - suffix;
                memory = -1;
            }
        }
    }
    else {
        int firstValue = suffix + 1;
        period = substrLen - suffix - 1;

        if (firstValue > period) {
            period = firstValue;
        }

        period++;

        //-------------------

        while (j <= limit) {
            i = firstValue;

            while (i < substrLen && substr[i] == str[i + j]) {
                i++;
            }

            if (i >= substrLen) {
                i = suffix;

                while (i >= 0 && substr[i] == str[i + j]) {
                    i--;
                }

                // since the decrement is by 1, 'i == -1' can be used instead of 'i < 0'
                if (i < 0) {
                    return j;
                }

                j += period;
            }
            else {
                j += i - suffix;
            }
        }
    }

    return -1;
}

//-------------------------------------------------

/**
 * finds the first instance of the substring
 * 
 * uses brute force
 * 
 * @param {*} str 
 * @param {*} substr 
 * @param {*} index starting index (inclusive)
 * @returns index of the substring, returns -1 if not found
 */
int tvnj::indexOfNaive(std::string str, std::string substr, int index) {
    if (index < 0) {
        index = 0;
    }

    const int substrLen = substr.size();
    int strLen = str.size();

    if (substrLen == 0) {
        if (index < strLen) {
            return index;
        }

        return 0;
    }

    strLen -= substrLen;
    const char firstChar = substr[0];
    int i = index;

    while (i <= strLen) {
        if (str[i] == firstChar) {
            int j = 1;

            while (j < substrLen && str[i + j] == substr[j]) {
                j++;
            }

            if (j == substrLen) { // j >= substrLen
                return i;
            }
        }

        i++;
    }

    return -1;
}

/**
 * finds the first instance of the substring
 * 
 * uses brute force
 * 
 * @param {*} str 
 * @param {*} substr 
 * @param {*} index starting index from the right (inclusive)
 * @returns index of the substring, returns -1 if not found
 */
int tvnj::indexOfNaiveLast(std::string str, std::string substr, int index) {
    int substrLen = substr.size(),
        i = str.size();

    if (substrLen == 0) {
        if (i == 0) {
            return 0;
        }

        if (index >= 0 && index < i) {
            return index;
        }

        return i - 1;
    }

    substrLen--;
    i--;

    const char lastChar = substr[substrLen];

    if (index >= 0 && index <= i) {
        i = index;
    }

    while (i >= substrLen) {
        if (str[i] == lastChar) {
            int j = 1;

            while (j <= substrLen && str[i - j] == substr[substrLen - j]) {
                j++;
            }

            if (j > substrLen) {
                return i - substrLen;
            }
        }

        i--;
    }

    return -1;
}

/**
 * finds the first instance of the char
 * 
 * linear search
 * 
 * @param {*} str 
 * @param {*} c 
 * @param {*} index starting index (inclusive)
 * @returns index of the char, returns -1 if not found
 */
int tvnj::indexOfChar(std::string str, char c, int index) {
    if (index < 0) {
        index = 0;
    }

    const int strLen = str.size();
    int i = index;

    while (i < strLen) { // i != strLen
        if (str[i] == c) {
            return i;
        }

        i++;
    }

    return -1;
}

/**
 * finds the last instance of the char
 * 
 * linear search
 * 
 * @param {*} str 
 * @param {*} c 
 * @param {*} index starting index from the right (inclusive)
 * @returns index of the char, returns -1 if not found
 */
int tvnj::indexOfCharLast(std::string str, char c, int index) {
    int i = str.size() - 1;

    if (index >= 0 && index <= i) {
        i = index;
    }

    while (i >= 0) { // i != -1
        if (str[i] == c) {
            return i;
        }

        i--;
    }

    return -1;

    // exclusive

    // int i = str.size();

    // if (index > 0 && index < i) {
    //     i = index;
    // }

    // while (i > 0) { // i != 0
    //     i--;

    //     if (str[i] == c) {
    //         return i;
    //     }
    // }

    // return -1;
}

/**
 * parses a command line string into an vector w/o any space char elements
 * 
 * strings are surrounded by quotes
 * 
 * @param {*} cmdLn 
 * @param {*} throwError 
 * @returns string vector
 */
std::vector<std::string> tvnj::cmdLnToArgArr(std::string cmdLn, bool throwError) {
    int i = 0,
        startOfArg = 0;
    const int len = cmdLn.size();
    bool inStr = false;
    std::vector<std::string> array;
    std::string str = "";
    char previousChar = ' ';

    while (i < len) {
        const char currentChar = cmdLn[i];

        // check if iteration is in a string
        if (inStr) {
            // check for and escape a char
            if (currentChar == '\\') {
                str += cmdLn.substr(startOfArg, i - startOfArg);
                i++;
                startOfArg = i;
            }
            // check for end of the string
            else if (currentChar == '"') {
                array.push_back(str + cmdLn.substr(startOfArg, i - startOfArg));

                inStr = false;
                str = "";
                startOfArg = i + 1;
            }
        }
        else {
            // skip whitespace between args

            // start of arg
            if (previousChar == ' ') {
                if (currentChar != ' ') {
                    startOfArg = i;
                }
            }
            // end of arg
            else if (previousChar != '"') {
                if (currentChar == ' ' || currentChar == '"') {
                    array.push_back(cmdLn.substr(startOfArg, i - startOfArg));

                    startOfArg = len;
                }
            }

            // check for start of a string
            if (currentChar == '"') {
                inStr = true;
                startOfArg = i + 1;
            }
        }

        previousChar = currentChar;
        i++;
    }

    if (inStr) {
        if (throwError) {
            throw std::invalid_argument("invalid command line");
        }
    }
    else {
        if (len - startOfArg != 0) { // 'startOfArg' will never be greater than 'len'
            array.push_back(cmdLn.substr(startOfArg));
        }
    }

    return array;
}

/**
 * capitalizes characters after spaces and lower case otherwise
 * 
 * @param {*} str 
 * @returns 
 */
std::string tvnj::toProperCase(std::string str) {
    std::string proper = "";
    bool isWhitespace = true;
    const int n = str.size();
    int i = 0;

    while (i < n) {
        char c = str[i];

        if (whitespaceChars.contains(c)) {
            isWhitespace = true;
        }
        else if (isWhitespace) {
            isWhitespace = false;
            c = std::toupper(c);
        }
        else {
            c = std::tolower(c);
        }

        proper += c;
        i++;
    }

    return proper;
}

/**
 * uses tolower()
 * 
 * @param {*} str 
 * @returns 
 */
std::string tvnj::toLowerCase(std::string str) {
    std::string lowerCase = "";
    int i = 0;
    const int n = str.size();

    while (i < n) {
        lowerCase += std::tolower(str[i]);
        i++;
    }

    return lowerCase;
}

/**
 * uses toupper()
 * 
 * @param {*} str 
 * @returns 
 */
std::string tvnj::toUpperCase(std::string str) {
    std::string upperCase = "";
    int i = 0;
    const int n = str.size();

    while (i < n) {
        upperCase += std::toupper(str[i]);
        i++;
    }

    return upperCase;
}

/**
 * 
 * @param {*} str 
 * @param {*} substr 
 * @returns 
 */
bool tvnj::startsWith(std::string str, std::string substr) {
    const size_t substrLen = substr.size();

    if (str.size() < substrLen) {
        return false;
    }

    size_t i = 0;

    while (i < substrLen) {
        if (str[i] != substr[i]) {
            return false;
        }

        i++;
    }

    return true;
}

/**
 * 
 * @param {*} str 
 * @param {*} c 
 * @returns 
 */
bool tvnj::startsWith(std::string str, char c) {
    if (str.size() == 0 || str[0] != c) {
        return false;
    }

    return true;
}

/**
 * 
 * @param {*} str 
 * @param {*} substr 
 * @returns 
 */
bool tvnj::endsWith(std::string str, std::string substr) {
    int strLen = str.size(),
        substrLen = substr.size();

    if (strLen < substrLen) {
        return false;
    }

    while (substrLen != 0) { // substrLen > 0
        strLen--;
        substrLen--;

        if (str[strLen] != substr[substrLen]) {
            return false;
        }
    }

    return true;
}

/**
 * 
 * @param {*} str 
 * @param {*} c 
 * @returns 
 */
bool tvnj::endsWith(std::string str, char c) {
    const int strLen = str.size();

    if (strLen == 0 || str[strLen - 1] != c) {
        return false;
    }

    return true;
}

/**
 * 
 * @param {*} str 
 * @param {*} substr 
 * @param {*} index inclusive, set to 0 to behave like startsWith(str, substr)
 * @returns 
 */
bool tvnj::startsWith(std::string str, std::string substr, int index) {
    const int strLen = str.size(),
        substrLen = substr.size();

    if (strLen < substrLen || index < 0 || index > strLen - substrLen) {
        return false;
    }

    int i = 0;

    while (i < substrLen) {
        if (str[i + index] != substr[i]) {
            return false;
        }

        i++;
    }

    return true;
}

/**
 * 
 * @param {*} str 
 * @param {*} c 
 * @param {*} index inclusive, set to 0 to behave like startsWith(str, c)
 * @returns 
 */
bool tvnj::startsWith(std::string str, char c, int index) {
    const int strLen = str.size();

    if (strLen == 0 || index < 0 || index >= strLen || str[index] != c) {
        return false;
    }

    return true;
}

/**
 * 
 * @param {*} str 
 * @param {*} substr 
 * @param {*} length length of the search area in the string (exclusive index), set to -1 to behave like endsWith(str, substr)
 * @returns 
 */
bool tvnj::endsWith(std::string str, std::string substr, int length) {
    int strLen = str.size(),
        substrLen = substr.size();

    if (length >= 0 && length <= strLen && length >= substrLen) {
        strLen = length;
    }

    if (strLen < substrLen) {
        return false;
    }

    while (substrLen != 0) { // substrLen > 0
        strLen--;
        substrLen--;

        if (str[strLen] != substr[substrLen]) {
            return false;
        }
    }

    return true;
}

/**
 * 
 * @param {*} str 
 * @param {*} c 
 * @param {*} length length of the search area in the string (exclusive index), set to -1 to behave like endsWith(str, c)
 * @returns 
 */
bool tvnj::endsWith(std::string str, char c, int length) {
    const int strLen = str.size();

    if (length < 0) {
        length = strLen;
    }

    if (strLen == 0 || strLen < length || str[length - 1] != c) {
        return false;
    }

    return true;
}

/**
 * 
 * @param {*} str1
 * @param {*} str2
 * @returns
 * 		combined str of 2 strings that are alternated w/ each other
 */
std::string tvnj::alternateStrings(std::string str1, std::string str2) {
    const int str1Len = str1.size(),
        str2Len = str2.size();
    std::string alternate = "";
    int x = 0,
        length;

    if (str1Len > str2Len) {
        length = str2Len;
    }
    else {
        length = str1Len;
    }

    //----------------------------

    while (x < length) {
        alternate += str1[x];
        alternate += str2[x];
        x++;
    }

    if (x < str1Len) {
        alternate += str1.substr(x);
    }
    else {
        alternate += str2.substr(x);
    }

    // while (x < str1Len) {
    //     alternate += str1[x];
    //     x++;
    // }

    // while (x < str2Len) {
    //     alternate += str2[x];
    //     x++;
    // }

    return alternate;
}

/**
 * exponentiation by squaring method
 * 
 * @param {*} str
 * @param {*} n
 * @returns
 */
std::string tvnj::repeat(std::string str, int n) {
    std::string repeated = "";
    std::string exponentiation = str;

    while (n > 0) {
        if (n % 2 != 0) {
            repeated += exponentiation;
        }

        exponentiation += exponentiation;
        n >>= 1;
    }

    return repeated;
}

/**
 * exponentiation by squaring method
 * 
 * @param {*} str 
 * @param {*} len 
 * @param {*} c 
 * @returns
 */
std::string tvnj::padLeft(std::string str, int len, char c) {
    int n = len - str.size();
    std::string pad = "";
    std::string padExponentiation;
    padExponentiation = c;

    while (n > 0) {
        if (n % 2 != 0) {
            pad += padExponentiation;
        }

        padExponentiation += padExponentiation;
        n >>= 1;
    }

    return pad + str;
}

/**
 * exponentiation by squaring method
 * 
 * @param {*} str 
 * @param {*} len 
 * @param {*} c 
 * @returns
 */
std::string tvnj::padRight(std::string str, int len, char c) {
    int n = len - str.size();
    std::string pad = "";
    std::string padExponentiation;
    padExponentiation = c;

    while (n > 0) {
        if (n % 2 != 0) {
            pad += padExponentiation;
        }

        padExponentiation += padExponentiation;
        n >>= 1;
    }

    return str + pad;
}

/**
 * finds all of the instances of the substring on the right side of the index
 * 
 * this implementation jumps to the second occurance of the substring's first char when a comparison failed in the substring comparison loop
 * 
 * @param {*} str 
 * @param {*} substr 
 * @param {*} index starting index (inclusive)
 * @param {*} includeOverlap 
 * @returns vector of indices of the substring, returns an empty vector if not found
 */
std::vector<int> tvnj::indexOfAllRight(std::string str, std::string substr, int index, bool includeOverlap) {
    std::vector<int> finds;
    const int substrLen = substr.size();

    if (substrLen == 0) {
        finds.push_back(0);

        return finds;
    }

    if (index < 0) {
        index = 0;
    }

    const int strLen = str.size() - substrLen;
    const char firstChar = substr[0];
    int i = index;

    while (i <= strLen) {
        if (str[i] == firstChar) {
            int j = 1,
                indexSkip = 0;

            while (j < substrLen) {
                const char compareChar = str[i + j];

                if (indexSkip == 0 && compareChar == firstChar) {
                    indexSkip = j;
                }

                if (compareChar == substr[j]) {
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

            if (j == substrLen) { // j >= substrLen
                finds.push_back(i);

                if (includeOverlap) {
                    i++;
                }
                else {
                    i += substrLen;
                }
            }
        }
        else {
            i++;
        }
    }

    return finds;
}

/**
 * finds all of the instances of the substring on the left side of the index
 * 
 * this implementation jumps to the second occurance of the substring's first char when a comparison failed in the substring comparison loop
 * 
 * @param {*} str 
 * @param {*} substr 
 * @param {*} index starting index (exclusive)
 * @param {*} includeOverlap 
 * @returns vector of indices of the substring, returns an empty vector if not found
 */
std::vector<int> tvnj::indexOfAllLeft(std::string str, std::string substr, int index, bool includeOverlap) {
    std::vector<int> finds;
    const int substrLen = substr.size();

    if (substrLen == 0) {
        finds.push_back(0);

        return finds;
    }

    const int strLen = str.size();

    if (index < 0 || index > strLen) {
        index = strLen;
    }

    const char firstChar = substr[0];
    int i = 0;
    index -= substrLen;

    while (i <= index) {
        if (str[i] == firstChar) {
            int j = 1,
                indexSkip = 0;

            while (j < substrLen) {
                const char compareChar = str[i + j];

                if (indexSkip == 0 && compareChar == firstChar) {
                    indexSkip = j;
                }

                if (compareChar == substr[j]) {
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

            if (j == substrLen) { // j >= substrLen
                finds.push_back(i);

                if (includeOverlap) {
                    i++;
                }
                else {
                    i += substrLen;
                }
            }
        }
        else {
            i++;
        }
    }

    return finds;
}

/**
 * finds all of the instances of the char on the right side of the index
 * 
 * linear search O(n) where n = the length of the string
 * 
 * @param {*} str 
 * @param {*} c 
 * @param {*} index starting index inclusive
 * @returns vector of indices of the substring, returns an empty vector if not found
 */
std::vector<int> tvnj::indexOfAllRight(std::string str, char c, int index) {
    std::vector<int> finds;

    if (index < 0) {
        index = 0;
    }

    const int strLen = str.size();
    int i = index;

    while (i < strLen) {
        if (str[i] == c) {
            finds.push_back(i);
        }

        i++;
    }

    return finds;
}

/**
 * finds all of the instances of the char on the left side of the index
 * 
 * linear search O(n) where n = the length of the string
 * 
 * @param {*} str 
 * @param {*} c 
 * @param {*} index ending index exclusive
 * @returns vector of indices of the substring, returns an empty vector if not found
 */
std::vector<int> tvnj::indexOfAllLeft(std::string str, char c, int index) {
    std::vector<int> finds;
    const int strLen = str.size();
    int i = 0;

    if (index < 0 || index > strLen) {
        index = strLen;
    }

    while (i < index) {
        if (str[i] == c) {
            finds.push_back(i);
        }

        i++;
    }

    return finds;
}

/**
 * finds all of the instances of the set of chars on the right side of the index
 * 
 * linear search O(n) where n = the length of the string
 * 
 * @param {*} str 
 * @param {*} charSet 
 * @param {*} index starting index inclusive
 * @returns vector of indices of the substring, returns an empty vector if not found
 */
std::vector<int> tvnj::indexOfAllRight(std::string str, std::unordered_set<char> charSet, int index) {
    std::vector<int> finds;

    if (index < 0) {
        index = 0;
    }

    const int strLen = str.size();
    int i = index;

    while (i < strLen) {
        if (charSet.contains(str[i])) {
            finds.push_back(i);
        }

        i++;
    }

    return finds;
}

/**
 * finds all of the instances of the set of chars on the left side of the index
 * 
 * linear search O(n) where n = the length of the string
 * 
 * @param {*} str 
 * @param {*} charSet 
 * @param {*} index ending index exclusive
 * @returns vector of indices of the substring, returns an empty vector if not found
 */
std::vector<int> tvnj::indexOfAllLeft(std::string str, std::unordered_set<char> charSet, int index) {
    std::vector<int> finds;
    const int strLen = str.size();
    int i = 0;

    if (index < 0 || index > strLen) {
        index = strLen;
    }

    while (i < index) {
        if (charSet.contains(str[i])) {
            finds.push_back(i);
        }

        i++;
    }

    return finds;
}

/**
 * joins the elements of a vector and returns a string
 * 
 * @param {*} vec 
 * @param {*} separator 
 * @param {*} indexStart inclusive
 * @param {*} indexEnd exclusive
 * @returns 
 */
std::string tvnj::join(std::vector<std::string> vec, std::string separator, int indexStart, int indexEnd) {
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
        s += vec[i] + separator;
    }

    return s + vec[n];
}

/**
 * joins the elements of a vector and returns a string
 * 
 * @param {*} vec 
 * @param {*} separator 
 * @param {*} indexStart inclusive
 * @param {*} indexEnd exclusive
 * @returns 
 */
std::string tvnj::join(std::vector<char> vec, std::string separator, int indexStart, int indexEnd) {
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
        s += vec[i] + separator;
    }

    return s + vec[n];
}

/**
 * get the char at positive and negative indices
 * 
 * @param str 
 * @param index 
 * @returns a character
 */
char tvnj::charAt(std::string str, int index) {
    if (index < 0) {
        index += str.size();
    }

    return str[index];
}

/**
 * python like string slicing
 * 
 * @param str 
 * @param start inclusive
 * @param end exclusive by default
 * @param step increment
 * @param inclusive bool for making the parameter "end" inclusive
 * @return a new string
 */
std::string tvnj::slice(std::string str, int start, int end, int step, bool inclusive) {
    const int len = str.size();

    if (start < 0) {
        start += len;
    }

    if (end < 0) {
        end += len;
    }

    if (step == 0) {
        step = 1;
        // return str.substr(start, end - start);
    }

    std::string newStr = "";

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
                newStr += str[i];
                i += step;
            }

            if (inclusive && i == end) {
                newStr += str[i];
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
                newStr += str[i];
                i += step;
            }

            if (inclusive && i == end) {
                newStr += str[i];
            }
        }
    }

    return newStr;
}

/**
 * @brief 1 row levenshtein distance
 * 
 * @param word1 
 * @param word2 
 * @return int 
 */
int tvnj::editDistanceFast(std::string word1, std::string word2) {
    const int word1Length = word1.size(),
        word2Length = word2.size();

    if (word1Length == 0) {
        return word2Length;
    }
    else if (word2Length == 0) {
        return word1Length;
    }

    std::vector<int> distance(word2Length);

    for (int i = 0; i < word2Length; i++) {
        distance[i] = i + 1;
    }

    /*
        j ->
    i   w o r d 2
    | w
    v o
      r
      d
      1

    left = delete
    corner = replace
    top = insert
    */
    for (int i = 0; i < word1Length; i++) {
        const char currentChar = word1[i];
        int j = 0,
            replace = i,
            insert = distance[j];

        // compute the first element of the array
        if (currentChar == word2[j]) {
            distance[j] = replace;
        }
        else {
            const int deleteChar = i + 1;
            distance[j] = 1 + std::min(std::min(deleteChar, replace), insert);
        }

        j++;

        // compute the rest of the array
        while (j < word2Length) {
            replace = insert;
            insert = distance[j];

            if (currentChar == word2[j]) {
                distance[j] = replace;
            }
            else {
                const int deleteChar = distance[j - 1];
                distance[j] = 1 + std::min(std::min(deleteChar, replace), insert);
            }

            j++;
        }
    }

    return distance[word2Length - 1];
}

/**
 * @brief remove tags not allowed and tags not in the language
 * the document string must have valid syntax
 * 
 * @param document 
 * @param notAllowedTags 
 * @param tagsInLanguage all of the tags in the markup language. pass empty array to skip check for tags not in the language
 * @param attributeQuotes set to true if the attribute values must have quotes
 * @return std::string 
 */
std::string tvnj::sanitizeMarkupLanguage(std::string document, std::vector<std::string> notAllowedTags, std::vector<std::string> tagsInLanguage, bool attributeQuotes) {
    std::string result = document;

    // removed forbidden tags

    for (size_t i = 0; i < notAllowedTags.size(); i++) {
        std::string tag = notAllowedTags[i];
        tag = tvnj::escapeRegex(tag);

        if (attributeQuotes) {
            std::regex tagRegex("(<\\s*(" + tag + ")(\\s+([a-z\\-]+\\s*=\\s*([\"'`])[\\s\\S]*?\\5\\s*)*)?\\s*>[\\s\\S]*<\\s*\\/\\s*\\2\\s*>)|(<\\s*(" + tag + ")(\\s+([a-z\\-]+\\s*=\\s*([\"'`])[\\s\\S]*?\\10\\s*)*)?\\s*\\/\\s*>)", std::regex_constants::icase);
            result = std::regex_replace(result, tagRegex, "");
        }
        else {
            std::regex tagRegex("(<\\s*(" + tag + ")(\\s+([a-z\\-]+\\s*=\\s*(([\"'`])[\\s\\S]*?\\6|[^\\s>]+\\s?)\\s*)*)?\\s*>[\\s\\S]*<\\s*\\/\\s*\\2\\s*>)|(<\\s*(" + tag + ")(\\s+([a-z\\-]+\\s*=\\s*(([\"'`])[\\s\\S]*?\\12|[^\\s/]+\\s?)\\s*)*)?\\s*\\/\\s*>)", std::regex_constants::icase);
            result = std::regex_replace(result, tagRegex, "");
        }
    }

    // remove tags not in the language

    size_t n = tagsInLanguage.size();

    if (n > 0) {
        n--;
        std::string allowedGroup = "((?!(";

        for (size_t i = 0; i < n; i++) {
            std::string tag = tagsInLanguage[i];
            tag = tvnj::escapeRegex(tag);
            allowedGroup += tag + "|";
        }

        std::string tag = tagsInLanguage[n];
        tag = tvnj::escapeRegex(tag);
        allowedGroup += tag + ")";

        if (attributeQuotes) {
            std::regex tagRegex("(<\\s*" + allowedGroup + "[\\s>])[a-z0-9!]+)(\\s+([a-z\\-]+\\s*=\\s*([\"'`])[\\s\\S]*?\\6\\s*)*)?\\s*>[\\s\\S]*<\\s*\\/\\s*\\2\\s*>)|(<\\s*" + allowedGroup + "(\\s+|\\s*\\/\\s*>))[a-z0-9!]+)(\\s+([a-z\\-]+\\s*=\\s*([\"'`])[\\s\\S]*?\\13\\s*)*)?\\s*\\/\\s*>)", std::regex_constants::icase);
            result = std::regex_replace(result, tagRegex, "");
        }
        else {
            std::regex tagRegex("(<\\s*" + allowedGroup + "[\\s>])[a-z0-9!]+)(\\s+([a-z\\-]+\\s*=\\s*(([\"'`])[\\s\\S]*?\\7|[^\\s>]+\\s?)\\s*)*)?\\s*>[\\s\\S]*<\\s*\\/\\s*\\2\\s*>)|(<\\s*" + allowedGroup + "(\\s+|\\s*\\/\\s*>))[a-z0-9!]+)(\\s+([a-z\\-]+\\s*=\\s*(([\"'`])[\\s\\S]*?\\15|[^\\s/]+\\s?)\\s*)*)?\\s*\\/\\s*>)", std::regex_constants::icase);
            result = std::regex_replace(result, tagRegex, "");
        }
    }

    return result;
}

/**
 * @brief detect tags not allowed and tags not in the language
 * the document string must have valid syntax
 * 
 * @param document 
 * @param notAllowedTags 
 * @param tagsInLanguage all of the tags in the markup language. pass empty array to skip check for tags not in the language
 * @param attributeQuotes set to true if the attribute values must have quotes
 * @return std::string 
 */
bool tvnj::isAllowedMarkupLanguage(std::string document, std::vector<std::string> notAllowedTags, std::vector<std::string> tagsInLanguage, bool attributeQuotes) {
    // detect forbidden tags

    for (size_t i = 0; i < notAllowedTags.size(); i++) {
        std::string tag = notAllowedTags[i];
        tag = tvnj::escapeRegex(tag);

        if (attributeQuotes) {
            std::regex tagRegex("(<\\s*(" + tag + ")(\\s+([a-z\\-]+\\s*=\\s*([\"'`])[\\s\\S]*?\\5\\s*)*)?\\s*>[\\s\\S]*<\\s*\\/\\s*\\2\\s*>)|(<\\s*(" + tag + ")(\\s+([a-z\\-]+\\s*=\\s*([\"'`])[\\s\\S]*?\\10\\s*)*)?\\s*\\/\\s*>)", std::regex_constants::icase);

            if (std::regex_search(document, tagRegex)) {
                return false;
            }
        }
        else {
            std::regex tagRegex("(<\\s*(" + tag + ")(\\s+([a-z\\-]+\\s*=\\s*(([\"'`])[\\s\\S]*?\\6|[^\\s>]+\\s?)\\s*)*)?\\s*>[\\s\\S]*<\\s*\\/\\s*\\2\\s*>)|(<\\s*(" + tag + ")(\\s+([a-z\\-]+\\s*=\\s*(([\"'`])[\\s\\S]*?\\12|[^\\s/]+\\s?)\\s*)*)?\\s*\\/\\s*>)", std::regex_constants::icase);

            if (std::regex_search(document, tagRegex)) {
                return false;
            }
        }
    }

    // detect tags not in the language

    size_t n = tagsInLanguage.size();

    if (n > 0) {
        n--;
        std::string allowedGroup = "((?!(";

        for (size_t i = 0; i < n; i++) {
            std::string tag = tagsInLanguage[i];
            tag = tvnj::escapeRegex(tag);
            allowedGroup += tag + "|";
        }

        std::string tag = tagsInLanguage[n];
        tag = tvnj::escapeRegex(tag);
        allowedGroup += tag + ")";

        if (attributeQuotes) {
            std::regex tagRegex("(<\\s*" + allowedGroup + "[\\s>])[a-z0-9!]+)(\\s+([a-z\\-]+\\s*=\\s*([\"'`])[\\s\\S]*?\\6\\s*)*)?\\s*>[\\s\\S]*<\\s*\\/\\s*\\2\\s*>)|(<\\s*" + allowedGroup + "(\\s+|\\s*\\/\\s*>))[a-z0-9!]+)(\\s+([a-z\\-]+\\s*=\\s*([\"'`])[\\s\\S]*?\\13\\s*)*)?\\s*\\/\\s*>)", std::regex_constants::icase);

            if (std::regex_search(document, tagRegex)) {
                return false;
            }
        }
        else {
            std::regex tagRegex("(<\\s*" + allowedGroup + "[\\s>])[a-z0-9!]+)(\\s+([a-z\\-]+\\s*=\\s*(([\"'`])[\\s\\S]*?\\7|[^\\s>]+\\s?)\\s*)*)?\\s*>[\\s\\S]*<\\s*\\/\\s*\\2\\s*>)|(<\\s*" + allowedGroup + "(\\s+|\\s*\\/\\s*>))[a-z0-9!]+)(\\s+([a-z\\-]+\\s*=\\s*(([\"'`])[\\s\\S]*?\\15|[^\\s/]+\\s?)\\s*)*)?\\s*\\/\\s*>)", std::regex_constants::icase);

            if (std::regex_search(document, tagRegex)) {
                return false;
            }
        }
    }

    return true;
}

std::string tvnj::sanitizeSVG(std::string document) {
    return tvnj::sanitizeMarkupLanguage(document, {
        "animate",
        "color-profile",
        "cursor",
        "discard",
        "font-face",
        "font-face-format",
        "font-face-name",
        "font-face-src",
        "font-face-uri",
        "foreignobject",
        "hatch",
        "hatchpath",
        "mesh",
        "meshgradient",
        "meshpatch",
        "meshrow",
        "missing-glyph",
        "script",
        "set",
        "solidcolor",
        "unknown",
        "use"
    }, {
        "a",
        "animate",
        "animateMotion",
        "animateTransform",
        "circle",
        "clipPath",
        "defs",
        "desc",
        "discard",
        "ellipse",
        "feBlend",
        "feColorMatrix",
        "feComponentTransfer",
        "feComposite",
        "feConvolveMatrix",
        "feDiffuseLighting",
        "feDisplacementMap",
        "feDistantLight",
        "feDropShadow",
        "feFlood",
        "feFuncA",
        "feFuncB",
        "feFuncG",
        "feFuncR",
        "feGaussianBlur",
        "feImage",
        "feMerge",
        "feMergeNode",
        "feMorphology",
        "feOffset",
        "fePointLight",
        "feSpecularLighting",
        "feSpotLight",
        "feTile",
        "feTurbulence",
        "filter",
        "foreignObject",
        "g",
        "image",
        "line",
        "linearGradient",
        "marker",
        "mask",
        "metadata",
        "mpath",
        "path",
        "pattern",
        "polygon",
        "polyline",
        "radialGradient",
        "rect",
        "script",
        "set",
        "stop",
        "style",
        "svg",
        "switch",
        "symbol",
        "text",
        "textPath",
        "title",
        "tspan",
        "use",
        "view"
    });
}

bool tvnj::isAllowedSVG(std::string document) {
    return tvnj::isAllowedMarkupLanguage(document, {
        "animate",
        "color-profile",
        "cursor",
        "discard",
        "font-face",
        "font-face-format",
        "font-face-name",
        "font-face-src",
        "font-face-uri",
        "foreignobject",
        "hatch",
        "hatchpath",
        "mesh",
        "meshgradient",
        "meshpatch",
        "meshrow",
        "missing-glyph",
        "script",
        "set",
        "solidcolor",
        "unknown",
        "use"
    }, {
        "a",
        "animate",
        "animateMotion",
        "animateTransform",
        "circle",
        "clipPath",
        "defs",
        "desc",
        "discard",
        "ellipse",
        "feBlend",
        "feColorMatrix",
        "feComponentTransfer",
        "feComposite",
        "feConvolveMatrix",
        "feDiffuseLighting",
        "feDisplacementMap",
        "feDistantLight",
        "feDropShadow",
        "feFlood",
        "feFuncA",
        "feFuncB",
        "feFuncG",
        "feFuncR",
        "feGaussianBlur",
        "feImage",
        "feMerge",
        "feMergeNode",
        "feMorphology",
        "feOffset",
        "fePointLight",
        "feSpecularLighting",
        "feSpotLight",
        "feTile",
        "feTurbulence",
        "filter",
        "foreignObject",
        "g",
        "image",
        "line",
        "linearGradient",
        "marker",
        "mask",
        "metadata",
        "mpath",
        "path",
        "pattern",
        "polygon",
        "polyline",
        "radialGradient",
        "rect",
        "script",
        "set",
        "stop",
        "style",
        "svg",
        "switch",
        "symbol",
        "text",
        "textPath",
        "title",
        "tspan",
        "use",
        "view"
    });
}

tvnj::Trie::TrieNode::TrieNode() {
    this->isEndOfWord = false;
}

bool tvnj::Trie::deleteNode(tvnj::Trie::TrieNode* node, const std::string& word, size_t depth) {
    if (depth == word.size()) {
        if (!node->isEndOfWord) {
            return false;
        }

        node->isEndOfWord = false;
        return node->children.empty();
    }

    char c = word[depth];

    if (!node->children.contains(c)) {
        return false;
    }

    bool shouldDeleteChild = this->deleteNode(node->children[c], word, depth + 1);

    if (shouldDeleteChild) {
        delete node->children[c];
        node->children.erase(c);
        return node->children.empty() && !node->isEndOfWord;
    }

    return false;
}

tvnj::Trie::Trie() {
    this->root = new tvnj::Trie::TrieNode();
}

tvnj::Trie::~Trie() {
    this->freeNode(this->root);
}

void tvnj::Trie::insert(const std::string& word) {
    tvnj::Trie::TrieNode* node = this->root;

    for (char c : word) {
        if (!node->children.contains(c)) {
            node->children[c] = new tvnj::Trie::TrieNode();
        }

        node = node->children[c];
    }

    node->isEndOfWord = true;
}

bool tvnj::Trie::search(const std::string& word) {
    tvnj::Trie::TrieNode* node = this->root;

    for (char c : word) {
        if (!node->children.contains(c)) {
            return false;
        }

        node = node->children[c];
    }

    return node->isEndOfWord;
}

bool tvnj::Trie::startsWith(const std::string& prefix) {
    tvnj::Trie::TrieNode* node = this->root;

    for (char c : prefix) {
        if (!node->children.contains(c)) {
            return false;
        }

        node = node->children[c];
    }

    return true;
}

void tvnj::Trie::remove(const std::string& word) {
    this->deleteNode(this->root, word, 0);
}

void tvnj::Trie::freeNode(tvnj::Trie::TrieNode* node) {
    for (auto& [key, value] : node->children) { // node.children.values()
        this->freeNode(value);
    }

    delete node;
}

tvnj::AhoCorasick::AhoCorasickNode::AhoCorasickNode() {
    this->isEndOfWord = false;
    this->suffixLink = nullptr;
    this->length = 0;
}

bool tvnj::AhoCorasick::deleteTrieNode(tvnj::AhoCorasick::AhoCorasickNode* node, const std::string& word, size_t depth) {
    if (depth == word.size()) {
        if (!node->isEndOfWord) {
            return false;
        }

        node->isEndOfWord = false;
        return node->children.empty();
    }

    char c = word[depth];

    if (!node->children.contains(c)) {
        return false;
    }

    bool shouldDeleteChild = this->deleteTrieNode(node->children[c], word, depth + 1);

    if (shouldDeleteChild) {
        delete node->children[c];
        node->children.erase(c);
        return node->children.empty() && !node->isEndOfWord;
    }

    return false;
}

tvnj::AhoCorasick::AhoCorasick() {
    this->root = new tvnj::AhoCorasick::AhoCorasickNode();
}

tvnj::AhoCorasick::AhoCorasick(const std::vector<std::string>& strings) {
    this->build(strings);
}

void tvnj::AhoCorasick::build(const std::vector<std::string>& strings) {
    this->root = new tvnj::AhoCorasick::AhoCorasickNode();

    for (size_t i = 0; i < strings.size(); i++) {
        this->insertTrie(strings[i]);
    }

    this->constructLinks();
}

tvnj::AhoCorasick::~AhoCorasick() {
    this->freeTrieNode(this->root);
}

void tvnj::AhoCorasick::insertTrie(const std::string& word) {
    tvnj::AhoCorasick::AhoCorasickNode* node = this->root;
    size_t i = 0;

    while (i < word.size()) {
        char c = word[i];
        i++;

        if (!node->children.contains(c)) {
            node->children[c] = new tvnj::AhoCorasick::AhoCorasickNode();
            node->children[c]->length = i; // height of the tree is the length of the string
        }

        node = node->children[c];
    }

    node->outputLinks.insert(node);
    node->isEndOfWord = true;
}

void tvnj::AhoCorasick::insert(const std::string& word) {
    this->insertTrie(word);
    this->constructLinks();
}

/**
 * returns [tuple(index, length), ...]
 */
std::vector<std::pair<size_t, size_t>> tvnj::AhoCorasick::search(const std::string& string) {
    tvnj::AhoCorasick::AhoCorasickNode* node = this->root;
    std::vector<std::pair<size_t, size_t>> output;

    if (node->isEndOfWord) { // empty string case
        output.push_back({0, 0}); // no need to iterate through output links
    }

    size_t i = 0;

    while (i < string.size()) {
        const char c = string[i];
        if (node->children.contains(c)) {
            node = node->children[c];
            i++;

            if (!node->outputLinks.empty()) {
                for (tvnj::AhoCorasick::AhoCorasickNode* outputNode : node->outputLinks) { // node.outputLinks.values()
                    output.push_back({i - outputNode->length, outputNode->length});
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

    return output;
}

void tvnj::AhoCorasick::remove(const std::string& word) {
    this->deleteTrieNode(this->root, word, 0);
    this->deleteLinks();
    this->constructLinks();
}

void tvnj::AhoCorasick::freeTrieNode(tvnj::AhoCorasick::AhoCorasickNode* node) {
    for (auto& [key, value] : node->children) { // node.children.values()
        this->freeTrieNode(value);
    }

    delete node;
}

void tvnj::AhoCorasick::constructLinks() {
    // BFS
    std::queue<tvnj::AhoCorasick::AhoCorasickNode*> nodeQueue;

    for (auto& [key, value] : this->root->children) { // node.children.values()
        nodeQueue.push(value);
        value->suffixLink = this->root;
    }

    while (!nodeQueue.empty()) {
        tvnj::AhoCorasick::AhoCorasickNode* currentNode = nodeQueue.front();
        nodeQueue.pop();

        for (auto& [key, value] : currentNode->children) { // node.children.values()
            nodeQueue.push(value);

            // output links
            tvnj::AhoCorasick::AhoCorasickNode* childFailureNode = currentNode->suffixLink;
            while (childFailureNode != nullptr && !childFailureNode->children.contains(key)) {
                childFailureNode = childFailureNode->suffixLink;
            }

            if (childFailureNode != nullptr) {
                value->suffixLink = childFailureNode->children[key];
            }
            else {
                value->suffixLink = this->root;
            }

            if (value->suffixLink->isEndOfWord) {
                value->outputLinks.insert(value->suffixLink->outputLinks.begin(), value->suffixLink->outputLinks.end()); // set1 U copy(set2)
            }
        }
    }
}

void tvnj::AhoCorasick::deleteLinks() {
    // DFS becuase of stack implementation
    std::stack<tvnj::AhoCorasick::AhoCorasickNode*> nodeStack;
    nodeStack.push(this->root);

    while (!nodeStack.empty()) {
        tvnj::AhoCorasick::AhoCorasickNode* currentNode = nodeStack.top();
        nodeStack.pop();

        // clear out all links because some are pointing to the deleted nodes
        currentNode->suffixLink = nullptr;
        currentNode->outputLinks.clear();

        if (currentNode->isEndOfWord) {
            currentNode->outputLinks.insert(currentNode);
        }

        for (auto& [key, value] : currentNode->children) { // node.children.values()
            nodeStack.push(value);
        }
    }
}
