#include <iostream>  // 표준 입출력 라이브러리

// 노드 구조체 정의 (LinkedList의 각 요소를 나타냄)
template <typename T>
struct Node {
    T data;           // 노드가 저장하는 데이터
    Node* next;       // 다음 노드를 가리키는 포인터

    // 노드의 생성자, 값을 초기화하고 다음 노드를 nullptr로 설정
    Node(T value) : data(value), next(nullptr) {}
};

// LinkedList 클래스 정의
template <typename T>
class LinkedList {
private:
    Node<T>* head;  // 리스트의 첫 번째 노드를 가리키는 포인터

public:
    // 생성자: LinkedList를 빈 상태로 초기화
    LinkedList() : head(nullptr) {}

    // 소멸자: 리스트가 삭제될 때 동적으로 할당된 모든 노드를 삭제하여 메모리 해제
    ~LinkedList() {
        Node<T>* current = head;  // 현재 노드를 가리키는 포인터
        while (current != nullptr) {  // 리스트의 끝까지 반복
            Node<T>* nextNode = current->next;  // 현재 노드의 다음 노드를 저장
            delete current;  // 현재 노드를 삭제
            current = nextNode;  // 다음 노드로 이동
        }
    }

    // 리스트의 앞쪽에 새로운 노드를 추가하는 메서드
    void insertFront(T value) {
        Node<T>* newNode = new Node<T>(value);  // 새로운 노드를 동적으로 생성
        newNode->next = head;  // 새로운 노드의 다음 노드를 현재 head로 설정
        head = newNode;  // head를 새로운 노드로 갱신 (리스트의 앞에 삽입)
    }

    // 리스트의 끝에 새로운 노드를 추가하는 메서드
    void insertBack(T value) {
        Node<T>* newNode = new Node<T>(value);  // 새로운 노드를 동적으로 생성
        if (head == nullptr) {  // 리스트가 비어있을 경우
            head = newNode;  // 새로운 노드를 head로 설정 (첫 노드로 삽입)
        } else {
            Node<T>* current = head;  // 리스트의 끝까지 순회하기 위한 포인터
            while (current->next != nullptr) {  // 마지막 노드까지 이동
                current = current->next;
            }
            current->next = newNode;  // 마지막 노드의 다음 노드로 새로운 노드를 연결
        }
    }

    // 리스트에서 특정 값을 가진 첫 번째 노드를 삭제하는 메서드
    bool remove(T value) {
        if (head == nullptr) return false;  // 리스트가 비어있으면 false 반환

        // 첫 번째 노드가 삭제할 값일 경우
        if (head->data == value) {
            Node<T>* temp = head;  // 삭제할 노드를 임시 포인터로 저장
            head = head->next;     // head를 다음 노드로 이동
            delete temp;           // 첫 번째 노드 삭제
            return true;           // 삭제 성공 시 true 반환
        }

        // 첫 번째 노드가 아닌 경우, 리스트를 순회하며 값을 찾음
        Node<T>* current = head;  // 현재 노드를 가리키는 포인터
        while (current->next != nullptr && current->next->data != value) {
            current = current->next;  // 삭제할 값이 나올 때까지 다음 노드로 이동
        }

        if (current->next == nullptr) {
            return false;  // 값을 찾지 못했으면 false 반환
        } else {
            Node<T>* temp = current->next;  // 삭제할 노드를 임시 포인터로 저장
            current->next = temp->next;     // 삭제할 노드의 다음 노드를 연결
            delete temp;                    // 삭제할 노드 메모리 해제
            return true;                    // 삭제 성공 시 true 반환
        }
    }

    // 리스트에서 특정 값을 가진 노드가 있는지 검색하는 메서드
    bool search(T value) const {
        Node<T>* current = head;  // 리스트를 순회할 포인터
        while (current != nullptr) {  // 리스트 끝까지 반복
            if (current->data == value) {  // 값을 찾으면 true 반환
                return true;
            }
            current = current->next;  // 다음 노드로 이동
        }
        return false;  // 값을 찾지 못하면 false 반환
    }

    // 리스트에 저장된 모든 노드를 출력하는 메서드
    void printList() const {
        Node<T>* current = head;  // 리스트를 순회할 포인터
        while (current != nullptr) {  // 리스트 끝까지 반복
            std::cout << current->data << " -> ";  // 현재 노드의 데이터를 출력
            current = current->next;  // 다음 노드로 이동
        }
        std::cout << "nullptr" << std::endl;  // 마지막에 nullptr을 출력하여 리스트 끝을 나타냄
    }

    // 리스트가 비어있는지 확인하는 메서드
    bool isEmpty() const {
        return head == nullptr;  // head가 nullptr이면 리스트가 비어있음을 의미
    }
};

int main() {
    LinkedList<int> list;  // int 타입을 저장하는 LinkedList 인스턴스 생성
    
    // 리스트의 끝에 10, 20을 추가
    list.insertBack(10);
    list.insertBack(20);
    
    // 리스트의 앞에 5를 추가
    list.insertFront(5);
    
    // 현재 리스트의 모든 요소를 출력
    std::cout << "Current List: ";
    list.printList();

    // 리스트에서 20을 제거
    std::cout << "Removing 20..." << std::endl;
    list.remove(20);
    
    // 20을 제거한 후 리스트 출력
    list.printList();

    // 리스트에서 10을 검색
    std::cout << "Searching for 10: " << (list.search(10) ? "Found" : "Not Found") << std::endl;

    return 0;  // 프로그램 정상 종료
}
