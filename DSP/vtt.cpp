#include<iostream>
#include<algorithm>
#include<cstdlib>

using namespace std;

template <typename T>
class vector
{
private:
    T* data;
    size_t used, space;

public:
    // nested class: iterator
    class iterator
    {
    public:
        iterator(T* p = nullptr, size_t idx = 0): pv(p), pos(idx) {}
        ~iterator() {}

        iterator& operator++() {
            ++pv; ++pos; return *this;
        }
        
        iterator operator++(int) {
            iterator tmp = *this; ++(*this); return tmp;
        }

        iterator& operator--() {
            --pv; --pos; return *this;
        }
        
        iterator operator--(int) {
            iterator tmp = *this; --(*this); return tmp;
        }

        iterator operator+(size_t n) {
            return iterator(pv + n, pos + n);
        }

        iterator operator-(size_t n) {
            return iterator(pv - n, pos - n);
        }

        bool operator==(const iterator& it) const {
            return pv == it.pv;
        }

        bool operator!=(const iterator& it) const {
            return pv != it.pv;
        }

        T& operator*() { return *pv; }

        const T* operator->() const { return pv; }

    private:
        friend class vector;
        T* pv;
        size_t pos;
    };

    vector():used(0), space(5), data(new T[5]){}
    vector(int size);
    vector(const vector<T>& rhs);
    vector(vector<T>&& rhs);
    vector(const std::initializer_list<T>& lst);
    ~vector();

    vector& operator=(const vector& v);
    vector& operator=(vector&& rhs);
    T& operator[](int n);

    void push_back(const T& x);
    void push_back(const T&& x);
    void pop_back();

    size_t capacity() const;
    size_t size() const;
    bool is_empty() const;
    void clear();
    void resize(size_t n, const T& val = T());
    void reserve(size_t n);
    
    T& front();
    const T& front() const;
    T& back();
    const T& back() const;

    iterator begin();
    iterator end();
    iterator erase(const iterator& it);
    iterator erase(const iterator& sit, const iterator& eit);
    iterator insert(const iterator& it, const T& val);

    void swap(vector<T>& rhs);
};

// Constructor implementations
template <typename T>
vector<T>::vector(int size):used(size), space(size), data(new T[size]) {
    for(size_t i = 0; i < used; i++) {
        data[i] = T();
    }
}

template <typename T>
vector<T>::vector(const vector<T>& rhs):used(rhs.used), space(rhs.space), data(new T[rhs.space]) {
    copy(rhs.data, rhs.data + used, data);
}

template <typename T>
vector<T>::vector(vector<T>&& rhs):data(rhs.data), used(rhs.used), space(rhs.space) {
    rhs.data = nullptr;
    rhs.used = rhs.space = 0;
}

template <typename T>
vector<T>::vector(const std::initializer_list<T>& lst):used(lst.size()), space(lst.size()), data(new T[lst.size()]) {
    copy(lst.begin(), lst.end(), data);
}

template <typename T>
vector<T>::~vector() { delete[] data; }

template <typename T>
vector<T>& vector<T>::operator=(const vector& v) {
    if(this == &v) { return *this; }
    if(capacity() != v.capacity()) {
        delete[] data;
        data = new T[v.capacity()];
        space = v.capacity();
    }

    used = v.size();
    copy(v.data, v.data + used, data);
    return *this;
}

template <typename T>
vector<T>& vector<T>::operator=(vector&& rhs) {
    if(this != &rhs) {
        delete[] data;
        data = rhs.data;
        used = rhs.used;
        space = rhs.space;

        rhs.data = nullptr;
        rhs.used = rhs.space = 0;
    }
    return *this;
}

template <typename T>
T& vector<T>::operator[](int n) {
    if(n >= size()) {
        cout << "vector::operator[]: index " << n << " out of range\n";
        exit(EXIT_FAILURE);
    }
    return data[n];
}

template <typename T>
void vector<T>::push_back(const T& x) {
    if(used == capacity()) {
        reserve(size() * 2);
    }
    data[used++] = x;
}

template <typename T>
void vector<T>::push_back(const T&& x) {
    if(used == capacity()) {
        reserve(size() * 2);
    }
    data[used++] = move(x);
}

template <typename T>
void vector<T>::pop_back() {
    if(!is_empty()) {
        used--;
    }
}

template <typename T>
size_t vector<T>::capacity() const { return space; }

template <typename T>
size_t vector<T>::size() const { return used; }

template <typename T>
bool vector<T>::is_empty() const { return used == 0; }

template <typename T>
void vector<T>::clear() {
    used = 0;
    space = 5;
    delete[] data;
    data = new T[space];
}

template <typename T>
void vector<T>::resize(size_t n, const T& val) {
    if(n > used) {
        while(n > used) {
            push_back(val);
        }
    } else if(n < used) {
        used = n;
    }
}

template <typename T>
void vector<T>::reserve(size_t n) {
    if(n <= capacity()) { return; }
    if(n < size()) { n = size(); }

    T* temp = new T[n];
    copy(data, data + used, temp);
    delete[] data;
    data = temp;
    space = n;
}

template <typename T>
T& vector<T>::front() { return data[0]; }

template <typename T>
const T& vector<T>::front() const { return data[0]; }

template <typename T>
T& vector<T>::back() { return data[used - 1]; }

template <typename T>
const T& vector<T>::back() const { return data[used - 1]; }

template <typename T>
typename vector<T>::iterator vector<T>::begin() { return iterator(data, 0); }

template <typename T>
typename vector<T>::iterator vector<T>::end() { return iterator(data + used, used); }

template <typename T>
typename vector<T>::iterator vector<T>::erase(const iterator& it) {
    if(it.pv >= data && it.pv < data + used) {
        size_t pos = it.pv - data;
        copy(data + pos + 1, data + used, data + pos);
        --used;
    }
    return iterator(data, used);
}

template <typename T>
typename vector<T>::iterator vector<T>::erase(const iterator& sit, const iterator& eit) {
    size_t start = sit.pv - data;
    size_t end = eit.pv - data;
    copy(data + end, data + used, data + start);
    used -= (end - start);
    return iterator(data, used);
}

template <typename T>
typename vector<T>::iterator vector<T>::insert(const iterator& it, const T& val) {
    if(used == space) reserve(2 * space);
    size_t pos = it.pv - data;
    copy_backward(data + pos, data + used, data + used + 1);
    data[pos] = val;
    ++used;
    return iterator(data + pos, pos);
}

template <typename T>
void vector<T>::swap(vector<T>& rhs) {
    std::swap(data, rhs.data);
    std::swap(used, rhs.used);
    std::swap(space, rhs.space);
}

int main() {
    vector<int> v(3);
    vector<int>::iterator it;

    cout<<"size of v: "<<v.size()<<endl;
    cout<<"capacity of v: "<<v.capacity()<<endl;
    cout<<"elements of v: ";
    for(int i = 0; i < v.size(); i++) { cout<<v[i]<<" "; }
    cout<<endl<<endl;

    for(int i = 0; i < v.size(); i++) { v[i] = i + 1; }
    for(int i = 10; i < 15; i++) {
        v.push_back(i);
    }

    cout<<"--- After push_back ---"<<endl;
    cout<<"size of v: "<<v.size()<<endl;
    cout<<"capacity of v: "<<v.capacity()<<endl;
    cout<<"elements of v: ";
    for(it = v.begin(); it != v.end(); it++) { cout<<*it<<" "; }
    cout<<endl<<endl;

    v.pop_back();
    v.pop_back();

    cout<<"--- After pop_back ---"<<endl;
    cout<<"size of v: "<<v.size()<<endl;
    cout<<"capacity of v: "<<v.capacity()<<endl;
    cout<<"elements of v: ";
    for(it = v.begin(); it != v.end(); it++) { cout<<*it<<" "; }
    cout<<endl;

    return 0;
}