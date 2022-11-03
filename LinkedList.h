//=====  Devlin - Huynh Tan Kiet - 22/06/2022  ====//

#ifndef __Singly_Linked_List__
#define __Singly_Linked_List__
#include <iostream>
#include <initializer_list>

template <class datatype>
class LinkedList {
    class node {
    public:
        node * next;
        datatype data;
        node(const datatype& info): data(info), next(nullptr) {}
    };

    node* head;
    node* tail;
    size_t size;

public:
    //=====  Constructors  ======//
#pragma region Constructors
    LinkedList(): head(nullptr), tail(nullptr), size(0u) {}
    LinkedList(std::initializer_list<datatype> source) : head(nullptr), tail(nullptr), size(0u) {
        for(auto& i :source) {
            this->push_back(i);
        }
    };
    ~LinkedList() {
        this->clear();  
    }
#pragma endregion

    //====  Methods  ====//
#pragma region Methods
    void push_back(const datatype& data) {
        if(head == nullptr) {
            head = tail = new node(data);
            ++size;
            return;
        }

        tail->next = new node(data);
        tail = tail->next;
        tail->next = nullptr;
        ++size;
    }

    void push_front(const datatype& info) {
        if(head == nullptr) {
                head = tail = new node(info);
                ++size;
                return;
            }
        node*temp = new node(info);
        temp->next = head;
        head = temp;
        ++size;
    }

    void push_Position(datatype index, datatype info) {
        if(index>= size || index < 0) return;
        node* positon = head;
        node * back = new node(info);
        for(datatype i = 1; i< index;i++)
            positon = positon->next;
        push_BackNode(positon,back);
        ++size;
    }

    void interchangeSort() {
        for(node*i = head; i->next != nullptr; i = i->next)
            for(node*j = i;j!= nullptr; j=j->next) {
                if(i->data>j->data)
                    std::swap(i->data, j->data);
            }
    }
    void swap(int index1, int index2) {
        node*temp1 = head;
        node*temp2 = head;
        int i = 0;
        while (index1 != i) {
            temp1 = temp1->next;
            i++;
        }
        i = 0;
        while (index2 != i)
        {
            temp2 = temp2->next;
            i++;
        }
        datatype _temp = temp1->data;
        temp1->data = temp2->data;
        temp2->data = _temp;
    }
    void pop_front() {
           if(head == nullptr)
               return;
          this->head = this->head->next;
          --size;
    }

    void pop_Position(int index) {
        --this->size;
        if(index>=size || index < 0) return;
        if(index == 0) {
            head = head->next;
            return;
        }

        node*temp = head;
        for(int i = 1;i<index;i++)
            temp = temp->next;

        if(index==size-1) {
            temp->next = nullptr;
            tail = temp;
            return;
        }
       temp->next = temp->next->next;
    }

        LinkedList where( bool (*func)(const datatype&)) {
        LinkedList<datatype> result;

        for(node* point = head; point; point = point->next)
            if (func(point->data))
                result.push_back(point->data);
        return result;
    }

    void push_BackNode(node*befor, node*back) {
        back->next = befor->next;
        befor->next = back;
    }
    void clear() {
        while (this->head)
            this->pop_front();
        }

    void display() const {
        if(head == nullptr) {
            std::cout<<"[]";
            return;
        }

        std::cout << "[" << head->data;
        for(node* i = head->next; i != nullptr; i = i->next)
            std::cout<<", "<<i->data;
        std::cout<<"]"<<std::endl;
    }

    bool empty() const{
        return size == 0u;
    }

    size_t lenght() const {
        return this->size;
    }

    size_t size_of() const {
        return sizeof(LinkedList<datatype>) + sizeof(node) * size;
    }

#pragma endregion

    //=====  Operator  =====//
#pragma region Operator
    operator bool() const{
        return size != 0u;
    }

    LinkedList&operator=(const LinkedList& source) {
            this->clear();
            if(source.empty())
                return *this;

           this->head = source.head;
           this->tail = source.tail;
           this->size = source.getSize();
           return *this;
        }

    LinkedList&operator+= (const LinkedList& source) {
           if(source.empty())
               return *this;

            this->tail->next = source.head;
            tail = source.tail;
            size+=source.getSize();
            return source;
        }

    datatype& operator[] (int index){
            if (index < 0 || index >= size)
                throw "Index was outside the bounds of the list !";

           node* i = head;
           for(; index>0; --index)
               i = i->next;
           return i->data;
       }
#pragma endregion

    //=====  Iterator  =====//
#pragma region Iterator
    class iterator{
        node* pointer;

        friend LinkedList;
        iterator(node* pointer) : pointer{pointer} {}

    public:
        datatype& operator*(){
            return pointer->data;
        }

        datatype* operator->(){
            return &pointer->data;
        }

        iterator& operator++(){
            if(pointer != nullptr)
                pointer = pointer->next;

            return *this;
        }

        bool operator==(const iterator& other){
            return pointer == other.pointer;
        }

        bool operator!=(const iterator& other){
            return pointer != other.pointer;
        }
    };
#pragma endregion

    //=====  Const Iterator  =====//
#pragma region Const Iterator
    class const_iterator{
        const node* pointer;

        friend LinkedList;
        const_iterator(const node* pointer) : pointer{pointer} {}

    public:
        const datatype& operator*(){
            return pointer->data;
        }

        const datatype* operator->(){
            return &pointer->data;
        }

        const_iterator& operator++(){
            if(pointer != nullptr)
                pointer = pointer->next;

            return *this;
        }

        bool operator==(const const_iterator& other){
            return pointer == other.pointer;
        }

        bool operator!=(const const_iterator& other){
            return pointer != other.pointer;
        }
    };
#pragma endregion

    iterator begin(){
        return iterator(head);
    }

    iterator end(){
        return iterator(nullptr);
    }

    const_iterator begin() const {
        return const_iterator(head);
    }

    const_iterator end() const {
        return const_iterator(nullptr);
    }
};

template <class Datatype>
std::ostream &operator<<(std::ostream&os, const LinkedList<Datatype>& source) {
    source.display();
    return os;
}

#endif // __Singly_Linked_List__
