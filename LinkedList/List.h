#ifndef PERSONAL_LINKED_LIST_H
#define PERSONAL_LINKED_LIST_H

#include <stdlib.h>
#include <stdexcept>
#include <iostream>
#include <string.h>
#include "Node.h"

/*!
 * \brief A doubly-linked list to suffice all your personal vector needs
 * 
 * \tparam T Type of the elements.
 */
template <typename T>
class List
{
private:
    //!Throws an out_of_range exception for calling some method with a subscript out of range
    void subError(const char *methodName)
    {
        char msg[] = "Subscript out of range when calling List function ";
        std::cout << msg << methodName << '\n';
        throw std::out_of_range(strcat(msg, methodName));
    }

    /*!
    * \brief Checks that a position given is valid for the current list, if not it calls subError
    * 
    * \param position the position to evaluate
    */
    void checkPos(const size_t position, const char *methodName)
    {
        if (position < 0 || position >= this->length())
        {
            subError(methodName);
        }
    }

    //! Points to the first element of the list
    Node<T> *head;

    //! Points to the last element of the list
    Node<T> *last;

    //! Holds the current amount of elements in the list
    size_t listSize;

public:
    //! Constructs a new linked list
    List() : head(nullptr), last(nullptr), listSize(0) {}

    //! Calls the clear method, deleting it's contents
    ~List()
    {
        this->clear();
    }

    // element access:

    /*!
    * \brief Returns a reference to the element at position _position_ in the vector container.
    * 
    * \param position position of the element in the container
    * \return T the element at the specified position 
    */
    T at(const size_t position)
    {
        checkPos(position, "at()");

        Node<T> *current = head;

        for (size_t i = 0; i < position; i++)
        {
            current = current->next;
        }
        return current->value;
    }

    /*!
    * \brief Returns a reference to the element at position _position_ in the vector container.
    * 
    * \param position position of the element in the container
    * \return T the element at the specified position 
    */
    T operator[](const size_t position)
    {
        return at(position);
    }

    // insert/delete

    /*!
    * \brief Adds a new element as the last element of the list
    * 
    * \param value value of the element to be inserted
    */
    void push_back(const T value)
    {
        Node<T> *newNode = new Node<T>(value);
        // If list is empty then assign newNode to head
        if (head == nullptr)
        {
            head = last = newNode;
        }
        else
        {
            Node<T> *current = last;
            newNode->prev = current;
            current->next = newNode;
            last = current->next;
        }
        ++listSize;
    }

    /*!
    * \brief Inserts a new element at the position given, the element gets inserted before the old element at the given position
    * 
    * \param position position where new element will be inserted, it's inserted before the element that used to have this position
    * \param value value of the element to be inserted
    */
    void insert(const size_t position, const T value)
    {
        if (position != 0)
        {
            checkPos(position - 1, "insert()");
        }

        Node<T> *newNode = new Node<T>(value);
        Node<T> *current = head;

        if (head == nullptr) // if list empty
        {
            head = last = newNode;
        }
        else if (position == 0) // if inserting at beginning
        {
            head = newNode;
            head->next = current;
            current->prev = head;
        }
        else if (position == this->length()) // if inserting at end
        {
            push_back(value);
            --listSize; // this is needed because push_back increases the size and then it'll get increased again at the end of this method
        }
        else
        {
            for (size_t i = 0; i < position; i++)
            {
                current = current->next;
            }
            current->prev->next = newNode;
            newNode->next = current;
            newNode->prev = current->prev;
            current->prev = newNode;
        }
        ++listSize;
    }

    // delete

    /*!
    * \brief Removes and returns the value of the last element on the list
    * 
    * \return T value of the element that was removed
    */
    T pop_back()
    {
        if (head == nullptr)
        {
            return NULL; //if list empty then return null
        }
        else if (head == last) // only 1 element
        {
            T retVal = last->value;
            delete head;
            head = last = nullptr;
            listSize = 0;
            return retVal;
        }
        else
        {
            T retVal = last->value;
            Node<T> *prevNode = last->prev;

            prevNode->next = nullptr;
            delete last;
            last = prevNode;
            --listSize;

            return retVal;
        }
    }

    /*!
    * \brief Erase the node from the list at the given position
    * 
    * \param position position of the element to be removed from the list
    */
    void erase(const size_t position)
    {
        checkPos(position, "erase()");
        if (head == nullptr) //if list empty
        {
            subError();
        }

        Node<T> *current = head;

        if (head == last) // if only 1 element
        {
            delete head;
            head = last = nullptr;
            listSize = 0;
            return;
        }

        if (position == 0) // if erasing first element
        {
            head = current->next;
            head->prev = nullptr;
            delete current;
        }
        else if (position == this->length()) // if erasing last element
        {
            current = last;
            last = current->prev;
            last->next = nullptr;
            delete current;
        }
        else
        {
            for (size_t i = 0; i < position; i++)
            {
                current = current->next;
            }
            current->prev->next = current->next;
            current->next->prev = current->prev;
            delete current;
        }
        --listSize;
    }

    //! Empty out the contents of the list by calling pop_back() repeatedly
    void clear()
    {
        while (this->length() > 0)
        {
            this->pop_back();
        }
    }

    // gets

    /*!
    * \brief Get the length of the list
    * 
    * \return size_t length of the list
    */
    size_t length()
    {
        return this->listSize;
    }

    /*!
    * \brief Get the first element of the list
    * 
    * \return T the first element of the list
    */
    T front()
    {
        return *(this->head);
    }

    /*!
    * \brief Return the element at the end of the list
    * 
    * \return T element at the end of the list
    */
    T back()
    {
        return *(this->last);
    }

    void print()
    {
        Node<T> *current = head;
        std::cout << "[" << current->value;
        while (current->next != nullptr)
        {
            current = current->next;
            std::cout << ", " << current->value;
        }
        std::cout << "]\n";
    }
};

#endif