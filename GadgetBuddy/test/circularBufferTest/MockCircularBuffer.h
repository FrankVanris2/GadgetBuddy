/**
 * By: Frank Vanris
 * Date: 7/15/2025
 * Desc: This is the Mock code for the Re-Implementation of the 
 * Circular Buffer since the Uno doesn't have the standard C++ library, 
 * so I am using regular C-standard array.
 */

 #pragma once
 #include "Interfaces/CircularBufferInterface.h"
 

 template<typename T>
 class MockCircularBuffer : public CircularBufferInterface<T> {
 private: 
    T* buffer;
    int writeIndex;
    int readIndex;
    int capacity;

    
 public:
      MockCircularBuffer(int _capacity) {
         if(_capacity < 0) {
            //Serial.println("Error: Invalid capacity. Capacity cannot be negative. "); // For actual arduino implementation
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
            // Serial.println("Error: CircularBuffer is empty. Cannot remove elements."); for actual arduino implementation
            return;
         }
         readIndex = (readIndex + 1) % capacity;
      }

      T get_front() override {
         if(isEmpty()) {
            // Serial.println("Error: CircularrBuffer is empty. No front element."); For actual arduino implementation
            return T();
         }
         return buffer[readIndex]; // Return the element at the 'front' index
      }
      
      T get_back() override {
         if(isEmpty()) {
            // Serial.println("Error: CircularBuffer is empty. No back element."); For actual arduino implementation
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

      int size() const override {
         if (writeIndex >= readIndex) {
            return writeIndex - readIndex;
         }

         return capacity - (readIndex - writeIndex);
      }

      void printBuffer() const {
         if (isEmpty()) {
            // Serial.println("[Buffer is empty]"); For actual arduino implementation
            return;
         }
         int idx = readIndex;
         // Serial.print("["); for arduino implementation
         while(idx != writeIndex) {
            // Serial.print(buffer[idx]); For arduino implementation
            idx = (idx + 1) % capacity;
            if(idx != writeIndex) {
                  // Serial.print(" "); For arduino Implementation
            }
         }
         // Serial.println("]");  for arduino Implmentation.
      }
 };