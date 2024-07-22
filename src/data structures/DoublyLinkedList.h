#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H

#include <string>

namespace tvnj {
    template<typename type>
    class DoublyLinkedList {
        public:
            DoublyLinkedList() {
                this->head = nullptr;
                this->tail = nullptr;
                this->length = 0;
            };
            DoublyLinkedList(const tvnj::DoublyLinkedList<type> & list) {
                if (list.length == 0) {
                    this->head = nullptr;
                    this->tail = nullptr;
                    this->length = 0;
                }
                else {
                    Node * currentNodeOther = list.head;
                    this->head = new Node(currentNodeOther->value);
                    Node * currentNode = this->head;
                    currentNodeOther = currentNodeOther->next;

                    // iterate through the list to copy the nodes
                    while (currentNodeOther != nullptr) {
                        currentNode->next = new Node(currentNodeOther->value, nullptr, currentNode);
                        currentNodeOther = currentNodeOther->next;
                        currentNode = currentNode->next;
                    }

                    this->tail = currentNode;
                    this->length = list.length;
                }
            };
            ~DoublyLinkedList() {};

            size_t size() const {
                return this->length;
            };

            std::string toString() const {
                size_t n = this->length;

                if (n == 0) {
                    return "";
                }

                n--;

                std::string s = "";
                Node * currentNode = this->head;

                for (size_t i = 0; i < n; i++) {
                    s += std::to_string(currentNode->value) + " ";
                    currentNode = currentNode->next;
                }

                return s + std::to_string(currentNode->value);
            };

            void insertHead(type value) {
                Node * node = new Node(value, this->head, nullptr);

                if (this->head == nullptr) {
                    this->tail = node;
                }
                else {
                    this->head->previous = node;
                }

                this->head = node;
                this->length++;
            };

            void insertTail(type value) {
                Node * node = new Node(value, nullptr, this->tail);

                if (this->tail == nullptr) {
                    this->head = node;
                }
                else {
                    this->tail->next = node;
                }

                this->tail = node;
                this->length++;
            };

            void sortedInsert(type value) {
                Node * newNode = new Node(value);

                // insert into empty list
                if (this->head == nullptr) {
                    this->head = newNode;
                    this->tail = newNode;
                }

                // insert before head
                else if (value <= this->head->value) {
                    newNode->next = this->head;
                    this->head->previous = newNode;
                    this->head = newNode;
                }

                // insert after tail
                else if (value >= this->tail->value) {
                    newNode->previous = this->tail;
                    this->tail->next = newNode;
                    this->tail = newNode;
                }

                // insert in the middle
                else {
                    // linear search
                    Node * currentNode = this->head;

                    while (currentNode != nullptr && currentNode->value < value) {
                        currentNode = currentNode->next;
                    }

                    // connect the node to the list
                    newNode->next = currentNode;
                    newNode->previous = currentNode->previous;
                    currentNode->previous->next = newNode;
                    currentNode->previous = newNode;
                }

                this->length++;
            };

            /**
             * linear search
             * 
             * @param {*} value 
             * @returns boolean
             */
            bool find(type value) {
                return this->searchNode(value) != nullptr;
            };

            /**
             * finds and deletes a value in the list
             * 
             * @param {*} value 
             * @returns boolean
             */
            bool deleteValue(type value) {
                // linear search
                Node * currentNode = this->searchNode(value);
                return this->deleteNode(currentNode);
            };

            /**
             * 
             * @returns boolean
             */
            bool deleteHead() {
                if (this->head == nullptr) {
                    return false;
                }

                Node * temp = this->head;

                if (this->head == this->tail) {
                    this->tail = nullptr;
                    this->head = nullptr;
                }
                else {
                    this->head = this->head->next;
                    this->head->previous = nullptr;
                }

                this->length--;

                // delete detached node
                delete temp;

                return true;
            };

            /**
             * 
             * @returns boolean
             */
            bool deleteTail() {
                if (this->tail == nullptr) {
                    return false;
                }

                Node * temp = this->tail;

                // connect the previous node to the next node
                if (this->tail == this->head) {
                    this->head = nullptr;
                    this->tail = nullptr;
                }
                else {
                    this->tail = this->tail->previous;
                    this->tail->next = nullptr;
                }

                this->length--;

                // delete detached node
                delete temp;

                return true;
            };

            void clear() {
                // manual memory management
                while (this->head != nullptr) {
                    Node * currentNode = this->head;
                    this->head = this->head->next;
                    delete currentNode;
                }

                this->head = nullptr;
                this->tail = nullptr;
                this->length = 0;
            };

            type getHead() {
                return this->head->value;
            };

            type getTail() {
                return this->tail->value;
            };
        private:
            class Node {
                public:
                    type value;
                    Node * next;
                    Node * previous;

                    Node(type value) {
                        this->value = value;
                        this->next = nullptr;
                        this->previous = nullptr;
                    };
                    Node(type value, Node * nextNode, Node * previousNode) {
                        this->value = value;
                        this->next = nextNode;
                        this->previous = previousNode;
                    };
                    ~Node() {};
            };

            Node * head;
            Node * tail;
            size_t length;

            /**
             * linear search
             * 
             * @param {*} value 
             * @returns 
             */
            Node * searchNode(type value) {
                Node * currentNode = this->head;

                while (currentNode != nullptr && currentNode->value != value) {
                    currentNode = currentNode->next;
                }

                return currentNode;
            };

            /**
             * 
             * @param {Node} node 
             * @returns boolean
             */
            bool deleteNode(Node * node) {
                if (node == nullptr) {
                    return false;
                }

                // connect the previous node to the next node
                if (node == this->head) {
                    this->head = node->next;
                }
                else {
                    node->previous->next = node->next;
                }

                // connect the next node to the previous node
                if (node == this->tail) {
                    this->tail = node->previous;
                }
                else {
                    node->next->previous = node->previous;
                }

                this->length--;

                // delete detached node
                delete node;

                return true;
            };
    };
}

#endif
