#ifndef SJTU_PRIORITY_QUEUE_HPP
#define SJTU_PRIORITY_QUEUE_HPP

#include <cstddef>
#include <functional>
#include <variant>

#include "exceptions.hpp"

namespace sjtu {
  /**
   * @brief a container like std::priority_queue which is a heap internal.
   * **Exception Safety**: The `Compare` operation might throw exceptions for certain data.
   * In such cases, any ongoing operation should be terminated, and the priority queue should be restored to its original state before the operation began.
   */
  template<typename T, class Compare = std::less<T> >
  class priority_queue {
  private:
    struct Node {
      T data;
      Node *left;
      Node *right;

      Node(const T &value) : data(value), left(nullptr), right(nullptr) {
      }
    };

    Node *root;
    size_t num;
    Compare cmp;

    Node *merge(Node *h1, Node *h2) {
      if (!h1) return h2;
      if (!h2) return h1;
      if (cmp(h1->data, h2->data)) {
        std::swap(h1, h2);
      }
      h1->right = merge(h1->right, h2);
      std::swap(h1->left, h1->right);
      return h1;
    }

    void clear(Node *current) {
      if (!current) return;
      clear(current->left);
      clear(current->right);
      delete current;
    }

    Node *copy(Node *otherRoot) {
      if (!otherRoot) return nullptr;
      Node *newNode = new Node(otherRoot->data);
      newNode->left = copy(otherRoot->left);
      newNode->right = copy(otherRoot->right);
      return newNode;
    }

  public:
    /**
     * @brief default constructor
     */
    priority_queue() : root(nullptr), num(0) {
    }

    /**
     * @brief copy constructor
     * @param other the priority_queue to be copied
     */
    priority_queue(const priority_queue &other) : num(other.num), cmp(other.cmp) {
      root = copy(other.root);
    }


    /**
     * @brief deconstructor
     */
    ~priority_queue() {
      clear(root);
    }

    /**
     * @brief Assignment operator
     * @param other the priority_queue to be assigned from
     * @return a reference to this priority_queue after assignment
     */
    priority_queue &operator=(const priority_queue &other) {
      if (this == &other) return *this;
      clear(root);
      root = copy(other.root);
      num = other.num;
      cmp = other.cmp;
      return *this;
    }

    /**
     * @brief get the top element of the priority queue.
     * @return a reference of the top element.
     * @throws container_is_empty if empty() returns true
     */
    const T &top() const {
      if (empty()) {
        throw container_is_empty();
      }
      return root->data;
    }

    /**
     * @brief push new element to the priority queue.
     * @param e the element to be pushed
     */
    void push(const T &e) {
      Node *newNode = new Node(e);
      try {
        root = merge(root, newNode);
        ++num;
      } catch (...) {
        delete newNode;
        throw runtime_error();
      }
    }

    /**
     * @brief delete the top element from the priority queue.
     * @throws container_is_empty if empty() returns true
     */
    void pop() {
      if (empty()) {
        throw container_is_empty();
      }
      Node *temp = root;
      root = merge(root->left, root->right);
      delete temp;
      --num;
    }

    /**
     * @brief return the number of elements in the priority queue.
     * @return the number of elements.
     */
    size_t size() const {
      return num;
    }

    /**
     * @brief check if the container is empty.
     * @return true if it is empty, false otherwise.
     */
    bool empty() const {
      return num == 0;
    }

    /**
     * @brief merge another priority_queue into this one.
     * The other priority_queue will be cleared after merging.
     * The complexity is at most O(logn).
     * @param other the priority_queue to be merged.
     */
    void merge(priority_queue &other) {
      root = merge(root, other.root);
      num += other.num;
      other.root = nullptr;
      other.num = 0;
    }
  };
}

#endif
