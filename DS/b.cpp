#include<iostream>

using namespace std;

class bag {

    int* data;
    int capacity;
    int size;
    int used;


    public:
        bag();
        void insert(int item);        
        void resize();

};

bag::bag() {


}

void bag:: resize() {

    int* temp = new int[capacity*2];
    for(int i = 0; i < size; i++) {
        temp[i] = data[i];
    }
    delete[] data;
    data = temp;
    capacity = capacity*2;
}
int main() {

    return 0;
}