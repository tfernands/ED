#ifndef HASHMAP_HPP
#define HASHMAP_HPP

#include <string>
#include "linkedlist.hpp"

template<typename T>
struct Hash {
    inline virtual int operator()(T const &t) const noexcept = 0;
};
template <>
struct Hash<int> {
    inline int operator()(long const &t) const noexcept {
        return t;
    }
};
template <>
struct Hash<char*> {
    inline int operator()(char* const &t) const noexcept {
        const int p[] = {3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41};
        const int n = 12;
        unsigned long sum = 0;
        unsigned int i = 0;
        while(true){
            if (t[i] == '\0' || t[i] == '\n') break;
            sum += p[i%n]*t[i];
            i++;
        }
        return sum;
    }
};
template <>
struct Hash<std::string> {
    inline int operator()(std::string const &t) const noexcept {
        const int p[] = {3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41};
        const int n = 12;
        unsigned long sum = 0;
        unsigned int i = 0;
        while(true){
            if (t[i] == '\0' || t[i] == '\n') break;
            sum += p[i%n]*t[i];
            i++;
        }
        return sum;
    }
};

template <class K, class V>
class HashMap {

    private:
    class Proxy{
        K key;
        HashMap<K, V>& parent;
        public:
        Proxy(HashMap<K, V>&p, const K& k): key(k), parent(p){}
        virtual ~Proxy(){}
        inline void operator=(const V& item){
            parent.put(key, item);
        }
        inline operator const V&(){
            return parent.get(key);
        }
    };

    unsigned int capacity;
    Hash<K> hash_function;
    LinkedList<K>* keyset;
    LinkedList<V>* values;

    unsigned int map(const K& key) const {
        return this->hash_function(key)%this->capacity;
    }

    public:
    HashMap(): HashMap(200){}; 
    HashMap(unsigned int capacity){
        this->capacity = capacity;
        this->keyset = new LinkedList<K>[this->capacity];
        this->values = new LinkedList<V>[this->capacity];
    }
    HashMap(const HashMap& hashmap){
        this->capacity = capacity;
        this->keyset = new LinkedList<K>(*hashmap.keyset);
        this->values = new LinkedList<V>(*hashmap.values);
    }
    virtual ~HashMap(){
        delete[] this->keyset;
        delete[] this->values;
    }

    int colisions() const {
        unsigned int colisions = 0;
        for (unsigned int i = 0; i < this->capacity; i++){
            if (this->keyset[i].size() > 0){
                colisions += this->keyset[i].size()-1;
            }
        }
        return colisions;
    }

    void put(const K& key, const V& value){
        unsigned int hashmap = this->map(key);
        int index = this->keyset[hashmap].indexOf(key);
        if (index > -1){
            this->values[hashmap].set(index, value);
        }
        else{
            this->keyset[hashmap].add(key);
            this->values[hashmap].add(value);
        }
    }

    V& get(const K& key) const {
        unsigned int hashmap = this->map(key);
        int index = this->keyset[hashmap].indexOf(key);
        if (index > -1){
            return this->values[hashmap][index];
        }
        throw std::invalid_argument("Key not found.");
    }

    V del(const K& key){
        unsigned int hashmap = this->map(key);
        int index = this->keyset[hashmap].indexOf(key);
        if (index > -1){
            this->keyset->pop(index);
            return this->values[hashmap].pop(index);
        }
    }

    Proxy operator[](const K& key){
        return Proxy(*this, key);
    }

    void printStructure() const {
        for (unsigned int i = 0; i < capacity; i++){
            if (keyset[i].size() > 0){
                std::cout << i << ": " << keyset[i] << std::endl;
            }
        }
    }

    friend std::ostream& operator<<(std::ostream &os, const HashMap<K, V> &c) {
        // Descricao: Overloading do operador << do ostream para realizar o output facil da estrutura.
        // Entrada: ostream and Collection.
        // Saida: os: std::ostream.
        bool first = false;
        os << '{';
        for (unsigned int i = 0; i < c.capacity; i++){
            for (int j = 0; j < c.keyset[i].size(); j++){
                if (!first){
                    first = true;
                    os << ' ';
                }
                else{
                    os << ", ";
                }
                os << c.keyset[i].get(j) << ": " << c.values[i].get(j);
            }
        }
        os << " }";
        return os;
    }

    inline int current_capacity() const {
        return this->capacity;
    }

};
#endif