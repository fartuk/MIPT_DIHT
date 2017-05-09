#pragma once

#include <atomic>
#include <iostream>
#include <thread>

///////////////////////////////////////////////////////////////////////

template <typename T>
class LockFreeStack {
  struct Node {
    T element;
        // to be continued
    Node* next;
  };

 public:
  explicit LockFreeStack() {}

  ~LockFreeStack() {  
    Node* curr_top = top_.load();
    while (curr_top) {
      Node* tmp = curr_top->next;
      delete curr_top;
      curr_top = tmp;
    }
    Node* curr_rub = rub_.load();
    while (curr_rub) {
      Node* tmp = curr_rub->next;
      delete curr_rub;
      curr_rub = tmp;
    }
        // not implemented
  }

  void Push(T element/* element */) {
    Node* new_node = new Node;
    new_node->element = element;
    Node* curr_top = top_.load();    
    new_node->next = curr_top;
    while (!top_.compare_exchange_strong(curr_top, new_node)) {
      new_node->next = curr_top;
    }
  }

  bool Pop(T& element/* element */) {
    // not implemented
    Node* curr_top = top_.load();
    while (true) {
      if (!curr_top) {
        return false;
      }
      if (top_.compare_exchange_strong(curr_top, curr_top->next)) {
        element = curr_top->element;
        Node* curr_rub = rub_.load();
        curr_top->next = curr_rub;
        while (!rub_.compare_exchange_strong(curr_rub, curr_top)) {
          curr_top->next = curr_rub;
        }
        return true;
      }
    }
  }

 private:
  std::atomic<Node*> rub_{nullptr};
  std::atomic<Node*> top_{nullptr};
};

///////////////////////////////////////////////////////////////////////

template <typename T>
using ConcurrentStack = LockFreeStack<T>;

///////////////////////////////////////////////////////////////////////
/*
main() {
  LockFreeStack<int> s;
  s.Push(5);
  s.Push(7);
  int tmp;
  s.Pop(tmp);
  std::cout << tmp;
}*/
