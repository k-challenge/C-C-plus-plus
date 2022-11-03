// Huynh Tan Kiet
// Queue
// Created on: 23/10/2022
// ----------------------------------------
// default constructor       : O(1)
// push, pop                 : O(1)
// firt, last                : O(1)
// out                       : O(n)
// operator()                : O(1)
// ----------------------------------------

#ifndef UNTITLED8_STACK_H
#define UNTITLED8_STACK_H
#include <iostream>
#include <initializer_list>

template < class datatype >
class queue {
private:
    class node {
    public:
        datatype info;
        node * next;
        node(const datatype & info): info(info), next(nullptr) {}
    };

    node * head;
    node * tail;
    size_t size;

    //===== Constructors =====//
#pragma region Constructors
public:
    queue(std::initializer_list<datatype> source) :
    head{ nullptr }, tail{ nullptr }, size{ 0u } {
        for (auto i : source)
            this->push(i);
    }
    queue(): head(nullptr), tail(nullptr), size(0) {} // Constructors
    ~queue() {
        this -> clear();
    } // Destructor
#pragma endregion

    //===== Methods =====//
#pragma region Methods
    void push(const datatype & info) {
        ++this -> size;
        if (head == nullptr) { // if queue is empty then initialize head and tail
            head = tail = new node(info);
            return;
        }

        tail -> next = new node(info); // add a node after tail
        tail = tail -> next; // move tail move tail to the end position
    }

    node * pop() {
        if (this -> head == nullptr)
            return this -> head;

        node * temp = this -> head;
        this -> head = this -> head -> next;
        --this -> size;
        return temp;
    }

    bool empty() const {
        return size == 0;
    }

    void clear() {
        while (this -> head)
            pop();
    }

    node * last() const {
        return this -> tail;
    }

    node * firt() const {
        return this -> head;
    }

    size_t length() const {
        return this -> size;
    }
    void out() const {
        std::cout << '[';
        for (node* i = this->head; i != nullptr; i = i->next) {
            std::cout << i->info;
            if (i->next != nullptr)
                std::cout << ", ";
        }
        std::cout << "]";
    }

    //===== Operator =====//
#pragma endregion

    operator bool() const {
        return size != 0; // if size != 0 return true else return !true
    }

#pragma endregion
};
template <class datatype>
std::ostream& operator<<(std::ostream& os, queue<datatype> list){
    list.out();
    return os;
}
#endif //UNTITLED8_STACK_H