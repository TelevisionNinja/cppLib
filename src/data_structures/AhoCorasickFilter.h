#ifndef AHOCORASICKFILTER_H
#define AHOCORASICKFILTER_H

#include "AhoCorasick.h"

namespace tvnj {
    class AhoCorasickFilter : public AhoCorasick {
        public:
            std::string filter(const std::string& string, const std::string& censoredString = "*");
            std::string filterAndIgnoreChars(const std::string& string, const std::string& censoredString, std::unordered_set<char> ignoreChars);
    };
}

#endif
