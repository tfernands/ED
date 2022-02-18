#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP

#include "collection.hpp"

template<class T>
class ListNode {
    public:
    T item;
    ListNode<T>* next;
    ListNode(T item){
        this->item = item;
        this->next = nullptr;
    }
    virtual ~ListNode(){};
};

template<class T>
class LinkedList: public Collection<T> {

    private:
    ListNode<T>* start;
    int sz = 0;

    ListNode<T>* getNode(int index){
        if (index >= 0 && index < this->sz) {
            int i = 0;
            ListNode<T>* current = this->start;
            while (current != nullptr){
                if (i++ == index) return current;
                else if (current->next != nullptr) current = current->next;
            }
        }
        throw "index out of bound";
    }

    public:
    LinkedList(){
        this->start = nullptr;
        this->sz = 0;
    }

    virtual ~LinkedList(){
        ListNode<T>* current = this->start;
        while (current != nullptr){
            ListNode<T>* next = current->next;
            delete current;
            current = next;
        }
    }

    inline void add(T item) override {
        this->insert(this->sz, item);
    }

    inline void set(int index, T item) override {
        int i = 0;
        ListNode<T>* temp = this->start;
        while(temp->next != nullptr && i < index){
            temp = temp->next;
        }
        temp->item = item;
    }

    inline void insert(int index, T item){
        if (index == 0){
            ListNode<T>* temp = new ListNode<T>(item);
            temp->next = this->start;
            this->start = temp;
        }
        else if (index == this->sz){
            ListNode<T>* temp = this->start;
            while(temp->next != nullptr){
                temp = temp->next;
            }
            temp->next = new ListNode<T>(item);
        }
        else{
            ListNode<T>* previous = this->getNode(index-1);
            ListNode<T>* temp = new ListNode<T>(item);
            temp->next = previous->next;
            previous->next = temp;
        }
        this->sz++;
    }

    inline T pop() override {
        return this->pop(this->sz-1);
    }

    inline T pop(int index) override {
         ListNode<T>* poped;
        if (this->start == nullptr){
            throw ("Poping from an empty list.");
        }
        else if (index == 0){
            poped = this->start;
            this->start = this->start->next;
        }
        else if (index < this->sz){
            ListNode<T>* previous = this->getNode(index-1);
            poped = previous->next;
            previous->next = poped->next;
        }
        else{
            throw ("Index out of bound.");
        }
        this->sz--;
        T item = poped->item;
        delete poped;
        return item;
    }

    inline T& get(int index) override {
        if (index<0) index=this->sz+index;
        return this->getNode(index)->item;
    }

    inline int size() override {
        return this->sz;
    }



};


#endif