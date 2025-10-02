#include "Trie.h"

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
