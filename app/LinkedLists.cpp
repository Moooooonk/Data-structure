#include <iostream>

// 노드 구조체
template <typename T>
struct Node {
    T data;
    Node* next;

    // 노드 생성자
    Node(T value) : data(value), next(nullptr) {}
};

// LinkedList 클래스
template <typename T>
class LinkedList {
private:
    Node<T>* head;  // 리스트의 첫 번째 노드

public:
    // 생성자: 리스트 초기화
    LinkedList() : head(nullptr) {}

    // 소멸자: 메모리 해제
    ~LinkedList() {
        Node<T>* current = head;
        while (current != nullptr) {
            Node<T>* nextNode = current->next;
            delete current;
            current = nextNode;
        }
    }

    // 리스트의 앞에 노드 추가
    void insertFront(T value) {
        Node<T>* newNode = new Node<T>(value);
        newNode->next = head;
        head = newNode;
    }

    // 리스트의 끝에 노드 추가
    void insertBack(T value) {
        Node<T>* newNode = new Node<T>(value);
        if (head == nullptr) {
            head = newNode;
        } else {
            Node<T>* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newNode;
        }
    }

    // 리스트에서 특정 값을 가진 노드 삭제
    bool remove(T value) {
        if (head == nullptr) return false;

        if (head->data == value) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
            return true;
        }

        Node<T>* current = head;
        while (current->next != nullptr && current->next->data != value) {
            current = current->next;
        }

        if (current->next == nullptr) {
            return false; // 해당 값이 리스트에 없음
        } else {
            Node<T>* temp = current->next;
            current->next = temp->next;
            delete temp;
            return true;
        }
    }

    // 리스트에서 특정 값 찾기
    bool search(T value) const {
        Node<T>* current = head;
        while (current != nullptr) {
            if (current->data == value) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    // 리스트 출력
    void printList() const {
        Node<T>* current = head;
        while (current != nullptr) {
            std::cout << current->data << " -> ";
            current = current->next;
        }
        std::cout << "nullptr" << std::endl;
    }

    // 리스트가 비었는지 확인
    bool isEmpty() const {
        return head == nullptr;
    }
};

int main() {
    LinkedList<int> list;
    
    list.insertBack(10);
    list.insertBack(20);
    list.insertFront(5);
    
    std::cout << "Current List: ";
    list.printList();

    std::cout << "Removing 20..." << std::endl;
    list.remove(20);
    list.printList();

    std::cout << "Searching for 10: " << (list.search(10) ? "Found" : "Not Found") << std::endl;

    return 0;
}
