#include "../src/unitTest.h"
#include "../src/data structures/DoublyLinkedList.h"

void doublyLinkedListTests() {
    tvnj::DoublyLinkedList<int> list;
    list.insertTail(10);
    list.insertTail(20);
    list.insertHead(5);
    list.sortedInsert(15);
    UNIT_TEST(list.toString(), "5 10 15 20");
    UNIT_TEST(list.getHead(), 5);
    UNIT_TEST(list.getTail(), 20);
    UNIT_TEST(list.find(100), false);
    UNIT_TEST(list.find(10), true);
    list.deleteValue(10);
    UNIT_TEST(list.find(10), false);
    UNIT_TEST(list.toString(), "5 15 20");
    list.deleteHead();
    UNIT_TEST(list.toString(), "15 20");
    list.deleteTail();
    UNIT_TEST(list.toString(), "15");
    list.clear();
    UNIT_TEST(list.toString(), "");
    UNIT_TEST(list.size(), 0);

    list.insertTail(10);
    list.insertTail(20);
    list.insertHead(5);
    list.sortedInsert(15);
    tvnj::DoublyLinkedList<int> list2(list);
    UNIT_TEST(list2.toString(), "5 10 15 20");
    list.clear();
    UNIT_TEST(list2.toString(), "5 10 15 20");
}
