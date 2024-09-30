#include <iostream>
#include <vector>
#include <algorithm> // for std::find

template <typename T>
class Bag {
private:
    std::vector<T> items;

public:
    // Bag에 아이템 추가
    void add(const T& item) {
        items.push_back(item);
    }

    // Bag에서 특정 아이템 제거
    bool remove(const T& item) {
        auto it = std::find(items.begin(), items.end(), item);
        if (it != items.end()) {
            items.erase(it);
            return true;
        }
        return false;
    }

    // Bag에서 특정 아이템 존재 여부 확인
    bool contains(const T& item) const {
        return std::find(items.begin(), items.end(), item) != items.end();
    }

    // Bag의 사이즈 반환
    int size() const {
        return items.size();
    }

    // Bag이 비어 있는지 확인
    bool isEmpty() const {
        return items.empty();
    }

    // Bag의 모든 아이템 출력
    void printItems() const {
        for (const auto& item : items) {
            std::cout << item << " ";
        }
        std::cout << std::endl;
    }
};

int main() {
    Bag<int> intBag;
    intBag.add(5);
    intBag.add(10);
    intBag.add(15);
    
    std::cout << "Bag contains: ";
    intBag.printItems();

    std::cout << "Bag size: " << intBag.size() << std::endl;
    std::cout << "Removing 10 from the bag..." << std::endl;
    intBag.remove(10);

    std::cout << "Bag contains: ";
    intBag.printItems();
    std::cout << "Bag size: " << intBag.size() << std::endl;

    return 0;
}
