#include <iostream>
#include <memory>  // for std::allocator
#include <stdexcept>  // for std::out_of_range

template <typename T>
class Vector {
private:
    T* data;               // 동적 배열을 가리킬 포인터
    size_t _size;          // 현재 벡터에 들어 있는 요소의 개수
    size_t _capacity;      // 현재 배열의 용량
    std::allocator<T> alloc; // 메모리 할당자

    // 크기를 증가시키는 메서드
    void reallocate(size_t new_capacity) {
        T* new_data = alloc.allocate(new_capacity); // 새 메모리 할당

        // 기존 요소들을 이동하거나 복사
        for (size_t i = 0; i < _size; ++i) {
            alloc.construct(new_data + i, std::move(data[i]));
            alloc.destroy(data + i); // 기존 요소 제거
        }

        // 이전 메모리 해제
        alloc.deallocate(data, _capacity);

        data = new_data;
        _capacity = new_capacity;
    }

public:
    // 기본 생성자
    Vector() : data(nullptr), _size(0), _capacity(0) {}

    // 복사 생성자
    Vector(const Vector& other) : _size(other._size), _capacity(other._capacity) {
        data = alloc.allocate(_capacity);
        for (size_t i = 0; i < _size; ++i) {
            alloc.construct(data + i, other.data[i]);
        }
    }

    // 이동 생성자
    Vector(Vector&& other) noexcept : data(other.data), _size(other._size), _capacity(other._capacity) {
        other.data = nullptr;
        other._size = 0;
        other._capacity = 0;
    }

    // 소멸자
    ~Vector() {
        for (size_t i = 0; i < _size; ++i) {
            alloc.destroy(data + i); // 요소 제거
        }
        alloc.deallocate(data, _capacity); // 메모리 해제
    }

    // 요소 추가
    void push_back(const T& value) {
        if (_size == _capacity) {
            reallocate(_capacity == 0 ? 1 : _capacity * 2);
        }
        alloc.construct(data + _size, value);
        ++_size;
    }

    // 요소 추가 (이동)
    void push_back(T&& value) {
        if (_size == _capacity) {
            reallocate(_capacity == 0 ? 1 : _capacity * 2);
        }
        alloc.construct(data + _size, std::move(value));
        ++_size;
    }

    // 요소 제거
    void pop_back() {
        if (_size > 0) {
            alloc.destroy(data + _size - 1);
            --_size;
        } else {
            throw std::out_of_range("Vector is empty");
        }
    }

    // 크기 반환
    size_t size() const {
        return _size;
    }

    // 용량 반환
    size_t capacity() const {
        return _capacity;
    }

    // 용량 예약
    void reserve(size_t new_capacity) {
        if (new_capacity > _capacity) {
            reallocate(new_capacity);
        }
    }

    // 크기 변경
    void resize(size_t new_size, const T& value = T()) {
        if (new_size > _capacity) {
            reallocate(new_size);
        }
        for (size_t i = _size; i < new_size; ++i) {
            alloc.construct(data + i, value);
        }
        for (size_t i = new_size; i < _size; ++i) {
            alloc.destroy(data + i);
        }
        _size = new_size;
    }

    // 요소 접근
    T& operator[](size_t index) {
        return data[index];
    }

    const T& operator[](size_t index) const {
        return data[index];
    }

    // 범위 검사 포함 접근
    T& at(size_t index) {
        if (index >= _size) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    const T& at(size_t index) const {
        if (index >= _size) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    // 복사 대입 연산자
    Vector& operator=(const Vector& other) {
        if (this == &other) return *this;

        // 기존 데이터 삭제
        for (size_t i = 0; i < _size; ++i) {
            alloc.destroy(data + i);
        }
        alloc.deallocate(data, _capacity);

        // 새로운 데이터 복사
        _size = other._size;
        _capacity = other._capacity;
        data = alloc.allocate(_capacity);
        for (size_t i = 0; i < _size; ++i) {
            alloc.construct(data + i, other.data[i]);
        }

        return *this;
    }

    // 이동 대입 연산자
    Vector& operator=(Vector&& other) noexcept {
        if (this == &other) return *this;

        // 기존 데이터 삭제
        for (size_t i = 0; i < _size; ++i) {
            alloc.destroy(data + i);
        }
        alloc.deallocate(data, _capacity);

        // 새로운 데이터 이동
        data = other.data;
        _size = other._size;
        _capacity = other._capacity;

        other.data = nullptr;
        other._size = 0;
        other._capacity = 0;

        return *this;
    }
};

int main() {
    Vector<int> vec;

    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);

    std::cout << "Vector elements: ";
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "Vector size: " << vec.size() << std::endl;
    std::cout << "Vector capacity: " << vec.capacity() << std::endl;

    vec.pop_back();

    std::cout << "After pop_back, size: " << vec.size() << std::endl;

    return 0;
}
