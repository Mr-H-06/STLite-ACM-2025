/**
 * implement a container like std::map
 */
#ifndef SJTU_MAP_HPP
#define SJTU_MAP_HPP

// only for std::less<T>
#include <functional>
#include <cstddef>
#include "utility.hpp"
#include "exceptions.hpp"

namespace sjtu {
  template<
    class Key,
    class T,
    class Compare = std::less<Key> >
  class map {
  public:
    /**
     * the internal type of data.
     * it should have a default constructor, a copy constructor.
     * You can use sjtu::map as value_type by typedef.
     */
    typedef pair<const Key, T> value_type;

    /**
     * see BidirectionalIterator at CppReference for help.
     *
     * if there is anything wrong throw invalid_iterator.
     *     like it = map.begin(); --it;
     *       or it = map.end(); ++end();
     */

    enum Color { RED, BLACK };

    struct Node {
      Color color;
      Node *parent;
      Node *left;
      Node *right;

      value_type data;

      Node() = default;

      Node(Color color_, const value_type &val, Node *parent_ = nullptr, Node *left_ = nullptr,
           Node *right_ = nullptr) : data(val), color(color_), parent(parent_), left(left_), right(right_) {
      }
    };

    class const_iterator;

    class iterator {
    private:
      /**
       * TODO add data members
       *   just add whatever you want.
       */

      Node *ptr;
      map *container;
      friend class const_iterator;

    public:
      iterator(Node *ptr_ = nullptr, map *container_ = nullptr) : ptr(ptr_), container(container_) {
        // TODO
      }

      iterator(const iterator &other) : ptr(other.ptr), container(other.container) {
        // TODO
      }

      Node *getptr() {
        return ptr;
      }

      map *getcontainer() {
        return container;
      }

      /**
       * TODO iter++
       */
      iterator operator++(int) {
        iterator tmp = *this;
        ++*this;
        return tmp;
      }

      /**
       * TODO ++iter
       */
      iterator &operator++() {
        if (!ptr) throw invalid_iterator();
        if (ptr->right) {
          ptr = ptr->right;
          while (ptr->left) {
            ptr = ptr->left;
          }
        } else {
          Node *p = ptr->parent;
          while (p && ptr == p->right) {
            ptr = p;
            p = p->parent;
          }
          ptr = p;
        }
        return *this;
      }

      /**
       * TODO iter--
       */
      iterator operator--(int) {
        iterator tmp = *this;
        --*this;
        return tmp;
      }

      /**
       * TODO --iter
       */
      iterator &operator--() {
        if (ptr == container->begin().ptr) throw invalid_iterator();
        if (!ptr) {
          ptr = container->tail;
        } else if (ptr->left) {
          ptr = ptr->left;
          while (ptr->right) {
            ptr = ptr->right;
          }
        } else {
          Node *p = ptr->parent;
          while (p && ptr == p->left) {
            ptr = p;
            p = p->parent;
          }
          ptr = p;
        }
        return *this;
      }

      /**
       * a operator to check whether two iterators are same (pointing to the same memory).
       */
      value_type &operator*() const {
        if (!ptr) throw invalid_iterator();
        return ptr->data;
      }

      bool operator==(const iterator &rhs) const {
        return ptr == rhs.ptr && container == rhs.container;
      }

      bool operator==(const const_iterator &rhs) const {
        return ptr == rhs.ptr && container == rhs.container;
      }

      /**
       * some other operator for iterator.
       */
      bool operator!=(const iterator &rhs) const {
        return !(*this == rhs);
      }

      bool operator!=(const const_iterator &rhs) const {
        return !(*this == rhs);
      }

      /**
       * for the support of it->first.
       * See <http://kelvinh.github.io/blog/2013/11/20/overloading-of-member-access-operator-dash-greater-than-symbol-in-cpp/> for help.
       */
      value_type *operator->() const
        noexcept {
        return &ptr->data;
      }
    };

    class const_iterator {
      // it should has similar member method as iterator.
      //  and it should be able to construct from an iterator.
    private:
      // data members.
      const Node *ptr;
      const map *container;
      friend class iterator;

    public:
      const_iterator(const Node *ptr_ = nullptr, const map *container_ = nullptr) : ptr(ptr_), container(container_) {
        // TODO
      }

      const_iterator(const const_iterator &other): ptr(other.ptr), container(other.container) {
        // TODO
      }

      const_iterator(const iterator &other) : ptr(other.ptr), container(other.container) {
        // TODO
      }

      // And other methods in iterator.
      // And other methods in iterator.
      // And other methods in iterator.
      const_iterator operator++(int) {
        const_iterator tmp = *this;
        ++*this;
        return tmp;
      }

      const_iterator &operator++() {
        if (!ptr) throw invalid_iterator();
        if (ptr->right) {
          ptr = ptr->right;
          while (ptr->left) {
            ptr = ptr->left;
          }
        } else {
          const Node *p = ptr->parent;
          while (p && ptr == p->right) {
            ptr = p;
            p = p->parent;
          }
          ptr = p;
        }
        return *this;
      }

      const_iterator operator--(int) {
        const_iterator tmp = *this;
        --*this;
        return tmp;
      }

      const_iterator &operator--() {
        if (ptr == container->cbegin().ptr) throw invalid_iterator();
        if (!ptr) {
          ptr = container->tail;
        } else if (ptr->left) {
          ptr = ptr->left;
          while (ptr->right) {
            ptr = ptr->right;
          }
        } else {
          const Node *p = ptr->parent;
          while (p && ptr == p->left) {
            ptr = p;
            p = p->parent;
          }
          ptr = p;
        }
        return *this;
      }

      const value_type &operator*() const {
        if (!ptr) throw invalid_iterator();
        return ptr->data;
      }

      bool operator==(const const_iterator &rhs) const {
        return ptr == rhs.ptr && container == rhs.container;
      }

      bool operator==(const iterator &rhs) const {
        return ptr == rhs.ptr && container == rhs.container;
      }

      bool operator!=(const const_iterator &rhs) const {
        return !(*this == rhs);
      }

      bool operator!=(const iterator &rhs) const {
        return !(*this == rhs);
      }

      const value_type *operator->() const noexcept {
        return &ptr->data;
      }
    };

    /**
     * TODO two constructors
     */
    map() : root(nullptr), tail(nullptr), size_(0) {
    }

    map(const map &other) : root(nullptr), size_(0) {
      for (const_iterator it = other.cbegin(); it != other.cend(); ++it) {
        insert(*it);
      }
    }

    /**
     * TODO assignment operator
     */
    map &operator=(const map &other) {
      if (this != &other) {
        clear();
        for (const_iterator it = other.cbegin(); it != other.cend(); ++it) {
          insert(*it);
        }
      }
      return *this;
    }

    /**
     * TODO Destructors
     */
    ~map() {
      clear();
    }

    /**
     * TODO
     * access specified element with bounds checking
     * Returns a reference to the mapped value of the element with key equivalent to key.
     * If no such element exists, an exception of type `index_out_of_bound'
     */
    T &at(const Key &key) {
      iterator it = find(key);
      if (it == end()) throw index_out_of_bound();
      return it->second;
    }

    const T &at(const Key &key) const {
      const_iterator it = find(key);
      if (it == cend()) throw index_out_of_bound();
      return it->second;
    }

    /**
     * TODO
     * access specified element
     * Returns a reference to the value that is mapped to a key equivalent to key,
     *   performing an insertion if such key does not already exist.
     */
    T &operator[](const Key &key) {
      iterator it = find(key);
      if (it == end()) {
        return insert(value_type(key, T())).first->second;
      }
      return it->second;
    }

    /**
     * behave like at() throw index_out_of_bound if such key does not exist.
     */
    const T &operator[](const Key &key) const {
      const_iterator it = find(key);
      if (it == cend()) throw index_out_of_bound();
      return it->second;
    }

    /**
     * return a iterator to the beginning
     */
    iterator begin() {
      Node *p = root;
      while (p && p->left) {
        p = p->left;
      }
      return iterator(p, this);
    }

    const_iterator cbegin() const {
      const Node *p = root;
      while (p && p->left) {
        p = p->left;
      }
      return const_iterator(p, this);
    }

    /**
     * return a iterator to the end
     * in fact, it returns past-the-end.
     */
    iterator end() {
      return iterator(nullptr, this);
    }

    const_iterator cend() const {
      return const_iterator(nullptr, this);
    }

    /**
     * checks whether the container is empty
     * return true if empty, otherwise false.
     */
    bool empty() const {
      return size_ == 0;
    }

    /**
     * returns the number of elements.
     */
    size_t size() const {
      return size_;
    }

    /**
     * clears the contents
     */
    void clear() {
      clearTree(root);
      root = nullptr;
      tail = nullptr;
      size_ = 0;
    }

    /**
     * insert an element.
     * return a pair, the first of the pair is
     *   the iterator to the new element (or the element that prevented the insertion),
     *   the second one is true if insert successfully, or false.
     */
    pair<iterator, bool> insert(const value_type &value) {
      return insertToTree(value, nullptr, root);
    }

    /**
     * erase the element at pos.
     *
     * throw if pos pointed to a bad element (pos == this->end() || pos points an element out of this)
     */
    void erase(iterator pos) {
      if (!pos.getptr() || pos.getcontainer() != this) throw invalid_iterator();
      if (pos.getptr() == tail) {
        tail = tail->parent;
        remove(pos->first, root);
      } else {
        remove(pos->first, root);
      }
    }

    /**
     * Returns the number of elements with key
     *   that compares equivalent to the specified argument,
     *   which is either 1 or 0
     *     since this container does not allow duplicates.
     * The default method of check the equivalence is !(a < b || b > a)
     */
    size_t count(const Key &key) const {
      return find(key) != cend() ? 1 : 0;
    }

    /**
     * Finds an element with key equivalent to key.
     * key value of the element to search for.
     * Iterator to an element with key equivalent to key.
     *   If no such element is found, past-the-end (see end()) iterator is returned.
     */
    iterator find(const Key &key) {
      Node *current = root;
      while (current) {
        if (Compare()(key, current->data.first)) {
          current = current->left;
        } else if (Compare()(current->data.first, key)) {
          current = current->right;
        } else {
          return iterator(current, this);
        }
      }
      return end();
    }

    const_iterator find(const Key &key) const {
      const Node *current = root;
      while (current != nullptr) {
        if (Compare()(key, current->data.first)) {
          current = current->left;
        } else if (Compare()(current->data.first, key)) {
          current = current->right;
        } else {
          return const_iterator(current, this);
        }
      }
      return cend();
    }

  private:
    Node *root;
    Node *tail;
    size_t size_;

    void clearTree(Node *node) {
      if (node) {
        clearTree(node->left);
        clearTree(node->right);
        delete node;
      }
    }

    pair<iterator, bool> insertToTree(const value_type &value, Node *parent, Node *current) {
      if (!current) {
        current = new Node(RED, value, parent);
        if (parent) {
          if (Compare()(value.first, parent->data.first)) {
            parent->left = current;
          } else {
            parent->right = current;
            if (parent == tail) {
              tail = current;
            }
          }
        } else {
          root = current;
          tail = current;
        }
        insertRebalance(current);
        ++size_;
        return {iterator(current, this), true};
      } else if (Compare()(value.first, current->data.first)) {
        return insertToTree(value, current, current->left);
      } else if (Compare()(current->data.first, value.first)) {
        return insertToTree(value, current, current->right);
      } else {
        return {iterator(current, this), false};
      }
    }

    void LL(Node *current) {
      Node *tmp = current->left;
      current->left = tmp->right;
      if (tmp->right) tmp->right->parent = current;
      tmp->right = current;
      tmp->parent = current->parent;
      if (current->parent) {
        if (current->parent->left == current) {
          current->parent->left = tmp;
        } else {
          current->parent->right = tmp;
        }
      } else {
        root = tmp;
      }
      current->parent = tmp;
    }

    void RR(Node *current) {
      Node *tmp = current->right;
      current->right = tmp->left;
      if (tmp->left) tmp->left->parent = current;
      tmp->left = current;
      tmp->parent = current->parent;
      if (current->parent) {
        if (current->parent->right == current) {
          current->parent->right = tmp;
        } else {
          current->parent->left = tmp;
        }
      } else {
        root = tmp;
      }
      current->parent = tmp;
    }

    void LR(Node *current) {
      RR(current->left);
      LL(current);
    }

    void RL(Node *current) {
      LL(current->right);
      RR(current);
    }

    void insertRebalance(Node *current) {
      while (current != root) {
        Node *parent = current->parent;
        if (parent->color == BLACK) break;
        Node *grandparent = parent->parent;
        Node *uncle = parent == grandparent->left ? grandparent->right : grandparent->left;
        if (uncle && uncle->color == RED) {
          parent->color = BLACK;
          uncle->color = BLACK;
          grandparent->color = RED;
          current = grandparent;
        } else {
          if (parent == grandparent->left) {
            if (current == parent->left) {
              parent->color = BLACK;
              grandparent->color = RED;
              LL(grandparent);
            } else {
              current->color = BLACK;
              grandparent->color = RED;
              LR(grandparent);
            }
          } else {
            if (current == parent->left) {
              current->color = BLACK;
              grandparent->color = RED;
              RL(grandparent);
            } else {
              parent->color = BLACK;
              grandparent->color = RED;
              RR(grandparent);
            }
          }
          break;
        }
      }
      root->color = BLACK;
    }

    void removeReblance(Node *current) {
      while (current != root) {
        Node *parent = current->parent;
        Node *brother = current == parent->left ? parent->right : parent->left;

        if (brother->color == RED) {
          brother->color = BLACK;
          parent->color = RED;
          if (brother == parent->left)
            LL(parent);
          else
            RR(parent);
        } else {
          bool left_is_red = brother->left && brother->left->color == RED;
          bool right_is_red = brother->right && brother->right->color == RED;
          if (!left_is_red && !right_is_red) {
            if (parent->color == RED) {
              brother->color = RED;
              parent->color = BLACK;
              break;
            } else {
              brother->color = RED;
              current = parent;
            }
          } else if (brother == parent->right) {
            if (left_is_red) {
              brother->left->color = BLACK;
              brother->color = RED;
              LL(brother);
            } else {
              brother->color = parent->color;
              parent->color = BLACK;
              brother->right->color = BLACK;
              RR(parent);
              break;
            }
          } else {
            if (right_is_red) {
              brother->right->color = BLACK;
              brother->color = RED;
              RR(brother);
            } else {
              brother->color = parent->color;
              parent->color = BLACK;
              brother->left->color = BLACK;
              LL(parent);
              break;
            }
          }
        }
      }
      root->color = BLACK;
    }

    void remove(const Key &value, Node *current) {
      if (!current) return;
      if (Compare()(value, current->data.first)) {
        remove(value, current->left);
      } else if (Compare()(current->data.first, value)) {
        remove(value, current->right);
      } else {
        if (current->left && current->right) {
          Node *tmp = current->right;
          while (tmp->left) tmp = tmp->left;
          Node *n = new Node(tmp->color, tmp->data, tmp->parent, tmp->left, tmp->right);
          if (tmp->parent->left == tmp) {
            tmp->parent->left = n;
          } else {
            tmp->parent->right = n;
          }
          if (tmp->left) {
            tmp->left->parent = n;
          }
          if (tmp->right) {
            tmp->right->parent = n;
          }

          tmp->left = current->left;
          tmp->right = current->right;
          tmp->parent = current->parent;
          tmp->color = current->color;
          if (root == current) {
            root = tmp;
          } else {
            if (current == current->parent->left) {
              current->parent->left = tmp;
            } else {
              current->parent->right = tmp;
            }
          }
          if (current->left) {
            current->left->parent = tmp;
          }
          if (current->right) {
            current->right->parent = tmp;
          }

          delete current;
          current = tmp;

          remove(tmp->data.first, current->right);
        } else {
          Node *tmp = nullptr;
          if (current->left) tmp = current->left;
          if (current->right) tmp = current->right;
          if (current->color == BLACK) {
            if (tmp && tmp->color == RED) {
              tmp->color = BLACK;
            } else {
              removeReblance(current);
            }
          }
          if (tmp) {
            tmp->parent = current->parent;
          }
          if (current->parent) {
            if (current->parent->left == current) {
              current->parent->left = tmp;
            } else {
              current->parent->right = tmp;
            }
          } else {
            root = tmp;
          }
          delete current;
          --size_;
        }
      }
    }
  };
}

#endif