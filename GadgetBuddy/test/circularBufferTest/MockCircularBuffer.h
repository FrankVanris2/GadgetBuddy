/**
 * By: Frank Vanris
 * Date: 7/15/2025
 * Desc: Re-Implementing since the Uno doesn't have the standard C++ library, so using regular C-standard array
 */

 #pragma once
 #include "Interfaces/CircularBufferInterface.h"

 template<class T>
 class MockCircularBuffer : public CircularBufferInterface<T> {
 private: 
    T* buffer;
    int writeIndex; //front
    int readIndex; //back
    int capacity;
    
 public:

    MockCircularBuffer(int _capacity) {
        if(_capacity < 0) {
            //Serial.println("Error: Invalid capacity. Capacity cannot be negative. "); 
            while(true); // loop indefinitely
        }

        this->capacity = _capacity + 1;

        //Dynamically allocate memory for the buffer using 'new'
        this->buffer = new T[this->capacity];
        this->writeIndex = 0;
        this->readIndex = 0;
    }


    ~MockCircularBuffer() override {
        delete[] buffer; // Free the array memory
        buffer = nullptr; // Prevent dangling pointer
    }

    void push_back(const T& val) override {
        if(isFull()) {
            readIndex = (readIndex + 1) % capacity;
        }
        buffer[writeIndex] = val;
        writeIndex = (writeIndex + 1) % capacity;
    }

    void pop_front() override {
        if (isEmpty()) {
            //Serial.println("Error: CircularBuffer is empty. Cannot remove elements."); 
            return;
        }
        readIndex = (readIndex + 1) % capacity;
    }

    T get_front() override {
        if(isEmpty()) {
            //Serial.println("Error: CircularrBuffer is empty. No front element."); 
            return T();
        }

        return buffer[readIndex]; // Return the element at the 'front' index
    }

    T get_back() override {
        if(isEmpty()) {
            //Serial.println("Error: CircularBuffer is empty. No back element."); 
            return T();
        }

        return buffer[(writeIndex - 1 + capacity) % capacity];
    }

    bool isEmpty() const override {
        return writeIndex == readIndex;
    }

    bool isFull() const override {
        return (writeIndex + 1) % capacity == readIndex;
    }

    T sum() const override {
        T total = T(); // Initialize sum to default value
        if(isEmpty()) {
            return total;
        }
        int currentIdx = readIndex;
        int current_size = size();

        for(int i = 0; i < current_size; ++i) {
            total += buffer[currentIdx];
            currentIdx = (currentIdx + 1) % capacity;
        }
        return total;
    }

    void clear() override {
        if(!isEmpty()) {
            readIndex = 0;
            writeIndex = 0;
        }
    }

    int size() const override {
        if (writeIndex >= readIndex) {
            return writeIndex - readIndex;
        }

        return capacity - (readIndex - writeIndex);
    }

    void printBuffer() const override {
        if (isEmpty()) {
            //Serial.println("[Buffer is empty]");
            return;
        }
        int idx = readIndex;
        //Serial.print("[");
        while(idx != writeIndex) {
            //Serial.print(buffer[idx]);
            idx = (idx + 1) % capacity;
            if(idx != writeIndex) {
                //Serial.print(" ");
            }
        }
        //Serial.println("]");
    }

 };
 