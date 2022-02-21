#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP

#include "collection.hpp"

template<class T>
class ListNode {
    public:
    T item;
    ListNode<T>* next;
    ListNode(const T& item){
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

    ListNode<T>* getNode(int index) const {
        if (index >= 0 && index < this->sz) {
            int i = 0;
            ListNode<T>* current = this->start;
            while (current != nullptr){
                if (i++ == index) return current;
                else if (current->next != nullptr) current = current->next;
            }
        }
        throw std::invalid_argument("index out of bound");
    }

    public:

    LinkedList(){
        this->start = nullptr;
        this->sz = 0;
    }

    LinkedList(std::initializer_list<T> list): LinkedList(){
         for (T item: list){
            this->add(item);
        }
    }

    LinkedList(const LinkedList<T>& linkedlist){
        this->start = nullptr;
        this->sz = 0;
        for (int i = 0; i < linkedlist.size(); i++){
            this->add(linkedlist.get(i));
        }
    }

    virtual ~LinkedList(){
        this->clear();
    }

    LinkedList<T>& operator=(const LinkedList<T>& linkedlist) {
        this->clear();
        for (int i = 0; i < linkedlist.size(); i++){
            this->add(linkedlist.get(i));
        }
        return *this;
    }

    inline void add(const T& item) override {
        this->insert(this->sz, item);
    }

    inline void set(int index, const T& item) override {
        int i = 0;
        ListNode<T>* temp = this->start;
        while(temp->next != nullptr && i < index){
            temp = temp->next;
        }
        temp->item = item;
    }

    inline void insert(int index, const T& item) override {
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
            throw std::invalid_argument("Poping from an empty list.");
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
            throw std::invalid_argument("Index out of bound.");
        }
        this->sz--;
        T item = poped->item;
        delete poped;
        return item;
    }

    inline T& get(int index) const override {
        if (index<0) index=this->sz+index;
        return this->getNode(index)->item;
    }

    inline int size() const override {
        return this->sz;
    }

    inline void clear() override {
        ListNode<T>* current = this->start;
        while (current != nullptr){
            ListNode<T>* next = current->next;
            delete current;
            current = next;
        }
    }

};


#endif