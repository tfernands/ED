#ifndef COLLECTION_HPP
#define COLLECTION_HPP

template<class T>
class Collection {
    
    public:
    virtual ~Collection(){}
    virtual void add(T item) = 0;
    virtual void insert(int index, T item) = 0;
    virtual T& get(int index) = 0;
    virtual void set(int index, T item) = 0;
    virtual T pop() = 0;
    virtual T pop(int index) = 0;
    virtual int size() = 0;

    virtual bool remove(T item){
        int index = this->indexOf(item);
        if (index > -1){
            this->pop(index);
            return true;
        }
        return false;
    }

    virtual int indexOf(const T& item){
        for (int i = 0; i < this->size(); i++){
            if ((*this)[i] == item) return i;
        }
        return -1;
    }

    class Proxy{
        int index;
        Collection<T>&parent;
        public:
        Proxy(Collection<T>&p, int i) : parent(p), index(i){}
        virtual ~Proxy(){}
        void operator=(T assgn){
            parent.set(index, assgn);
        }
        operator T const &(){
            return parent.get(index);
        }
    };

    Proxy operator[](int index){
        return Proxy(*this, index);
    }

    friend std::ostream& operator<<(std::ostream &os, Collection<T> &c) {
        // Descricao: Overloading do operador << do ostream para realizar o output facil da estrutura.
        // Entrada: ostream and Collection.
        // Saida: os: std::ostream.
        os << '[';
        for (int i = 0; i < c.size(); i++){
            os << c[i];
            if (i < c.size()-1) os << ", ";
        }
        os << ']';
        return os;
    } 
    
};





#endif