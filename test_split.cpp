/*
CSCI 104: Homework 1 Problem 1

Use this file to test your split.cpp file.

Create linked lists and split them with your split() function.

You can compile this file like this:
g++ split.cpp test_split.cpp -o test_split
*/
#include <iostream>
#include "split.h"

Node* createList(int minVal, int maxVal) {
    Node* head = nullptr;
    Node* tail = nullptr;
    for (int v = minVal; v <= maxVal; v++) {
        Node* node = new Node{v, nullptr};
        if (head == nullptr) {
            head = node;
        } else {
            tail->next = node;
        }
        tail = node;
    }
    return head;
}

void printList(Node* head) {
    Node* curr = head;
    while (curr != nullptr) {
        std::cout << curr->value;
        if (curr->next != nullptr) {
            std::cout << " -> ";
        }
        curr = curr->next;
    }
    std::cout << std::endl;
}
void deleteList(Node*& head) {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

int main(int argc, char* argv[])
{
  Node * testList = createList(1,9);
  Node * odds = nullptr;
  Node * evens = nullptr;
  printList(testList);
  split(testList, odds, evens);

  printList(odds);
  printList(evens);
  deleteList(odds);
  deleteList(evens);
}
