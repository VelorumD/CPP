#include <iostream>
#include <string>
#include "DoublyLinkList.h"

// HELPERS
void printList(DoublyLinkedList& list) {
  int size = list.Size();
  for (int i = 0; i < size; ++i) {
    std::cout << list[i] << " -> ";
  }
  std::cout << "null" << std::endl;
}

void addNItems(DoublyLinkedList* list, int N) {
  for (int i = 0; i < N; ++i) {
    list->Add(list->Size() + 1);
  }
}

DoublyLinkedList* createListWithNItems(int N) {
  DoublyLinkedList* list = new DoublyLinkedList();
  addNItems(list, N);
  return list;
}

void removeNItems(DoublyLinkedList* list, int N, int indices[]) {
  for (int i = 0; i < N; ++i) {
    list->Remove(indices[i]);
  }
}

void expectListSize(DoublyLinkedList* list, int expectedSize) {
  if (list->Size() != expectedSize) {
    std::string errorMsg = "Expected size " + std::to_string(expectedSize) + ", but had " + std::to_string(list->Size());
    printList(*list);
    delete list;
    throw errorMsg;
  }
}

// TESTS
void runTest(void (*test)(), std::string testName) {
  Node::ALLOCATIONS = 0;
  try {
    test();
    std::cout << "PASS " + testName;
  }
  catch (std::string errorMsg) {
    std::cout << errorMsg << std::endl;
    std::cout << "FAIL " + testName;
  }

  std::cout << " IN MEMORY: " << Node::ALLOCATIONS << std::endl;
}

void test_Add_1_Remove_1_should_have_size_0() {
  DoublyLinkedList* list = createListWithNItems(1);
  int indices[] = { 0 };
  removeNItems(list, 1, indices);
  expectListSize(list, 0);
  delete list;
}

void test_Add_1_Remove_1_Add_3_should_have_size_3() {
  DoublyLinkedList* list = createListWithNItems(1);
  int indices[] = { 0 };
  removeNItems(list, 1, indices);
  addNItems(list, 3);
  expectListSize(list, 3);
  delete list;
}

void test_Add_2_Remove_last_should_have_size_1() {
  DoublyLinkedList* list = createListWithNItems(2);
  list->Remove(1);
  expectListSize(list, 1);
  delete list;
}

void test_Add_2_remove_first_Add_5_should_have_size_6() {
  DoublyLinkedList* list = createListWithNItems(2);
  list->Remove(0);
  addNItems(list, 5);
  expectListSize(list, 6);
  delete list;
}

void test_Add_10_items_To_List() {
  DoublyLinkedList* list = createListWithNItems(10);
  expectListSize(list, 10);
  delete list;
}

void test_Remove_remove_2_items_should_have_8_left() {
  DoublyLinkedList* list = createListWithNItems(10);
  int indices[] = { 3, 7 };
  removeNItems(list, 2, indices);
  expectListSize(list, 8);

  delete list;
}

// MAIN
int main()
{
  runTest(test_Add_1_Remove_1_should_have_size_0, "Add 1 Remove 1, should have size 0");
  runTest(test_Add_1_Remove_1_Add_3_should_have_size_3, "Add 1 Remove 1 Add 3, should have size 3");
  runTest(test_Add_2_Remove_last_should_have_size_1, "Add 2 Remove last, should have size 1");
  runTest(test_Add_2_remove_first_Add_5_should_have_size_6, "Add 2 Remove first Add 5, should have size 6");
  runTest(test_Add_10_items_To_List, "Add 10 itesm to List");
  runTest(test_Remove_remove_2_items_should_have_8_left, "Remove 2 items from list, should size 8");
}