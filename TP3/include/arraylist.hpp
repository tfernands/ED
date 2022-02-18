#ifndef ARRAYLIST_HPP
#define ARRAYLIST_HPP

#include "collection.hpp"

template<class T>
class ArrayList: public Collection<T> {

    private:
    T* arr;
    int sz, capacity = 0;

    void set_capacity(int capacity){
        if (capacity <= this->sz){
            throw ("Cannot make the array smaller than it is ocupied.");
        }
        this->capacity = capacity;
        T* narr = new T[this->capacity];
        for (int i = 0; i < this->sz; i++){
            narr[i] = this->arr[i];
        }
        delete[] this->arr;
        this->arr = narr;
    }

    void assurecapacity(){
        if (this->sz == this->capacity){
            this->set_capacity(this->capacity*2);
        }
    }

    public:
    ArrayList() : ArrayList(10){}
    ArrayList(int capacity){
        this->sz = 0;
        this->capacity = capacity;
        this->arr = new T[this->capacity];
    }
    ~ArrayList(){
        delete[] arr;
    }

    inline void add(T item) override {
        this->assurecapacity();
        this->arr[this->sz++] = item;
    }

    inline void set(int index, T item) override {
        if (index<0) index=this->sz+index;
        if (index < 0 || index >= this->sz) throw ("Index out of bound.");
        this->arr[index] = item;
    }

    inline void insert(int index, T item) override {
        if (index > this->sz) throw ("Index out of bound.");
        this->assurecapacity();
        for (int i = this->sz++; i > index; i--){
            this->arr[i] = this->arr[i-1];
        }
        this->arr[index] = item;
    }
  
    inline T pop() override {
        return this->arr[--this->sz];
    }

    inline T pop(int index) override {
        T item = (*this)[index];
        for (int i = index; i < this->sz-1; i++){
            this->arr[i] = this->arr[i+1];
        }
        this->sz--;
        return item;
    }

    inline T& get(int index) override {
        if (index<0) index=this->sz+index;
        if (index < 0 || index >= this->sz) throw ("Index out of bound.");
        return this->arr[index];
    }

    inline int size() override {
        return this->sz;
    }
};


#endif