#include "stringUtils.h"
#include <stdexcept>

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
std::string tvnj::trimChar(std::string str, char trimChar) {
    int end = str.size();
    while (end) {
        --end;

        if (str[end] != trimChar) {
            ++end;
            break;
        }
    }

    if (!end) {
        return "";
    }

    int start = 0;
    while (str[start] == trimChar) {
        ++start;
    }

    return str.substr(start, end - start);
}

//-------------------------------------------------

/**
 * trims a substring from a string
 * 
 * @param {*} str str to be trimmmed
 * @param {*} trimSubstr substring that will be trimed off of the str
 * @returns 
 */
std::string tvnj::trimSubstr(std::string str, std::string trimSubstr) {
    const int substrLen = trimSubstr.size();
    int end = str.size();

    if (!substrLen || end < substrLen) {
        return str;
    }

    int strIndex = end,
        substrIndex = substrLen;
    while (strIndex) {
        --strIndex;
        --substrIndex;

        if (str[strIndex] != trimSubstr[substrIndex]) {
            break;
        }

        if (!substrIndex) {
            end = strIndex,
                substrIndex = substrLen;
        }
    }

    if (!end) {
        return "";
    }

    int start = 0;
    strIndex = 0,
        substrIndex = 0;
    while (str[strIndex] == trimSubstr[substrIndex]) {
        ++strIndex;
        ++substrIndex;

        if (substrIndex == substrLen) {
            start = strIndex,
                substrIndex = 0;
        }
    }

    return str.substr(start, end - start);
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

    bool isSpace = true;

    for (int i = 0; i <= limit; i++) {
        if (whitespaceChars.count(str[i])) {
            isSpace = true;
        }
        else if (isSpace) {
            isSpace = false;

            if (i == limit || whitespaceChars.count(str[i + substrLen])) {
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

    if (!substrLen) {
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

                if (!indexSkip && compareChar == firstChar) {
                    indexSkip = j;
                }

                if (compareChar == substr[j]) {
                    j++;
                }
                else {
                    if (!indexSkip) {
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

    if (!substrLen) {
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
std::string tvnj::replace(std::string str, std::string substr, std::string replacement, int index) {
    const int substrLen = substr.size();

    if (!substrLen) {
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

                if (!indexSkip && compareChar == firstChar) {
                    indexSkip = j;
                }

                if (compareChar == substr[j]) {
                    j++;
                }
                else {
                    if (!indexSkip) {
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
 * @param {*} index 
 * @returns 
 */
std::string tvnj::replaceLast(std::string str, std::string substr, std::string replacement, int index) {
    int substrLen = substr.size();

    if (!substrLen) {
        return str;
    }

    substrLen--;

    const int strLen = str.size() - 1;
    const char lastChar = substr[substrLen];
    int i = index;

    if (index < 0 || index > strLen) {
        i = strLen;
    }

    while (i >= substrLen) {
        if (str[i] == lastChar) {
            int j = 1,
                indexSkip = 0;

            while (j <= substrLen) {
                const char compareChar = str[i - j];

                if (!indexSkip && compareChar == lastChar) {
                    indexSkip = j;
                }

                if (compareChar == substr[substrLen - j]) {
                    j++;
                }
                else {
                    if (!indexSkip) {
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
 * replaces n instances of the substring
 * 
 * @param {*} str 
 * @param {*} substr 
 * @param {*} replacement 
 * @param {*} n 
 * @param {*} index 
 * @returns 
 */
std::string tvnj::replaceNTimes(std::string str, std::string substr, std::string replacement, int n, int index) {
    const int substrLen = substr.size();

    if (!substrLen || !n) {
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

                if (!indexSkip && compareChar == firstChar) {
                    indexSkip = j;
                }

                if (compareChar == substr[j]) {
                    j++;
                }
                else {
                    if (!indexSkip) {
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
 * @param {*} index 
 * @returns 
 */
std::string tvnj::replaceNTimesLast(std::string str, std::string substr, std::string replacement, int n, int index) {
    int substrLen = substr.size();

    if (!substrLen || !n) {
        return str;
    }

    substrLen--;

    const int strLen = str.size() - 1;
    const char lastChar = substr[substrLen];
    int i = index,
        count = 0;

    if (index < 0 || index > strLen) {
        i = strLen;
    }

    while (i >= substrLen) {
        if (str[i] == lastChar) {
            int j = 1,
                indexSkip = 0;

            while (j <= substrLen) {
                const char compareChar = str[i - j];

                if (!indexSkip && compareChar == lastChar) {
                    indexSkip = j;
                }

                if (compareChar == substr[substrLen - j]) {
                    j++;
                }
                else {
                    if (!indexSkip) {
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

    for (int i = 0, len = str.size(); i < len; i++) {
        const char current = str[i];

        if (current == delimiter) {
            words.push_back(word);
            word = "";
        }
        else {
            word += current;
        }
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
std::string tvnj::trimCharArr(std::string str, std::vector<char> charArr) {
    const int charsLen = charArr.size();
    int end = str.size();

    while (end) {
        --end;
        const char current = str[end];
        int i = 0;

        while (i < charsLen && current != charArr[i]) {
            i++;
        }

        if (i == charsLen) {
            ++end;
            break;
        }
    }

    if (!end) {
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

        ++start;
    }

    return str.substr(start, end - start);
}

/**
 * trims a set of characters from a string
 * 
 * @param {*} str 
 * @param {*} charSet chars that will be trimed off of the str
 * @returns 
 */
std::string tvnj::trimCharSet(std::string str, std::unordered_set<char> charSet) {
    int end = str.size();

    while (end) {
        --end;
 
        if (!charSet.count(str[end])) {
            ++end;
            break;
        }
    }

    if (!end) {
        return "";
    }

    int start = 0;

    while (charSet.count(str[start])) {
        ++start;
    }

    return str.substr(start, end - start);
}

//-------------------------------------------------

/**
 * trims a list of substrings from a string
 * 
 * @param {*} str 
 * @param {*} substrArr substrings that will be trimed off of the str, must be sorted from longest to shortest
 * @returns 
 */
std::string tvnj::trimSubstrArr(std::string str, std::vector<std::string> substrArr) {
    const int substrsLen = substrArr.size();

    /*
    reject substring arrays with empty strings, (assumes the list is not sorted by length)
    use this if statement if the array will always be sorted:

    if (!substrsLen || !substrArr[0].size()) {
        return str;
    }
    */
    for (int i = 0; i < substrsLen; i++) {
        if (!substrArr[i].size()) {
            return str;
        }
    }

    int end = str.size();

    while (end) {
        int i = 0;

        while (i < substrsLen) {
            const std::string substr = substrArr[i];
            int substrIndex = substr.size();

            if (substrIndex <= end) {
                int strIndex = end;

                while (substrIndex) {
                    --strIndex;
                    --substrIndex;

                    if (str[strIndex] != substr[substrIndex]) {
                        ++substrIndex;
                        break;
                    }
                }

                if (!substrIndex) {
                    end = strIndex;
                    break;
                }
            }

            i++;
        }

        if (i == substrsLen) {
            break;
        }
    }

    if (!end) {
        return "";
    }

    int start = 0,
        len = end;

    while (true) {
        int i = 0;

        while (i < substrsLen) {
            const std::string substr = substrArr[i];
            const int substrLen = substr.size();

            i++;

            if (substrLen < len) {
                int strIndex = start,
                    substrIndex = 0;

                while (str[strIndex] == substr[substrIndex]) {
                    ++strIndex;
                    ++substrIndex;

                    if (substrIndex == substrLen) {
                        start = strIndex;
                        len = end - start;
                        i = 0;
                        break;
                    }
                }
            }
        }

        if (i == substrsLen) {
            break;
        }
    }

    return str.substr(start, len);
}

//-------------------------------------------------

/**
 * trim whitespace
 * 
 * @param {*} str 
 * @returns 
 */
std::string tvnj::trim(std::string str) {
    return tvnj::trimCharSet(str, whitespaceChars);
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
    const int substrLen = substr.size();

    if (!substrLen) {
        return -1;
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

                if (!indexSkip && compareChar == firstChar) {
                    indexSkip = j;
                }

                if (compareChar == substr[j]) {
                    j++;
                }
                else {
                    if (!indexSkip) {
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
    int substrLen = substr.size();

    if (!substrLen) {
        return 0;
    }

    substrLen--;

    const int strLen = str.size() - 1;
    const char lastChar = substr[substrLen];
    int i = index;

    if (index < 0 || index > strLen) {
        i = strLen;
    }

    while (i >= substrLen) {
        if (str[i] == lastChar) {
            int j = 1,
                indexSkip = 0;

            while (j <= substrLen) {
                const char compareChar = str[i - j];

                if (!indexSkip && compareChar == lastChar) {
                    indexSkip = j;
                }

                if (compareChar == substr[substrLen - j]) {
                    j++;
                }
                else {
                    if (!indexSkip) {
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

    if (!substrLen) {
        return -1;
    }

    if (substrLen == 1) {
        return tvnj::indexOfChar(str, substr[0], index);
    }

    if (substrLen <= 8192) {
        return tvnj::indexOfNaiveSkip(str, substr, index);
    }

    return tvnj::indexOfTwoWay(str, substr, index);
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
                ++k;
            }
        }
        else { // a > b
            *maxSuffix = j;
            ++j;
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
                ++k;
            }
        }
        else { // a < b
            *maxSuffix = j;
            ++j;
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

    for (int index = 0; index <= suffix; ++index) {
        if (substr[index] != substr[index + period]) {
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

            ++i;

            //-------------------
            // scan for matches in the right half

            while (i < substrLen && substr[i] == str[i + j]) {
                ++i;
            }

            if (i >= substrLen) {
                // scan for matches in the left half

                i = suffix;

                while (i > memory && substr[i] == str[i + j]) {
                    --i;
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

        ++period;

        //-------------------

        while (j <= limit) {
            i = firstValue;

            while (i < substrLen && substr[i] == str[i + j]) {
                ++i;
            }

            if (i >= substrLen) {
                i = suffix;

                while (i >= 0 && substr[i] == str[i + j]) {
                    --i;
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
    const int substrLen = substr.size();

    if (!substrLen) {
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
    int substrLen = substr.size();

    if (!substrLen) {
        return 0;
    }

    substrLen--;

    const int strLen = str.size() - 1;
    const char lastChar = substr[substrLen];
    int i = index;

    if (index < 0 || index > strLen) {
        i = strLen;
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
    const int strLen = str.size() - 1;
    int i = index;

    if (index < 0 || index > strLen) {
        i = strLen;
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
std::string tvnj::properCase(std::string str) {
    std::string proper = "";
    bool isSpace = true;
    const int n = str.size();
    int i = 0;

    while (i < n) {
        char c = str[i];

        if (c == ' ') {
            isSpace = true;
        }
        else if (isSpace) {
            isSpace = false;
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