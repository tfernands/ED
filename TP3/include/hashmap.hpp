#ifndef HASHMAP_HPP
#define HASHMAP_HPP

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
        while(i < 1000){
            if (t[i] == '\0' || t[i] == '\n') break;
            sum += p[i%n]*t[i];
            i++;
        }
        return sum;
    }
};

template <class K, class V> class HashMap;

template <class K, class V>
class HashMap {

    private:
    unsigned int capacity;
    Hash<K> hash_function;
    LinkedList<K>* keyset;
    LinkedList<V>* values;

    unsigned int map(K key){
        return this->hash_function(key)%this->capacity;
    }

    public:
    HashMap(): HashMap(100){}; 
    HashMap(unsigned int capacity){
        this->capacity = capacity;
        this->keyset = new LinkedList<K>[this->capacity];
        this->values = new LinkedList<V>[this->capacity];
    }
    virtual ~HashMap(){
        delete[] this->keyset;
        delete[] this->values;
    }

    int colisions(){
        unsigned int colisions = 0;
        for (int i = 0; i < this->capacity; i++){
            if (this->keyset->size() > 0){
                colisions += this->keyset->size()-1;
            }
        }
    }

    void put(K key, V value){
        unsigned int hashmap = this->map(key);
        unsigned int index = this->keyset[hashmap].indexOf(key);
        if (index > -1){
            this->keyset->pop(index);
            this->values->pop(index);
        }
        this->keyset->add(key);
        this->values->add(value);
    }

    V& get(K key){
        unsigned int hashmap = this->map(key);
        unsigned int index = this->keyset[hashmap].indexOf(key);
        if (index > -1){
            return this->values[hashmap][index];
        }
    }

    V del(K key){
        unsigned int hashmap = this->map(key);
        unsigned int index = this->keyset[hashmap].indexOf(key);
        if (index > -1){
            this->keyset->pop(index);
            return this->values[hashmap].pop(index);
        }
    }

    friend std::ostream& operator<<(std::ostream &os, HashMap<K, V> &c) {
        // Descricao: Overloading do operador << do ostream para realizar o output facil da estrutura.
        // Entrada: ostream and Collection.
        // Saida: os: std::ostream.
        os << '{' << std::endl;
        for (int i = 0; i < c.capacity; i++){
            for (int j = 0; j < c.keyset->size(); j++){
                os << c.keyset[i][j] << ": " << c.values[i][j] << std::endl;
            }
        }
        os << '}';
        return os;
    }

    class HashProxy{
        K key;
        HashMap<K, V>&parent;
        public:
        HashProxy(HashMap<K, V>&p, K k) : parent(p), key(k){}
        virtual ~HashProxy(){}
        void operator=(V assgn){
            parent.put(key, assgn);
        }
        operator V const &(){
            return parent.get(key);
        }
    };
    HashProxy operator[](K key){
        return HashProxy(*this, key);
    }

};
#endif