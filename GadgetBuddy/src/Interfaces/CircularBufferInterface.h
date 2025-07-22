/**
 * By: Frank Vanris
 * Date: 7/15/2025
 * Desc: Creating a Circular Buffer Interface
 */

 #pragma once

template<class T>
class CircularBufferInterface {
public:
    
    //constructor and destructor
    CircularBufferInterface(){}
    virtual ~CircularBufferInterface(){}

    // function for adding element to buffer
    virtual void push_back(const T& val) = 0;

    // function to remove an element from the buffer
    virtual void pop_front() = 0;

    // function to get the first element that's currently at the front
    virtual T get_front() = 0;

    // function to get the back element that's in the buffer
    virtual T get_back() = 0;

    // function to check if buffer is empty
    virtual bool isEmpty() const = 0;

    // function to check if buffer is full
    virtual bool isFull() const = 0;

    // return the sum of all elements within the buffer
    virtual T sum() const = 0;

    // function that clears the circular buffer with all elements
    virtual void clear() = 0;
    
    // getting the size of the circular buffer
    virtual int size() const = 0;

    // printing the contents within the buffer
    virtual void printBuffer() const = 0;
};