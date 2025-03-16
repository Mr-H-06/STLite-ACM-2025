#ifndef SJTU_PRIORITY_QUEUE_HPP
#define SJTU_PRIORITY_QUEUE_HPP

#include <cstddef>
#include <functional>
#include "exceptions.hpp"

namespace sjtu {
/**
 * @brief a container like std::priority_queue which is a heap internal.
 * **Exception Safety**: The `Compare` operation might throw exceptions for certain data.
 * In such cases, any ongoing operation should be terminated, and the priority queue should be restored to its original state before the operation began.
 */
template<typename T, class Compare = std::less<T>>
class priority_queue {
public:
	/**
	 * @brief default constructor
	 */
	priority_queue() {}

	/**
	 * @brief copy constructor
	 * @param other the priority_queue to be copied
	 */
	priority_queue(const priority_queue &other) {}

	/**
	 * @brief deconstructor
	 */
	~priority_queue() {}

	/**
	 * @brief Assignment operator
	 * @param other the priority_queue to be assigned from
	 * @return a reference to this priority_queue after assignment
	 */
	priority_queue &operator=(const priority_queue &other) {}

	/**
	 * @brief get the top element of the priority queue.
	 * @return a reference of the top element.
	 * @throws container_is_empty if empty() returns true
	 */
	const T & top() const {}

	/**
	 * @brief push new element to the priority queue.
	 * @param e the element to be pushed
	 */
	void push(const T &e) {}

	/**
	 * @brief delete the top element from the priority queue.
	 * @throws container_is_empty if empty() returns true
	 */
	void pop() {}

	/**
	 * @brief return the number of elements in the priority queue.
	 * @return the number of elements.
	 */
	size_t size() const {}

	/**
	 * @brief check if the container is empty.
	 * @return true if it is empty, false otherwise.
	 */
	bool empty() const {}

	/**
	 * @brief merge another priority_queue into this one.
	 * The other priority_queue will be cleared after merging.
	 * The complexity is at most O(logn).
	 * @param other the priority_queue to be merged.
	 */
	void merge(priority_queue &other) {}
};

}

#endif