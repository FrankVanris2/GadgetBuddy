/**
 * By: Frank Vanris
 * Date: 7/15/2025
 * Desc: Re-Implementing since the Uno doesn't have the standard C++ library, so using regular C-standard array
 */

 #pragma once
 #include "Interfaces/CircularBufferInterface.h"
 #include <Arduino.h>

 template<class T>
 class CircularBuffer : public CircularBufferInterface<T> {
 private: 
    T* buffer;
    int writeIndex; //front
    int readIndex; //back
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
   bool isEmpty() const override;

   /// @brief Checks if buffer is full
   /// @return true or false
   bool isFull() const override;

   /// @brief Checks the size of the buffer
   /// @return current size of buffer with elements inside
   int size() const override;

   /// @brief Prints out the contents within the Buffer
   void printBuffer() const override;

 };
 