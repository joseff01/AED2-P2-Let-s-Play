#ifndef PERSONAL_LINKED_LIST_H
#define PERSONAL_LINKED_LIST_H

#include <stdlib.h>
#include "Node.h"

template <typename T>
class List
{
private:
    void subError(); // Handles memory subscripts out of range
    void checkPos(const size_t position);

    Node<T> *head;
    Node<T> *last;

    size_t listSize;

public:
    //! Constructs a new linked list
    List() : head(nullptr), last(nullptr), listSize(0) {}

    //! Calls the clear method, deleting it's contents
    ~List();

    // element access:
    T at(const size_t position);
    T operator[](const size_t position);

    // insert/delete
    void push_back(const T value);
    void insert(const size_t position, const T value);

    // delete
    T pop_back();
    void erase(const size_t position);
    void clear();

    // gets
    size_t length();
    T front();
    T back();
};

#endif