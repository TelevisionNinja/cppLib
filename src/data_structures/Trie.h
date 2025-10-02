#ifndef TRIE_H
#define TRIE_H

#include <string>
#include <unordered_map>

namespace tvnj {
    class Trie {
        private:
            class TrieNode {
                public:
                    std::unordered_map<char, TrieNode*> children; // can be replaced with array if alphabet is known
                    bool isEndOfWord;

                    TrieNode();
            };

            TrieNode* root;

            bool deleteNode(TrieNode* node, const std::string& word, size_t depth);
            void freeNode(TrieNode* node);

        public:
            Trie();
            ~Trie();

            void insert(const std::string& word);
            bool search(const std::string& word);
            bool startsWith(const std::string& prefix);
            void remove(const std::string& word);
    };
}

#endif
