/**
 * By: Frank Vanris
 * Date: 7/15/2025
 * Desc: Re-Implementing since the Uno doesn't have the standard C++ library, so using regular C-standard array
 */

 #pragma once
 #include "Interfaces/CircularBufferInterface.h"

 template<typename T>
 class CircularBuffer : public CircularBufferInterface<T> {
 private: 
    T* buffer;
    int front;
    int back;
    int capacity
    
 public:
 };
 