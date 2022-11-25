#include "DoublyLinkList.h"

int Node::ALLOCATIONS = 0;

DoublyLinkedList::DoublyLinkedList() {
  _head = 0; 
  _size = 0;
}

DoublyLinkedList::~DoublyLinkedList() {
  // Release all memory
  while (_head != 0) {
    Node* temp = _head->next;
    delete _head;
    _head = temp;
  }
}

void DoublyLinkedList::Add(int data) {
  // Empty list
  if (_head == 0) {
    _head = new Node(data, 0, 0);
    _size++;
    return;
  }

  Node* node = _head;
  while (node->next != 0) {
    node = node->next;
  }

  Node* newNode = new Node(data, 0, node);
  node->next = newNode;
  _size++;
}

void DoublyLinkedList::Remove(int index) {
  if (index < 0 && (index + 1) > _size) {
    throw "Attempting to remove object out of bounds.";
  }

  Node* node = _head;
  int nodeIndex = 0;
  while (nodeIndex < index) {
    nodeIndex++;
    node = node->next;
  }

  if (node->next != 0) {
    node->next->previous = node->previous;
  }
  if (node->previous != 0) {
    node->previous->next = node->next;
  }
  
  //Move the head if removing firs item.
  if (index == 0)
  {
    _head = node->next;
  }

  delete node;
  _size--;
}

int& DoublyLinkedList::operator[](int index) {
  if (index < 0 && (index+1) > _size) {
    throw "Attempting to access object out of bounds.";
  }
  
  Node* node = _head;
  int nodeIndex = 0;
  while (nodeIndex < index) {
    nodeIndex++;
    node = node->next;
  }

  return node->data;
}