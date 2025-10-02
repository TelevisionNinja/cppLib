#ifndef MINBINARYHEAP_H
#define MINBINARYHEAP_H

#include <vector>
#include <string>
#include "../stringUtils.h"

namespace tvnj {
    /**
     * @brief 0 indexed binary min heap
     * 
     * @tparam type 
     */
    template<typename type>
    class MinBinaryHeap {
        public:
            MinBinaryHeap() {};
            MinBinaryHeap(std::vector<type> array) {
                this->heap = array;
                tvnj::MinBinaryHeap<type>::buildMinBinaryHeap(this->heap);
            };
            MinBinaryHeap(const tvnj::MinBinaryHeap<type> & heap) {
                this->heap = heap.heap;
            };
            ~MinBinaryHeap() {};

            void insert(type value) {
                // insert
                this->heap.push_back(value);

                size_t child = this->heap.size() - 1;

                // bottom up
                while (child > 0) {
                    size_t parent = (child - 1) / 2;

                    if (this->heap[parent] > value) {
                        type temp = this->heap[parent];
                        this->heap[parent] = this->heap[child];
                        this->heap[child] = temp;

                        child = parent;
                    }
                    else {
                        break;
                    }
                }
            };
            bool remove(type & value) {
                if (this->isEmpty()) {
                    return false;
                }

                // return the value
                value = this->heap[0];

                // swap the last value to the root
                this->heap[0] = this->heap[this->heap.size() - 1];
                this->heap.pop_back();

                tvnj::MinBinaryHeap<type>::minHeapify(this->heap, 0);

                return true;
            };
            bool isEmpty() const {
                return this->heap.size() == 0;
            };
            size_t size() const {
                return this->heap.size();
            };

            std::string toString() const {
                return "[" + tvnj::join(this->heap, ", ") + "]";
            };

            static void minHeapify(std::vector<type> & array, size_t index) {
                size_t largest = index;
                size_t parent = index;
                size_t n = array.size();

                // shuffle small values down
                while (true) {
                    size_t left = 2 * parent + 1;
                    size_t right = 2 * parent + 2;

                    if (left < n && array[left] < array[largest]) {
                        largest = left;
                    }

                    if (right < n && array[right] < array[largest]) {
                        largest = right;
                    }

                    if (largest != parent) {
                        type temp = array[largest];
                        array[largest] = array[parent];
                        array[parent] = temp;

                        parent = largest;
                    }
                    else {
                        break;
                    }
                }
            };

            static void buildMinBinaryHeap(std::vector<type> & array) {
                size_t i = array.size() / 2;
                while (i > 0) {
                    i--;
                    tvnj::MinBinaryHeap<type>::minHeapify(array, i);
                }
            };
        private:
            std::vector<type> heap;
    };
}

#endif
