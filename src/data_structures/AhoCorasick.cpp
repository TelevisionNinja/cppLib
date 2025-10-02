#include "AhoCorasick.h"
#include <queue>
#include <stack>

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
    // DFS becuase of stack implementation time complexity. traversal order does not matter
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
