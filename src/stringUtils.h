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

        replace(std::string str, std::string substr, std::string replacement, int index = 0),
        replaceLast(std::string str, std::string substr, std::string replacement, int index = -1),

        replaceNTimes(std::string str, std::string substr, std::string replacement, int n, int index = 0),
        replaceNTimesLast(std::string str, std::string substr, std::string replacement, int n, int index = -1);

    //-------------------------------------------------

    std::vector<std::string> split(std::string str, char delimiter = ' ');

    //-------------------------------------------------

    std::string trim(std::string str),

        trimChar(std::string str, char trimChar),
        trimSubstr(std::string str, std::string trimSubstr),

        trimCharArr(std::string str, std::vector<char> charArr),
        trimCharSet(std::string str, std::unordered_set<char> charSet),

        trimSubstrArr(std::string str, std::vector<std::string> substrArr);

    //-------------------------------------------------

    int indexOf(std::string str, std::string substr, int index = 0),

        indexOfTwoWay(std::string str, std::string substr, int index = 0),

        indexOfNaive(std::string str, std::string substr, int index = 0),
        indexOfNaiveLast(std::string str, std::string substr, int index = -1),

        indexOfNaiveSkip(std::string str, std::string substr, int index = 0),
        indexOfNaiveSkipLast(std::string str, std::string substr, int index = -1),

        indexOfChar(std::string str, char substr, int index = 0),
        indexOfCharLast(std::string str, char substr, int index = -1);

    //-------------------------------------------------

    std::vector<std::string> cmdLnToArgArr(std::string cmdLn, bool throwError = true);

    //-------------------------------------------------

    std::string properCase(std::string str),
        toLowerCase(std::string str),
        toUpperCase(std::string str);
}

#endif
