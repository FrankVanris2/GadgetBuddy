/**
 * By: Frank Vanris
 * Date: 7/15/2025
 * Desc: Re-Implementing since the Uno doesn't have the standard C++ library, so using regular C-standard array
 */

 #pragma once
 #include "Interfaces/CircularBufferInterface.h"
 #include <Arduino.h>

 template<typename T>
 class CircularBuffer : public CircularBufferInterface<T> {
 private: 
    T* buffer;
    int writeIndex; //front
    int readIndex; //back
    int capacity
    
 public:

   MockCircularBuffer(int _capacity) {
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

   ~MockCircularBuffer() override {
      delete[] buffer; // Free the array memory
      buffer = nullptr; // Prevent dangling pointer
   }

   // Pushing elements into the circular buffer.
   void push_back(const T& val) override {
      if(isFull()) {
         readIndex = (readIndex + 1) % capacity;
      }
      buffer[writeIndex] = val;
      writeIndex = (writeIndex + 1) % capacity;
   }

   // Popping elements at the front of the circular buffer.
   void pop_front() override {
      if (isEmpty()) {
         Serial.println("Error: CircularBuffer is empty. Cannot remove elements."); 
         return;
      }
      readIndex = (readIndex + 1) % capacity;
   }

   // Obtaining the front element within the circular buffer.
   T get_front() override {
      if(isEmpty()) {
         Serial.println("Error: CircularrBuffer is empty. No front element."); 
         return T();
      }

      return buffer[readIndex]; // Return the element at the 'front' index
   }

   // Getting back element within the circular buffer
   T get_back() override {
      if(isEmpty()) {
         Serial.println("Error: CircularBuffer is empty. No back element."); 
         return T();
      }

      return buffer[(writeIndex - 1 + capacity) % capacity];
   }

   // Function to check if circular buffer is empty
   bool isEmpty() const override {
      return writeIndex == readIndex;
   }

   // Function to check if circular buffer is full
   bool isFull() const override {
      return (writeIndex + 1) % capacity == readIndex;
   }

   // Function to return the size of the circular buffer
   int size() const override {
      if (writeIndex >= readIndex) {
         return writeIndex - readIndex;
      }

      return capacity - (readIndex - writeIndex);
   }

   // Printing the elements within the circular buffer
   void printBuffer() const {
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

 };
 