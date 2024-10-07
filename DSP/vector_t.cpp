#include<iostream>
#include<algorithm>
#include<cstdlib>
#include<iterator>

using namespace std;

template <class T>
class vector
{
private:
    T* data;
    size_t used, space;
    using iterator = T*;
public:
    vector():used(0), space(5), data(new T[5]){}
    vector(int size);
    ~vector();

    vector& operator=(const vector& v);
    T& operator[](int n);
    void operator()(int n);

    void push_back(T x);
    void pop_back();

    size_t capacity() const;
    size_t size() const;

    void reserve(size_t n);
    bool is_empty() const;
    void clear();
    void resize(size_t n);

    iterator begin();
    iterator end();
};

template <class T>
vector<T>::vector(int size):used(size), space(size), data(new T[size]) {
    for(size_t i = 0; i < used; i++) {
        data[i] = T();
    }
}

template <class T>
vector<T>::~vector() { delete[] data; }

template <class T>
vector<T>& vector<T>::operator=(const vector& v) {
    if(this == &v) {return *this;}
    if(capacity() != v.capacity()) {
        delete[] data;
        data = new T[v.capacity()];
        space = v.capacity();
    }

    used = v.size();
    copy(v.data, v.data + used, data);
    return *this;
}

template <class T>
T& vector<T>::operator[](int n) {
    if(n >= size()) {
        cout<<"vector::operator[]: index "<< n << " out of range\n";
        exit(1);  // 범위를 벗어난 경우 오류 종료
    }
    return data[n];
}

template <class T>
void vector<T>::push_back(T x) {
    if(used == capacity()) {
        reserve(size()*2);
    }
    data[used++] = x;
}

template <class T>
void vector<T>::pop_back() { if(!is_empty()) { used--; } }

template <class T>
size_t vector<T>::capacity() const { return space; }

template <class T>
size_t vector<T>::size() const { return used; }

template <class T>
void vector<T>::reserve(size_t n) {
    if(n <= capacity()) { return; }
    if(n < size()) { n = size(); }
    
    T* temp = new T[n];
    copy(data, data + used, temp);
    delete[] data;
    data = temp;
    space = n;
}

template <class T>
bool vector<T>::is_empty() const { 
    return used == 0; 
}

template <class T>
void vector<T>::clear() { 
    used = 0; 
    space = 5;
    delete[] data;
    data = new T[space];
}

template <class T>
void vector<T>::resize(size_t n) {
    if(n > used) {
        while(n > used) { 
            push_back(T()); 
        } 
    }
    else if(n < used) { used = n; }
}

template <class T>
typename vector<T>::iterator vector<T>::begin() { return data; }

template <class T>
typename vector<T>::iterator vector<T>::end() { return data + used; }

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
