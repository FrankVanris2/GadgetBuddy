/**
 * By: Frank Vanris
 * Date: 7/17/2025
 * Desc: Created A Circular Buffer implementation that is around the C-based Array
 */

#include "CircularBuffer.h"

template <class T>
CircularBuffer<T>::CircularBuffer(int _capacity) {
    if(_capacity < 0) {
        Serial.println("Error: Invalid capacity. Capacity cannot be negative. "); 
        while(true); // loop indefinitely
    }

    this->capacity = _capacity + 1;

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
void CircularBuffer<T>::push_back(const T& val)  {
    if(isFull()) {
        readIndex = (readIndex + 1) % capacity;
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
    if(isEmpty()) {
        Serial.println("Error: CircularrBuffer is empty. No front element."); 
        return T();
    }

    return buffer[readIndex]; // Return the element at the 'front' index
}

template <class T>
T CircularBuffer<T>::get_back() {
    if(isEmpty()) {
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
    while(idx != writeIndex) {
        Serial.print(buffer[idx]);
        idx = (idx + 1) % capacity;
        if(idx != writeIndex) {
            Serial.print(" ");
        }
    }
    Serial.println("]");
}
