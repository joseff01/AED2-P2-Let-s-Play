#include "List.h"

template <typename T>
List<T>::~List()
{
    this->clear();
}

template <typename T>
T List<T>::at(const size_t position)
{
    checkPos(position);

    Node<T> *current = head;

    for (size_t i = 0; i < position; i++)
    {
        current = current->next;
    }
    return current->value;
}

template <typename T>
T List<T>::operator[](const size_t position)
{
    return at(position);
}

template <typename T>
void List<T>::push_back(const T value)
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

template <typename T>
T List<T>::pop_back()
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

template <typename T>
void List<T>::insert(const size_t position, const T value)
{
    checkPos(position);

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

template <typename T>
void List<T>::erase(const size_t position)
{
    checkPos();
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

template <typename T>
void List<T>::clear()
{
    while (this->length() > 0)
    {
        this->pop_back();
    }
}

template <typename T>
void List<T>::checkPos(const size_t position)
{
    if (position < 0 || position >= this->length())
    {
        subError();
    }
}

template <typename T>
void List<T>::subError()
{
    printf("ERROR: Subscript out of range.\n");
    throw std::out_of_range("Subscript out of range.");
}

/*!
 * \brief Get the length of the list
 * 
 * \return size_t length of the list
 */
template <typename T>
size_t List<T>::length()
{
    return this->listSize;
}

/*!
 * \brief Get the first element of the list
 * 
 * \return T the first element of the list
 */
template <typename T>
T List<T>::front()
{
    return *(this->head);
}

/*!
 * \brief Return the element at the end of the list
 * 
 * \return T element at the end of the list
 */
template <typename T>
T List<T>::back()
{
    return *(this->last);
}