#include <iostream>  // 입출력 스트림 사용을 위한 헤더
#include <vector>    // 동적 배열인 std::vector를 사용하기 위한 헤더
#include <algorithm> // std::find 함수를 사용하기 위한 헤더

// 템플릿 클래스로 Bag 선언, 여러 타입의 데이터를 다룰 수 있도록 함
template <typename T>
class Bag {
private:
    std::vector<T> items; // Bag에 저장되는 아이템들을 담는 동적 배열 (vector)

public:
    // Bag에 아이템을 추가하는 메서드
    void add(const T& item) {
        items.push_back(item); // vector의 push_back을 사용하여 item을 추가
    }

    // Bag에서 특정 아이템을 제거하는 메서드
    bool remove(const T& item) {
        // std::find를 사용해 vector에서 해당 item을 찾음
        auto it = std::find(items.begin(), items.end(), item);
        // 아이템을 찾았으면 삭제
        if (it != items.end()) {
            items.erase(it); // vector에서 해당 위치의 아이템을 제거
            return true;     // 삭제 성공 시 true 반환
        }
        return false;        // 아이템이 없을 경우 false 반환
    }

    // Bag에서 특정 아이템이 존재하는지 확인하는 메서드
    bool contains(const T& item) const {
        // std::find를 사용하여 item이 존재하는지 확인
        return std::find(items.begin(), items.end(), item) != items.end();
    }

    // Bag에 있는 아이템 개수를 반환하는 메서드
    int size() const {
        return items.size(); // vector의 크기(size)를 반환
    }

    // Bag이 비어 있는지 확인하는 메서드
    bool isEmpty() const {
        return items.empty(); // vector가 비어 있으면 true, 아니면 false 반환
    }

    // Bag에 저장된 모든 아이템을 출력하는 메서드
    void printItems() const {
        // vector의 모든 요소를 순회하며 출력
        for (const auto& item : items) {
            std::cout << item << " "; // 각 아이템을 공백으로 구분하여 출력
        }
        std::cout << std::endl; // 출력이 끝나면 줄바꿈
    }
};

// main 함수: Bag 클래스의 동작을 테스트하는 함수
int main() {
    Bag<int> intBag; // 정수형(int)을 저장하는 Bag 객체 생성
    intBag.add(5);   // Bag에 5 추가
    intBag.add(10);  // Bag에 10 추가
    intBag.add(15);  // Bag에 15 추가
    
    // Bag의 현재 상태를 출력
    std::cout << "Bag contains: ";
    intBag.printItems(); // Bag에 저장된 아이템 출력

    // Bag의 크기를 출력
    std::cout << "Bag size: " << intBag.size() << std::endl;

    // Bag에서 10을 제거
    std::cout << "Removing 10 from the bag..." << std::endl;
    intBag.remove(10);

    // 10을 제거한 후의 Bag 상태 출력
    std::cout << "Bag contains: ";
    intBag.printItems(); // Bag에 저장된 아이템 출력

    // Bag의 크기를 다시 출력
    std::cout << "Bag size: " << intBag.size() << std::endl;

    return 0; // 프로그램 정상 종료
}
