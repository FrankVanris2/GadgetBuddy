/**
 * @file CircularBufferInterface.h
 * @author Frank Vanris
 * @date 7/15/2025
 * @brief Interface for a generic circular buffer.
 *
 * This template abstract class defines the required methods for any circular buffer implementation,
 * supporting modularity and interchangeability within the GadgetBuddy system.
 */

#ifndef CIRCULAR_BUFFER_INTERFACE_H
#define CIRCULAR_BUFFER_INTERFACE_H

template<class T>
class CircularBufferInterface {
public:
    /**
     * @brief Default constructor.
     */
    CircularBufferInterface() {}

    /**
     * @brief Virtual destructor.
     */
    virtual ~CircularBufferInterface() {}

    /**
     * @brief Add an element to the back of the buffer.
     * @param val Value to add.
     */
    virtual void push_back(const T& val) = 0;

    /**
     * @brief Remove the front element from the buffer.
     */
    virtual void pop_front() = 0;

    /**
     * @brief Get the front element.
     * @return Front element.
     */
    virtual T get_front() = 0;

    /**
     * @brief Get the back (most recently added) element.
     * @return Back element.
     */
    virtual T get_back() = 0;

    /**
     * @brief Check if buffer is empty.
     * @return True if empty, false otherwise.
     */
    virtual bool isEmpty() const = 0;

    /**
     * @brief Check if buffer is full.
     * @return True if full, false otherwise.
     */
    virtual bool isFull() const = 0;

    /**
     * @brief Get the sum of all elements in the buffer.
     * @return Sum of elements.
     */
    virtual T sum() const = 0;

    /**
     * @brief Clear all elements from the buffer.
     */
    virtual void clear() = 0;

    /**
     * @brief Get the current number of elements in the buffer.
     * @return Number of elements.
     */
    virtual int size() const = 0;

    /**
     * @brief Print buffer contents (for debugging).
     */
    virtual void printBuffer() const = 0;
};

#endif