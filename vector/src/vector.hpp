#ifndef SJTU_VECTOR_HPP
#define SJTU_VECTOR_HPP

#include "exceptions.hpp"

#include <climits>
#include <cstddef>

namespace sjtu
{
/**
 * a data container like std::vector
 * store data in a successive memory and support random access.
 */
template<typename T>
class vector {
public:
    /**
     * TODO
     * a type for actions of the elements of a vector, and you should write
     *   a class named const_iterator with same interfaces.
     */
    /**
     * you can see RandomAccessIterator at CppReference for help.
     */
    class const_iterator;
    class iterator {
    // The following code is written for the C++ type_traits library.
    // Type traits is a C++ feature for describing certain properties of a type.
    // For instance, for an iterator, iterator::value_type is the type that the
    // iterator points to.
    // STL algorithms and containers may use these type_traits (e.g. the following
    // typedef) to work properly. In particular, without the following code,
    // @code{std::sort(iter, iter1);} would not compile.
    // See these websites for more information:
    // https://en.cppreference.com/w/cpp/header/type_traits
    // About value_type: https://blog.csdn.net/u014299153/article/details/72419713
    // About iterator_category: https://en.cppreference.com/w/cpp/iterator
    public:
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = T*;
        using reference = T&;
        using iterator_category = std::output_iterator_tag;

    private:
        /**
         * TODO add data members
         *   just add whatever you want.
         */
        T* ptr;
        vector<T>* vector_;

    public:
        iterator(T* p = nullptr, vector<T>* v = nullptr) : ptr(p), vector_(v) {}

        /**
         * return a new iterator which pointer n-next elements
         * as well as operator-
         */
        iterator operator+(const int &n) const {
            //TODO
            return iterator(ptr + n, vector_);
        }
        iterator operator-(const int &n) const {
            //TODO
            return iterator(ptr - n, vector_);
        }
        // return the distance between two iterators,
        // if these two iterators point to different vectors, throw invaild_iterator.
        int operator-(const iterator &rhs) const {
            //TODO
            if (vector_ != rhs.vector_) {
                throw sjtu::invalid_iterator();
            }
            return ptr - rhs.ptr;
        }
        iterator& operator+=(const int &n) {
            //TODO
            ptr += n;
            return *this;
        }
        iterator& operator-=(const int &n) {
            //TODO
            ptr -= n;
            return *this;
        }
        /**
         * TODO iter++
         */
        iterator operator++(int) {
            iterator temp = *this;
            ++ptr;
            return temp;
        }
        /**
         * TODO ++iter
         */
        iterator& operator++() {
            ++ptr;
            return *this;
        }
        /**
         * TODO iter--
         */
        iterator operator--(int) {
            iterator temp = *this;
            --ptr;
            return temp;
        }
        /**
         * TODO --iter
         */
        iterator& operator--() {
            --ptr;
            return *this;
        }
        /**
         * TODO *it
         */
        T& operator*() const {
            return *ptr;
        }
        /**
         * a operator to check whether two iterators are same (pointing to the same memory address).
         */
        bool operator==(const iterator &rhs) const {
            return ptr == rhs.ptr;
        }
        bool operator==(const const_iterator &rhs) const {
            return ptr == rhs.getPtr();
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
    };
    /**
     * TODO
     * has same function as iterator, just for a const object.
     */
    class const_iterator {
    public:
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = T*;
        using reference = T&;
        using iterator_category = std::output_iterator_tag;

    private:
        /*TODO*/
        const T* ptr;
        const vector<T>* vec;

    public:
        const_iterator(const T* p = nullptr, const vector<T>* v = nullptr) : ptr(p), vec(v) {}

        const T* getPtr() const {
            return ptr;
        }

        const_iterator operator+(const int &n) const {
            return const_iterator(ptr + n, vec);
        }

        const_iterator operator-(const int &n) const {
            return const_iterator(ptr - n, vec);
        }

        int operator-(const const_iterator &rhs) const {
            if (vec != rhs.vec) {
                throw sjtu::invalid_iterator();
            }
            return ptr - rhs.ptr;
        }

        const_iterator& operator+=(const int &n) {
            ptr += n;
            return *this;
        }

        const_iterator& operator-=(const int &n) {
            ptr -= n;
            return *this;
        }

        const_iterator operator++(int) {
            const_iterator temp = *this;
            ++ptr;
            return temp;
        }

        const_iterator& operator++() {
            ++ptr;
            return *this;
        }

        const_iterator operator--(int) {
            const_iterator temp = *this;
            --ptr;
            return temp;
        }

        const_iterator& operator--() {
            --ptr;
            return *this;
        }

        const T& operator*() const {
            return *ptr;
        }

        bool operator==(const const_iterator &rhs) const {
            return ptr == rhs.ptr;
        }

        bool operator==(const iterator &rhs) const {
            return ptr == rhs.getPtr();
        }

        bool operator!=(const const_iterator &rhs) const {
            return !(*this == rhs);
        }

        bool operator!=(const iterator &rhs) const {
            return !(*this == rhs);
        }
    };
    /**
     * TODO Constructs
     * At least two: default constructor, copy constructor
     */
private:
    T* data;
    size_t size_, capacity;
public:
    vector() : data(nullptr), size_(0), capacity(0) {}
    vector(const vector &other) : size_(other.size_), capacity(other.capacity) {
        data = static_cast<T*>(operator new(capacity * sizeof(T)));
        for (size_t i = 0; i < size_; ++i) {
            new (data + i) T(other.data[i]);
        }
    }
    /**
     * TODO Destructor
     */
    ~vector() {
        for (size_t i = 0; i < size_; ++i) {
            data[i].~T();
        }
        operator delete(data);
    }
    /**
     * TODO Assignment operator
     */
    vector &operator=(const vector &other) {
        if (this != &other) {
            for (size_t i = 0; i < size_; ++i) {
                data[i].~T();
            }
            operator delete(data);
            size_ = other.size_;
            capacity = other.capacity;
            data = static_cast<T*>(operator new(capacity * sizeof(T)));
            for (size_t i = 0; i < size_; ++i) {
                new (data + i) T(other.data[i]);
            }
        }
        return *this;
    }
    /**
     * assigns specified element with bounds checking
     * throw index_out_of_bound if pos is not in [0, size)
     */
    T & at(const size_t &pos) {
        if (pos >= size_) {
            throw index_out_of_bound();
        }
        return data[pos];
    }
    const T & at(const size_t &pos) const {
        if (pos >= size_) {
            throw index_out_of_bound();
        }
        return data[pos];
    }
    /**
     * assigns specified element with bounds checking
     * throw index_out_of_bound if pos is not in [0, size)
     * !!! Pay attentions
     *   In STL this operator does not check the boundary but I want you to do.
     */
    T & operator[](const size_t &pos) {
        if (pos >= size_) {
            throw index_out_of_bound();
        }
        return data[pos];
    }
    const T & operator[](const size_t &pos) const {
        if (pos >= size_) {
            throw index_out_of_bound();
        }
        return data[pos];
    }
    /**
     * access the first element.
     * throw container_is_empty if size == 0
     */
    const T & front() const {
        if (empty()) {
            throw container_is_empty();
        }
        return data[0];
    }
    /**
     * access the last element.
     * throw container_is_empty if size == 0
     */
    const T & back() const {
        if (empty()) {
            throw container_is_empty();
        }
        return data[size_ - 1];
    }
    /**
     * returns an iterator to the beginning.
     */
    iterator begin() {
        return iterator(data, this);
    }
    const_iterator begin() const {
        return const_iterator(data, this);
    }
    const_iterator cbegin() const {
        return const_iterator(data, this);
    }
    /**
     * returns an iterator to the end.
     */
    iterator end() {
        return iterator(data + size_, this);
    }
    const_iterator end() const {
        return const_iterator(data + size_, this);
    }
    const_iterator cend() const {
        return const_iterator(data + size_, this);
    }
    /**
     * checks whether the container is empty
     */
    bool empty() const {
        return size_ == 0;
    }
    /**
     * returns the number of elements
     */
    size_t size() const {
        return size_;
    }
    /**
     * clears the contents
     */
    void clear() {
        for (size_t i = 0; i < size_; ++i) {
            data[i].~T();
        }
        operator delete(data);
        data = nullptr;
        size_ = 0;
        capacity = 0;
    }
    /**
     * inserts value before pos
     * returns an iterator pointing to the inserted value.
     */
    iterator insert(iterator pos, const T &value) {
        size_t index = pos - begin();
        if (size_ == capacity) {
            capacity = (capacity == 0) ? 1 : capacity * 2;
            T* newData = static_cast<T*>(operator new(capacity * sizeof(T)));
            for (size_t i = 0; i < index; ++i) {
                new (newData + i) T(data[i]);
                data[i].~T();
            }
            new (newData + index) T(value);
            for (size_t i = index; i < size_; ++i) {
                new (newData + i + 1) T(data[i]);
                data[i].~T();
            }
            operator delete(data);
            data = newData;
        } else {
            for (size_t i = size_; i > index; --i) {
                new (data + i) T(data[i - 1]);
                data[i - 1].~T();
            }
            new (data + index) T(value);
        }
        ++size_;
        return iterator(data + index, this);
    }
    /**
     * inserts value at index ind.
     * after inserting, this->at(ind) == value
     * returns an iterator pointing to the inserted value.
     * throw index_out_of_bound if ind > size (in this situation ind can be size because after inserting the size will increase 1.)
     */
    iterator insert(const size_t &ind, const T &value) {
        if (ind > size_) {
            throw index_out_of_bound();
        }
        return insert(iterator(data + ind, this), value);
    }
    /**
     * removes the element at pos.
     * return an iterator pointing to the following element.
     * If the iterator pos refers the last element, the end() iterator is returned.
     */
    iterator erase(iterator pos) {
        size_t index = pos - begin();
        data[index].~T();
        for (size_t i = index; i < size_ - 1; ++i) {
            new (data + i) T(data[i + 1]);
            data[i + 1].~T();
        }
        --size_;
        return iterator(data + index, this);
    }
    /**
     * removes the element with index ind.
     * return an iterator pointing to the following element.
     * throw index_out_of_bound if ind >= size
     */
    iterator erase(const size_t &ind) {
        if (ind >= size_) {
            throw index_out_of_bound();
        }
        return erase(iterator(data + ind, this));
    }
    /**
     * adds an element to the end.
     */
    void push_back(const T &value) {
        insert(end(), value);
    }
    /**
     * remove the last element from the end.
     * throw container_is_empty if size() == 0
     */
    void pop_back() {
        if (empty()) {
            throw container_is_empty();
        }
        --size_;
        data[size_].~T();
    }
};


}

#endif

//new -> operator new 用了豆包