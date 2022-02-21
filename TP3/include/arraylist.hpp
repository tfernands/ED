#ifndef ARRAYLIST_HPP
#define ARRAYLIST_HPP

#include <stdexcept>
#include "collection.hpp"

template<class T>
class ArrayList: public Collection<T> {

    private:
    T* arr;
    int sz, capacity = 0;

    void set_capacity(int capacity){
        if (capacity <= this->sz){
            throw std::invalid_argument("Cannot make the array smaller than it is occupied.");
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

    ArrayList(const ArrayList<T>& arraylist) {
        this->sz = arraylist.size();
        this->capacity = arraylist.current_capacity();
        this->arr = new T[this->capacity];
        for (int i = 0; i < this->sz; i++){
            this->arr[i] = arraylist.get(i);
        }
    }

    ArrayList(std::initializer_list<T> list): ArrayList(list.size()){
         for (T item: list){
            add(item);
        }
    }

    virtual ~ArrayList(){
        delete[] arr;
    }

    ArrayList<T>& operator=(const ArrayList<T>& arraylist) {
        if (arraylist.current_capacity() > this->capacity){
            this->set_capacity(arraylist.current_capacity());
        }
        for (int i = 0; i < arraylist.size(); i++){
            this->arr[i] = arraylist.get(i);
        }
        this->sz = arraylist.size();
        return *this;
    }

    inline void add(const T& item) override {
        this->assurecapacity();
        this->arr[this->sz++] = item;
    }

    inline void set(int index, const T& item) override {
        if (index<0) index=this->sz+index;
        if (index < 0 || index >= this->sz) throw std::invalid_argument("Index out of bound.");
        this->arr[index] = item;
    }

    inline void insert(int index, const T& item) override {
        if (index > this->sz) throw std::invalid_argument("Index out of bound.");
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

    inline T& get(int index) const override {
        if (index<0) index=this->sz+index;
        if (index < 0 || index >= this->sz) throw std::invalid_argument("Index out of bound.");
        return this->arr[index];
    }

    inline int size() const override {
        return this->sz;
    }

    void clear() override {
        this->sz = 0;
    }

    inline int current_capacity() const {
        return this->capacity;
    }
};


#endif