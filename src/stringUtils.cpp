#include "stringUtils.h"
#include <stdexcept>
#include <algorithm>

const std::unordered_set<char> whitespaceChars = {
    '\n',
    '\r',
    '\t',
    ' ',
    '\v',
    '\f'
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
    while (end) {
        end--;

        if (str[end] != trimChar) {
            end++;
            break;
        }
    }

    if (end == 0) {
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

    while (end) {
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

    int strIndex = end,
        substrIndex = substrLen;
    while (strIndex) {
        strIndex--;
        substrIndex--;

        if (str[strIndex] != trimSubstr[substrIndex]) {
            break;
        }

        if (substrIndex == 0) {
            end = strIndex;
            substrIndex = substrLen;
        }
    }

    if (end == 0) {
        return "";
    }

    int start = 0;
    strIndex = 0;
    substrIndex = 0;
    while (str[strIndex] == trimSubstr[substrIndex]) {
        strIndex++;
        substrIndex++;

        if (substrIndex == substrLen) {
            start = strIndex;
            substrIndex = 0;
        }
    }

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

    int start = 0,
        strIndex = 0,
        substrIndex = 0;
    while (start < len) {
        if (str[strIndex] != trimSubstr[substrIndex]) {
            return str.substr(start);
        }

        strIndex++;
        substrIndex++;

        if (substrIndex == substrLen) {
            start = strIndex;
            substrIndex = 0;
        }
    }

    return "";
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
    int end = str.size();

    if (substrLen == 0 || end < substrLen) {
        return str;
    }

    int strIndex = end,
        substrIndex = substrLen;
    while (strIndex) {
        strIndex--;
        substrIndex--;

        if (str[strIndex] != trimSubstr[substrIndex]) {
            return str.substr(0, end);
        }

        if (substrIndex == 0) {
            end = strIndex;
            substrIndex = substrLen;
        }
    }

    return "";
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
std::string tvnj::cutOff(std::string str, int charLimit) {
    if (str.size() > charLimit) {
        return str.substr(0, charLimit - 3) + "...";
    }

    return str;
}

//-------------------------------------------------

const std::vector<std::string> entities = {
    "&lt;",
    "&gt;",
    "&amp;",
    "&#39;",
    "&apos;",
    "&quot;"
};
const std::vector<std::string> entityChars = {
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
    const int entityLen = entities.size();

    for (int i = 0, strLen = str.size(); i < strLen; i++) {
        if (str[i] == '&') {
            for (int j = 0; j < entityLen; j++) {
                const std::string entity = entities[j];
                const int len = entity.size(),
                    lowerLen = len - 1;

                if (i + len <= strLen && str[i + lowerLen] == ';') {
                    int k = 1;

                    while (k < lowerLen && str[i + k] == entity[k]) {
                        k++;
                    }

                    if (k == lowerLen) {
                        str.replace(i, len, entityChars[j]);
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
    const int entityLen = entities.size();

    for (int i = 0, strLen = str.size(); i < strLen; i++) {
        if (str[i] == '&') {
            for (int j = 0; j < entityLen; j++) {
                const std::string entity = entities[j];
                const int len = entity.size(),
                    lowerLen = len - 1;

                if (i + len <= strLen) {
                    if (str[i + lowerLen] == ';') {
                        int k = 1;

                        while (k < lowerLen && str[i + k] == entity[k]) {
                            k++;
                        }

                        if (k == lowerLen) {
                            str.replace(i, len, entityChars[j]);
                            strLen -= lowerLen;
                            break;
                        }
                    }
                }
                else {
                    break;
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
bool tvnj::includesPhrase1(std::string str, std::string phrase, bool caseSensitive) {
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

            if (i == limit || whitespaceChars.contains(str[i + substrLen])) {
                int j = 0;

                while (j < substrLen && str[i + j] == phrase[j]) {
                    j++;
                }

                if (j == substrLen) {
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
std::string tvnj::replaceAll1(std::string str, std::string substr, std::string replacement) {
    const int substrLen = substr.size();

    if (substrLen == 0) {
        return str;
    }

    const char firstChar = substr[0];
    int i = 0,
        strLen = str.size() - substrLen;
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

            if (j == substrLen) {
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
 * replaces all instances of the substring
 * 
 * @param {*} str 
 * @param {*} substr 
 * @param {*} replacement 
 * @returns 
 */
std::string tvnj::replaceAll2(std::string str, std::string substr, std::string replacement) {
    const int substrLen = substr.size();

    if (substrLen == 0) {
        return str;
    }

    const int replacementLen = replacement.size();
    int i = str.find(substr, 0);

    while (i != std::string::npos) {
        str.replace(i, substrLen, replacement);
        i = str.find(substr, i + replacementLen);
    }

    return str;
}

//-------------------------------------------------

/**
 * replaces the 1st instance of the substring
 * 
 * @param {*} str 
 * @param {*} substr 
 * @param {*} replacement 
 * @param {*} index 
 * @returns 
 */
std::string tvnj::replaceFirst(std::string str, std::string substr, std::string replacement, int index) {
    const int substrLen = substr.size();

    if (substrLen == 0 || index < 0) {
        return str;
    }

    const char firstChar = substr[0];
    int i = index;
    const int strLen = str.size() - substrLen;

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

            if (j == substrLen) {
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
 * replaces the last instance of the substring
 * 
 * @param {*} str 
 * @param {*} substr 
 * @param {*} replacement 
 * @param {*} index inclusive
 * @returns 
 */
std::string tvnj::replaceLast(std::string str, std::string substr, std::string replacement, int index) {
    int substrLen = substr.size();

    if (substrLen == 0) {
        return str;
    }

    substrLen--;

    const char lastChar = substr[substrLen];
    int i = str.size() - 1;

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
 * replaces n instances of the substring starting from the left side
 * 
 * @param {*} str 
 * @param {*} substr 
 * @param {*} replacement 
 * @param {*} n 
 * @param {*} index 
 * @returns 
 */
std::string tvnj::replaceNTimesLeft(std::string str, std::string substr, std::string replacement, int n, int index) {
    const int substrLen = substr.size();

    if (substrLen == 0 || n <= 0 || index < 0) {
        return str;
    }

    const char firstChar = substr[0];
    int i = index,
        strLen = str.size() - substrLen,
        count = 0;
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

            if (j == substrLen) {
                str.replace(i, substrLen, replacement);

                count++;
                if (count == n) {
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
    int substrLen = substr.size();

    if (substrLen == 0 || n <= 0) {
        return str;
    }

    substrLen--;

    const char lastChar = substr[substrLen];
    int i = str.size() - 1,
        count = 0;

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
                if (count == n) {
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
 * splits strings by a specified delimiter from the left side
 * 
 * @param {*} str 
 * @param {*} delimiter 
 * @param {*} n 
 * @param {*} index 
 * @returns 
 */
std::vector<std::string> tvnj::splitNTimesLeft(std::string str, char delimiter, int n, int index) {
    std::vector<std::string> words;

    if (n <= 0 || index < 0) {
        words.push_back(str);
        return words;
    }

    std::string word = "";
    const int len = str.size();
    int i = index,
        count = 0;

    while (i < len) {
        const char current = str[i];

        if (current == delimiter) {
            words.push_back(word);

            count++;
            if (count == n) {
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
 * splits strings by a specified delimiter from the right side
 * 
 * @param {*} str 
 * @param {*} delimiter 
 * @param {*} n 
 * @param {*} index 
 * @returns 
 */
std::vector<std::string> tvnj::splitNTimesRight(std::string str, char delimiter, int n, int index) {
    std::vector<std::string> words;

    if (n <= 0) {
        words.push_back(str);
        return words;
    }

    std::string word = "";
    int i = str.size() - 1,
        count = 0;

    if (index >= 0 && index <= i) {
        i = index;
    }

    while (i >= 0) {
        const char current = str[i];

        if (current == delimiter) {
            words.push_back(word);

            count++;
            if (count == n) {
                words.push_back(str.substr(0, i));
                std::reverse(words.begin(), words.end());
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
    std::reverse(words.begin(), words.end());
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
 * splits strings by a specified delimiters from the left side
 * 
 * @param {*} str 
 * @param {*} delimiters set of delimiters
 * @param {*} n 
 * @param {*} index 
 * @returns 
 */
std::vector<std::string> tvnj::splitNTimesLeft(std::string str, std::unordered_set<char> delimiters, int n, int index) {
    std::vector<std::string> words;

    if (n <= 0 || index < 0) {
        words.push_back(str);
        return words;
    }

    std::string word = "";
    const int len = str.size();
    int i = index,
        count = 0;

    while (i < len) {
        const char current = str[i];

        if (delimiters.contains(current)) {
            words.push_back(word);

            count++;
            if (count == n) {
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
 * splits strings by a specified delimiters from the right side
 * 
 * @param {*} str 
 * @param {*} delimiters set of delimiters
 * @param {*} n 
 * @param {*} index 
 * @returns 
 */
std::vector<std::string> tvnj::splitNTimesRight(std::string str, std::unordered_set<char> delimiters, int n, int index) {
    std::vector<std::string> words;

    if (n <= 0) {
        words.push_back(str);
        return words;
    }

    std::string word = "";
    int i = str.size() - 1,
        count = 0;

    if (index >= 0 && index <= i) {
        i = index;
    }

    while (i >= 0) {
        const char current = str[i];

        if (delimiters.contains(current)) {
            words.push_back(word);

            count++;
            if (count == n) {
                words.push_back(str.substr(0, i));
                std::reverse(words.begin(), words.end());
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
    std::reverse(words.begin(), words.end());
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

            if (j == delimiterLen) {
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
 * splits strings by a specified delimiter from the left side
 * 
 * @param {*} str 
 * @param {*} delimiter 
 * @param {*} n 
 * @param {*} index 
 * @returns 
 */
std::vector<std::string> tvnj::splitNTimesLeft(std::string str, std::string delimiter, int n, int index) {
    std::vector<std::string> words;
    const int delimiterLen = delimiter.size();

    if (delimiterLen == 0 || n <= 0 || index < 0) {
        words.push_back(str);
        return words;
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

            if (j == delimiterLen) {
                words.push_back(word);
                i += delimiterLen;

                count++;
                if (count == n) {
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
 * splits strings by a specified delimiter from the right side
 * 
 * @param {*} str 
 * @param {*} delimiter 
 * @param {*} n 
 * @param {*} index inclusive
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
                if (count == n) {
                    words.push_back(str.substr(0, i - delimiterLen));
                    std::reverse(words.begin(), words.end());
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

    if (i > 0) {
        words.push_back(str.substr(0, i) + word);
    }
    else {
        words.push_back(word);
    }

    std::reverse(words.begin(), words.end());
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

    while (end) {
        end--;
        const char current = str[end];
        int i = 0;

        while (i < charsLen && current != charArr[i]) {
            i++;
        }

        if (i == charsLen) {
            end++;
            break;
        }
    }

    if (end == 0) {
        return "";
    }

    int start = 0;

    while (true) {
        const char current = str[start];
        int i = 0;

        while (i < charsLen && current != charArr[i]) {
            i++;
        }

        if (i == charsLen) {
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

    while (end) {
        end--;
 
        if (!charSet.contains(str[end])) {
            end++;
            break;
        }
    }

    if (end == 0) {
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

    while (end) {
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

            while (substrIndex) {
                strIndex--;
                substrIndex--;

                if (str[strIndex] != substr[substrIndex]) {
                    substrIndex++;
                    break;
                }
            }

            if (substrIndex == 0) {
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

    if (end == 0) {
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

                if (substrIndex == substrLen) {
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

                if (substrIndex == substrLen) {
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

            while (substrIndex) {
                strIndex--;
                substrIndex--;

                if (str[strIndex] != substr[substrIndex]) {
                    substrIndex++;
                    break;
                }
            }

            if (substrIndex == 0) {
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
 * @param {*} index starting index
 * @returns index of the substring, returns -1 if not found
 */
int tvnj::indexOfNaiveSkip(std::string str, std::string substr, int index) {
    if (index < 0) {
        return -1;
    }

    const int substrLen = substr.size();

    if (substrLen == 0) {
        return 0;
    }

    const char firstChar = substr[0];
    int i = index;
    const int strLen = str.size() - substrLen;

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

            if (j == substrLen) {
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
        i = str.size() - 1;

    if (substrLen == 0) {
        if (i == -1) {
            return 0;
        }

        return i;
    }

    substrLen--;

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
 * @param {*} index starting index
 * @returns index of the substring, returns -1 if not found
 */
int tvnj::indexOf(std::string str, std::string substr, int index) {
    const int substrLen = substr.size();

    if (substrLen == 0) {
        return 0;
    }

    if (substrLen == 1) {
        return tvnj::indexOfChar(str, substr[0], index);
    }

    if (substrLen <= 8192) {
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
 * @param {*} index starting index
 * @returns index of the substring, returns -1 if not found
 */
int tvnj::indexOfTwoWay(std::string str, std::string substr, int index) {
    if (index < 0) {
        return -1;
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
 * @param {*} index starting index
 * @returns index of the substring, returns -1 if not found
 */
int tvnj::indexOfNaive(std::string str, std::string substr, int index) {
    if (index < 0) {
        return -1;
    }

    const int substrLen = substr.size();

    if (substrLen == 0) {
        return 0;
    }

    const int strLen = str.size() - substrLen;
    const char firstChar = substr[0];
    int i = index;

    while (i <= strLen) {
        if (str[i] == firstChar) {
            int j = 1;

            while (j < substrLen && str[i + j] == substr[j]) {
                j++;
            }

            if (j == substrLen) {
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
 * uses slightly smarter brute force
 * 
 * @param {*} str 
 * @param {*} substr 
 * @param {*} index starting index from the right (inclusive)
 * @returns index of the substring, returns -1 if not found
 */
int tvnj::indexOfNaiveLast(std::string str, std::string substr, int index) {
    int substrLen = substr.size(),
        i = str.size() - 1;

    if (substrLen == 0) {
        if (i == -1) {
            return 0;
        }

        return i;
    }

    substrLen--;

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
 * @param {*} index starting index
 * @returns index of the char, returns -1 if not found
 */
int tvnj::indexOfChar(std::string str, char c, int index) {
    if (index < 0) {
        return -1;
    }

    const int strLen = str.size();
    int i = index;

    while (i < strLen) {
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

    while (i >= 0) {
        if (str[i] == c) {
            return i;
        }

        i--;
    }

    return -1;
}

/**
 * parses a command line string into an array w/o any space char elements
 * 
 * @param {*} cmdLn 
 * @param {*} throwError 
 * @returns string array
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
        if (len - startOfArg) {
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
 * @param {*} index inclusive
 * @returns 
 */
bool tvnj::startsWith(std::string str, std::string substr, int index) {
    const int strLen = str.size(),
        substrLen = substr.size();

    if (strLen < substrLen || index < 0) {
        return false;
    }

    if (strLen == 0) {
        return true;
    }

    int i = index;

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
 * @param {*} substr 
 * @param {*} length 
 * @returns 
 */
bool tvnj::endsWith(std::string str, std::string substr, int length) {
    int strLen = str.size(),
        substrLen = substr.size();

    if (length >= 0 && length <= substrLen) {
        substrLen = length;
    }

    if (strLen < substrLen) {
        return false;
    }

    if (strLen == 0) {
        return true;
    }

    while (substrLen) {
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
 * 
 * @param {*} str
 * @param {*} n
 * @returns
 */
std::string tvnj::repeat(std::string str, int n) {
    std::string repeated = "";

    for (int i = 0; i < n; i++) {
        repeated += str;
    }

    return repeated;
}

/**
 * 
 * @param {*} str 
 * @param {*} len 
 * @param {*} c 
 * @returns
 */
std::string tvnj::padLeft(std::string str, int len, char c) {
    const int n = len - str.size();

    for (int i = 0; i < n; i++) {
        str = c + str;
    }

    return str;
}

/**
 * 
 * @param {*} str 
 * @param {*} len 
 * @param {*} c 
 * @returns
 */
std::string tvnj::padRight(std::string str, int len, char c) {
    const int n = len - str.size();

    for (int i = 0; i < n; i++) {
        str += c;
    }

    return str;
}

/**
 * finds the first instance of the substring
 * 
 * this implementation jumps to the second occurance of the substring's first char when a comparison failed in the substring comparison loop
 * 
 * @param {*} str 
 * @param {*} substr 
 * @param {*} index starting index
 * @param {*} includeOverlap 
 * @returns index of the substring, returns an empty vector if not found
 */
std::vector<int> tvnj::indexOfAll(std::string str, std::string substr, int index, bool includeOverlap) {
    std::vector<int> finds;

    if (index < 0) {
        return finds;
    }

    const int substrLen = substr.size();

    if (substrLen == 0) {
        finds.push_back(0);
        return finds;
    }

    const char firstChar = substr[0];
    int i = index;
    const int strLen = str.size() - substrLen;

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

            if (j == substrLen) {
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
