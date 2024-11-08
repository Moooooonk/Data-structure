#include<iostream>
#include<algorithm>
#include<cstdlib>  
#include<iterator>

using namespace std;

class vector
{
private:
    int* data;
    size_t used, space;
    using iterator = int*;
public:
    vector():used(0), space(5), data(new int[5]){}
    vector(int size);
    ~vector();

    vector& operator=(const vector& v);
    int& operator[](int n);
    void operator()(int n);

    void push_back(int x);
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

vector::vector(int size):used(size), space(size), data(new int[size]) {
    for(size_t i = 0; i < used; i++) {
        data[i] = int();
    }
}

vector::~vector() { delete[] data; }

vector& vector::operator=(const vector& v) {
    if(this == &v) {return *this;}
    if(capacity() != v.capacity()) {
        delete[] data;
        data = new int[v.capacity()];
        space = v.capacity();
    }

    used = v.size();
    copy(v.data, v.data + used, data);
    return *this;
}

int& vector::operator[](int n) {
    if(n >= size()) {
        cout<<"vector::operator[]: index "<< n << " out of range\n";
    }
    return data[n];
}

void vector::push_back(int x) {
    if(used == capacity()) {
        reserve(size()*2);
    }
    data[used++] = x;
}

void vector::pop_back() { if(!is_empty()) { used--; } }

size_t vector::capacity() const { return space; }

size_t vector::size() const { return used; }

void vector::reserve(size_t n) {
    if(n <= capacity()) { return; }
    if(n < size()) { n = size(); }
    
    int* temp = new int[n];
    copy(data, data + used, temp);
    delete[] data;
    data = temp;
    space = n;
}

bool vector::is_empty() const { 
    return used == 0;
}

void vector::clear() { 
    used = 0; 
    space = 5;
    delete[] data;
    data = new int[space];
}

void vector::resize(size_t n) {
    if(n > used) {
        while(n > used) { 
            push_back(int()); 
        } 
    }
    else if(n < used) { used = n; }
}

typename vector::iterator vector::begin() { return data; }

typename vector::iterator vector::end() { return data + used; }

int main() {
    vector v(3);
    vector::iterator it;

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