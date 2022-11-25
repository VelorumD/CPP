#pragma once

#include <iostream>

struct Node {
  static int ALLOCATIONS;

  Node(int data, Node* next, Node* previous) {
    this->data = data;
    this->next = next;
    this->previous = previous;

    ALLOCATIONS++;
  }

  ~Node() {
    ALLOCATIONS--;
  }

  int data;

  Node* next;
  Node* previous;
};

class DoublyLinkedList {
  public:
    DoublyLinkedList();
    ~DoublyLinkedList();

    int Size() const { return _size; }

    //Add at end of list.
    void Add(int data);
    void Remove(int index);
    void Reverse();

    int& operator[](int index);

  private:
    Node* _head;
    int _size;
};