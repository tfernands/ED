#ifndef COLLECTION_HPP
#define COLLECTION_HPP

template<class T>
class Collection {

    private:

    class Proxy{
        int index;
        Collection<T> &parent;
        public:
        Proxy(Collection<T>&p, int i): index(i), parent(p){}
        virtual ~Proxy(){}
        inline void operator=(const T& item){
            parent.set(index, item);
        }
        inline operator T&() const {
            return parent.get(index);
        }
    };

    public:
    virtual ~Collection(){}
    virtual void add(const T& item) = 0;
    virtual void insert(int index, const T& item) = 0;
    virtual T& get(int index) const = 0;
    virtual void set(int index, const T& item) = 0;
    virtual T pop() = 0;
    virtual T pop(int index) = 0;
    virtual int size() const = 0;
    virtual void clear() = 0;

    virtual bool remove(T item){
        int index = this->indexOf(item);
        if (index > -1){
            this->pop(index);
            return true;
        }
        return false;
    }

    virtual int indexOf(const T& item) const {
        for (int i = 0; i < this->size(); i++){
            if (this->get(i) == item) return i;
        }
        return -1;
    }

    Proxy operator[](int index){
        return Proxy(*this, index);
    }

    bool operator==(const Collection &collection) const {
        if (size() == collection.size()){
            for (int i = 0; i < size(); i++){
                if (get(i) != collection.get(i)) return false;
            }
            return true;
        }
        return false;
    }

    friend std::ostream& operator<<(std::ostream &os, const Collection<T> &c) {
        // Descricao: Overloading do operador << do ostream para realizar o output facil da estrutura.
        // Entrada: ostream and Collection.
        // Saida: os: std::ostream.
        os << '[';
        for (int i = 0; i < c.size(); i++){
            os << c.get(i);
            if (i < c.size()-1) os << ", ";
        }
        os << ']';
        return os;
    } 

};





#endif