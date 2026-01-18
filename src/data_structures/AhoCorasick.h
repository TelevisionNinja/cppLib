#ifndef AHOCORASICK_H
#define AHOCORASICK_H

#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <tuple>

namespace tvnj {
    class AhoCorasick {
        protected:
            class AhoCorasickNode {
                public:
                    std::unordered_map<char, AhoCorasickNode*> children; // can be replaced with array if alphabet is known
                    AhoCorasickNode* suffixLink;
                    std::unordered_set<AhoCorasickNode*> outputLinks;
                    size_t length;

                    AhoCorasickNode();
            };

            AhoCorasickNode* root;

            bool deleteTrieNode(AhoCorasickNode* node, const std::string& word, size_t depth);
            void freeTrieNode(AhoCorasickNode* node);
            void deleteLinks();

            void insertTrie(const std::string& word);
            void constructLinks();

        public:
            AhoCorasick();
            AhoCorasick(const std::vector<std::string>& strings);
            ~AhoCorasick();

            void insert(const std::string& word);
            void build(const std::vector<std::string>& strings);
            std::vector<std::pair<size_t, size_t>> search(const std::string& string);
            std::vector<std::tuple<size_t, size_t, size_t, size_t>> searchVerbose(const std::string& string);

            void remove(const std::string& word);
    };
}

#endif
