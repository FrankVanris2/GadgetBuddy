/**
 * By: Frank Vanris
 * Date: 7/15/2025
 * Desc: Re-Implementing since the Uno doesn't have the standard C++ library, so using regular C-standard array
 */

#pragma once
#include "Interfaces/CircularBufferInterface.h"
#include <Arduino.h> // Keep this for Serial.println, as this is the Arduino-specific implementation

template<class T>
class CircularBuffer : public CircularBufferInterface<T> { // GOOD: public inheritance
private:
    T* buffer;
    // FIX: Corrected comments for clarity. writeIndex is the 'back', readIndex is the 'front'.
    int writeIndex; // back
    int readIndex;  // front
    int capacity;

public:

    /// @brief This is the circular buffer constructor.
    /// @param _capacity
    CircularBuffer(int _capacity);

    /// @brief Destructor for the circular buffer.
    ~CircularBuffer() override;

    /// @brief Method to push back elements into the circular buffer.
    /// @param val
    void push_back(const T& val) override;


    /// @brief Method that pops the elements at the front of the buffer.
    void pop_front() override;

    /// @brief Gets the front element
    /// @return front element of buffer
    T get_front() override;

    /// @brief Gets the back element
    /// @return back element of buffer
    T get_back() override;

    /// @brief Checks if buffer is empty
    /// @return true or false
    bool isEmpty() const override; // GOOD: const-correct

    /// @brief Checks if buffer is full
    /// @return true or false
    bool isFull() const override; // GOOD: const-correct

    /// @brief Get the sum of all the elements within the Buffer
    /// @return all the summed elements within the buffer
    T sum() const override; // FIX: Added 'const' as it doesn't modify object state

    /// @brief Checks the size of the buffer
    /// @return current size of buffer with elements inside
    int size() const override; // GOOD: const-correct

    /// @brief Prints out the contents within the Buffer
    void printBuffer() const override; // GOOD: const-correct

};

// --- Template Method Definitions (MOVED FROM .CPP AND PLACED HERE) ---

template <class T>
CircularBuffer<T>::CircularBuffer(int _capacity) {
    if(_capacity < 0) {
        Serial.println("Error: Invalid capacity. Capacity cannot be negative. ");
        // For Arduino, while(true) is a valid (though drastic) way to halt execution on critical error.
        // For native testing, this would hang the test.
        while(true); // loop indefinitely
    }

    this->capacity = _capacity + 1; // Internal capacity is user_capacity + 1

    //Dynamically allocate memory for the buffer using 'new'
    this->buffer = new T[this->capacity];
    this->writeIndex = 0;
    this->readIndex = 0;
}

template <class T>
CircularBuffer<T>::~CircularBuffer() {
    delete[] buffer; // Free the array memory
    buffer = nullptr; // Prevent dangling pointer
}


template <class T>
void CircularBuffer<T>::push_back(const T& val) {
    if(isFull()) {
        readIndex = (readIndex + 1) % capacity; // Overwrite oldest element if full
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
    readIndex = (readIndex + 1) % capacity; // Advance read index
}

template <class T>
T CircularBuffer<T>::get_front() {
    if(isEmpty()) {
        Serial.println("Error: CircularBuffer is empty. No front element.");
        return T(); // Return default-constructed value
    }

    return buffer[readIndex]; // Return the element at the 'front' index
}

template <class T>
T CircularBuffer<T>::get_back() {
    if(isEmpty()) {
        Serial.println("Error: CircularBuffer is empty. No back element.");
        return T(); // Return default-constructed value
    }

    // Calculate the index of the last inserted element
    // (writeIndex - 1) handles the case where writeIndex is 0 after a wrap-around
    return buffer[(writeIndex - 1 + capacity) % capacity];
}

template <class T>
bool CircularBuffer<T>::isEmpty() const {
    return writeIndex == readIndex;
}

template <class T>
bool CircularBuffer<T>::isFull() const {
    // This condition correctly implements the "one empty slot" strategy
    return (writeIndex + 1) % capacity == readIndex;
}

// FIX: Added 'const' to the definition to match declaration
template <class T>
T CircularBuffer<T>::sum() const {
    T total = T(); // Initialize sum to the default value of type T (e.g., 0 for numeric types)

    if (isEmpty()) {
        return total;
    }

    int current_idx = readIndex;
    int current_size = size(); // Get the current number of elements

    // Loop through each element currently in the buffer.
    for (int i = 0; i < current_size; ++i) {
        total += buffer[current_idx]; // Add the element at the current_idx to the total.
        current_idx = (current_idx + 1) % capacity; // Move to the next logical element, wrapping around.
    }
    return total; // Return the calculated sum.
}

template <class T>
int CircularBuffer<T>::size() const {
    if (writeIndex >= readIndex) {
        return writeIndex - readIndex;
    }
    // When writeIndex has wrapped around (e.g., writeIndex < readIndex)
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
    while(idx != writeIndex) {
        Serial.print(buffer[idx]); // Prints the element (assumes T is printable by Serial.print)
        idx = (idx + 1) % capacity;
        if(idx != writeIndex) {
            Serial.print(" ");
        }
    }
    Serial.println("]");
}
