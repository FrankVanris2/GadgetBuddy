/**
 * @file CircularBuffer.h
 * @author Frank Vanris
 * @date 7/15/2025
 * @brief Lightweight circular buffer implementation for Arduino and Uno compatibility.
 *
 * This template class provides a fixed-size circular buffer using a C-style array,
 * supporting push, pop, sum, and print operations. Designed for environments without
 * the standard C++ library, such as Arduino Uno.
 */

#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H

#include "Interfaces/CircularBufferInterface.h"
#include <Arduino.h> // Required for Serial printing in Arduino environments

/**
 * @class CircularBuffer
 * @brief Fixed-size circular buffer for generic type T.
 * @tparam T Type of elements stored in the buffer.
 */
template<class T>
class CircularBuffer : public CircularBufferInterface<T> {
public:
    /**
     * @brief Constructor.
     * @param _capacity Maximum number of elements (user capacity).
     */
    CircularBuffer(int _capacity);

    /**
     * @brief Destructor.
     */
    ~CircularBuffer() override;

    /**
     * @brief Add an element to the back of the buffer.
     *        Overwrites oldest element if buffer is full.
     * @param val Value to add.
     */
    void push_back(const T& val) override;

    /**
     * @brief Remove the front element from the buffer.
     */
    void pop_front() override;

    /**
     * @brief Get the front element.
     * @return Front element, or default value if empty.
     */
    T get_front() override;

    /**
     * @brief Get the back (most recently added) element.
     * @return Back element, or default value if empty.
     */
    T get_back() override;

    /**
     * @brief Check if buffer is empty.
     * @return True if empty, false otherwise.
     */
    bool isEmpty() const override;

    /**
     * @brief Check if buffer is full.
     * @return True if full, false otherwise.
     */
    bool isFull() const override;

    /**
     * @brief Get the sum of all elements in the buffer.
     * @return Sum of elements (requires T to support operator+).
     */
    T sum() const override;

    /**
     * @brief Clear all elements from the buffer.
     */
    void clear() override;

    /**
     * @brief Get the current number of elements in the buffer.
     * @return Number of elements.
     */
    int size() const override;

    /**
     * @brief Print buffer contents to Serial (for debugging).
     */
    void printBuffer() const override;

private:
    T* buffer;           ///< Underlying array storage
    int writeIndex;      ///< Index for next write (back)
    int readIndex;       ///< Index for next read (front)
    int capacity;        ///< Internal buffer capacity (user capacity + 1)
};

// --- Template Method Definitions ---

template <class T>
CircularBuffer<T>::CircularBuffer(int _capacity) {
    if (_capacity < 0) {
        Serial.println("Error: Invalid capacity. Capacity cannot be negative.");
        while (true); // Halt execution on critical error
    }
    this->capacity = _capacity + 1; // Internal capacity is user_capacity + 1
    this->buffer = new T[this->capacity];
    this->writeIndex = 0;
    this->readIndex = 0;
}

template <class T>
CircularBuffer<T>::~CircularBuffer() {
    delete[] buffer;
    buffer = nullptr;
}

template <class T>
void CircularBuffer<T>::push_back(const T& val) {
    if (isFull()) {
        readIndex = (readIndex + 1) % capacity; // Overwrite oldest element
    }
    buffer[writeIndex] = val;
    writeIndex = (writeIndex + 1) % capacity;
}

template <class T>
void CircularBuffer<T>::pop_front() {
    if (isEmpty()) {
        Serial.println("Error: CircularBuffer is empty. Cannot remove elements.");
        return;
    }
    readIndex = (readIndex + 1) % capacity;
}

template <class T>
T CircularBuffer<T>::get_front() {
    if (isEmpty()) {
        Serial.println("Error: CircularBuffer is empty. No front element.");
        return T();
    }
    return buffer[readIndex];
}

template <class T>
T CircularBuffer<T>::get_back() {
    if (isEmpty()) {
        Serial.println("Error: CircularBuffer is empty. No back element.");
        return T();
    }
    return buffer[(writeIndex - 1 + capacity) % capacity];
}

template <class T>
bool CircularBuffer<T>::isEmpty() const {
    return writeIndex == readIndex;
}

template <class T>
bool CircularBuffer<T>::isFull() const {
    return (writeIndex + 1) % capacity == readIndex;
}

template <class T>
T CircularBuffer<T>::sum() const {
    T total = T();
    if (isEmpty()) return total;
    int current_idx = readIndex;
    int current_size = size();
    for (int i = 0; i < current_size; ++i) {
        total += buffer[current_idx];
        current_idx = (current_idx + 1) % capacity;
    }
    return total;
}

template <class T>
void CircularBuffer<T>::clear() {
    readIndex = 0;
    writeIndex = 0;
}

template <class T>
int CircularBuffer<T>::size() const {
    if (writeIndex >= readIndex) {
        return writeIndex - readIndex;
    }
    return capacity - (readIndex - writeIndex);
}

template <class T>
void CircularBuffer<T>::printBuffer() const {
    if (isEmpty()) {
        Serial.println("[Buffer is empty]");
        return;
    }
    int idx = readIndex;
    Serial.print("[");
    while (idx != writeIndex) {
        Serial.print(buffer[idx]);
        idx = (idx + 1) % capacity;
        if (idx != writeIndex) {
            Serial.print(" ");
        }
    }
    Serial.println("]");
}

#endif // CIRCULAR_BUFFER_H