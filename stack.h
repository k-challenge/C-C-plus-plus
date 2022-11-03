#ifndef UNTITLED8_STACK_H
#define UNTITLED8_STACK_H
#include <initializer_list>
#include <iostream>

template <class datatype>
class stack{
private:
    class node{
    public:
        datatype info;
        node*next;

        node(const datatype& info): info(info), next(nullptr) {}
    };

    node *top;
    size_t size;

    //===== Constructors =====//
#pragma region Constructors
public:

    stack(): top(nullptr), size(0u){}
    stack(std::string exp){
        this->top = new node(exp[exp.length()-1]);
        for(int i = exp.length()-2; i >= 0; i--)
            push(exp[i]);
    }
    ~stack(){
        this->clear();
    }
#pragma endregion

    //===== Methods =====//
#pragma region Methods
    void push(datatype info) {
        ++this->size;
        if(top == nullptr) {
            top = new node(info);
            return;
        }

        node*temp = new node(info);
        temp->next = this->top;
        this->top = temp;
    }

    node *pop(){
        if(top == nullptr) {
            return top;
        }

        --size;
        node *temp = this->top;
        this->top = this->top->next;
        temp->next = nullptr;
        return temp;
    }

    void reverse() {
        node * prev, *curent, *next;
        curent = prev = top;
        curent = curent->next;
        prev->next = nullptr;
        while(curent != nullptr) {
            next = curent->next;
            curent->next = prev;
            prev = curent;
            curent = next;
        }
        top = prev;
    }

    bool empty() const{
        return size == 0;
    }

    void clear() {
        while(this->top!=0) {
            pop();
        }
    }

    node*_top() const {
        return this->top;
    }
    void out() const{
        if(top == nullptr) {
            std::cout << "| |" << std::endl;
            return;
        }

        std::cout<<"| "<<top->info<<" |";
        for(node*i = top->next; i!= nullptr; i = i->next)
            std::cout<<" "<<i->info<<" |";
        std::cout<<std::endl;
    }

    size_t length() const{
        return this->size;
    }
#pragma endregion

    //===== Operator =====//

#pragma endregion
};

#endif //UNTITLED8_STACK_H
