// ourDeque.h
#ifndef OURDEQUE_H
#define OURDEQUE_H

#include <stdexcept>

template <typename T>
class dnode {
public:
    T data;
    dnode* next;
    dnode* prev;

    dnode(const T& value = T()) : data(value), next(nullptr), prev(nullptr) {}
};

template <typename T>
class ourDeque {
private:
    dnode<T>* head;
    dnode<T>* tail;
    int count;

public:
    ourDeque() : head(nullptr), tail(nullptr), count(0) {}
    ~ourDeque() { clear(); }

    void push_back(const T& value);
    void push_front(const T& value);
    void pop_back();
    void pop_front();
    T front() const;
    T back() const;
    bool empty() const { return count == 0; }
    int size() const { return count; }
    void clear();
};

// Function definitions
template <typename T>
void ourDeque<T>::push_back(const T& value) {
    dnode<T>* newNode = new dnode<T>(value);
    if (empty()) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
    count++;
}

template <typename T>
void ourDeque<T>::push_front(const T& value) {
    dnode<T>* newNode = new dnode<T>(value);
    if (empty()) {
        head = tail = newNode;
    } else {
        head->prev = newNode;
        newNode->next = head;
        head = newNode;
    }
    count++;
}

template <typename T>
void ourDeque<T>::pop_back() {
    if (empty()) throw std::runtime_error("Deque is empty");
    dnode<T>* oldTail = tail;
    tail = tail->prev;
    if (tail) tail->next = nullptr;
    else head = nullptr;
    delete oldTail;
    count--;
}

template <typename T>
void ourDeque<T>::pop_front() {
    if (empty()) throw std::runtime_error("Deque is empty");
    dnode<T>* oldHead = head;
    head = head->next;
    if (head) head->prev = nullptr;
    else tail = nullptr;
    delete oldHead;
    count--;
}

template <typename T>
T ourDeque<T>::front() const {
    if (empty()) throw std::runtime_error("Deque is empty");
    return head->data;
}

template <typename T>
T ourDeque<T>::back() const {
    if (empty()) throw std::runtime_error("Deque is empty");
    return tail->data;
}

template <typename T>
void ourDeque<T>::clear() {
    while (!empty()) pop_front();
}

#endif
