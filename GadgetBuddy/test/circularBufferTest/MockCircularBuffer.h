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
    int front;
    int back;
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
         this->front = 0;
         this->back = 0;
      }

      ~MockCircularBuffer() override {
         delete[] buffer; // Free the array memory
         buffer = nullptr; // Prevent dangling pointer
      }

      void push_back(const T& val) override {
         if(isFull()) {
            front = (front + 1) % capacity;
         }
         buffer[back] = val;
         back = (back + 1) % capacity;
      }

      void pop_front() override {
         if (isEmpty()) {
            // Serial.println("Error: CircularBuffer is empty. Cannot remove elements."); for actual arduino implementation
            return;
         }
         front = (front + 1) % capacity;
      }

      T get_front() override {
         if(isEmpty()) {
            // Serial.println("Error: CircularrBuffer is empty. No front element."); For actual arduino implementation
            return T();
         }
         return buffer[front]; // Return the element at the 'front' index
      }
      
      T get_back() override {
         if(isEmpty()) {
            // Serial.println("Error: CircularBuffer is empty. No back element."); For actual arduino implementation
            return T();
         }

         return buffer[(back - 1 + capacity) % capacity];
      }

      bool isEmpty() const override {
         return back == front;
      }

      bool isFull() const override {
         return (back + 1) % capacity == front;
      }

      int size() const override {
         if (back >= front) {
            return back - front;
         }

         return capacity - (front - back);
      }

      void printBuffer() const {
         if (isEmpty()) {
            // Serial.println("[Buffer is empty]"); For actual arduino implementation
            return;
         }
         int idx = front;
         // Serial.print("["); for arduino implementation
         while(idx != back) {
            // Serial.print(buffer[idx]); For arduino implementation
            idx = (idx + 1) % capacity;
            if(idx != back) {
                  // Serial.print(" "); For arduino Implementation
            }
         }
         // Serial.println("]");  for arduino Implmentation.
      }
 };