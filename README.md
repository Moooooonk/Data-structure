# Data-structure

1. Bag Class 과제 제출 안내
제출 기한: 10/15 23:59

구현 사항
아래 설명에 따라 Bag 클래스를 bag.h와 bag.cpp 파일로 나눠서 구현하세요.

1. Bag 클래스:

필드:
items: 템플릿 타입 T를 저장하는 std::vector<T> 타입의 리스트로, Bag에 저장된 모든 아이템을 관리.

메서드:
add(T item): Bag에 item을 추가하는 메서드.  
반환값 없음.

remove(T item): Bag에서 주어진 item을 삭제하는 메서드.
성공적으로 삭제했으면 true, 해당 item이 존재하지 않으면 false를 반환.

contains(T item): Bag 안에 주어진 item이 존재하는지 확인하는 메서드.
존재하면 true, 존재하지 않으면 false를 반환.

size():
Bag에 있는 아이템의 개수를 반환하는 메서드.
반환 타입은 int.

isEmpty():
Bag이 비어있는지 확인하는 메서드.
비어있으면 true, 아니면 false를 반환.

printItems():
Bag에 있는 모든 아이템을 출력하는 메서드.
출력 형태는 각 아이템을 공백으로 구분하여 한 줄로 출력합니다.

유효하지 않은 입력 처리
remove() 메서드에서 Bag 안에 존재하지 않는 아이템을 삭제하려고 할 경우, 아무런 변화 없이 false를 반환합니다.
추가 기능 및 요구 사항:
Bag 클래스는 템플릿 클래스로 작성해야 합니다. 즉, 정수, 문자열, 또는 사용자 정의 객체 등 다양한 타입의 데이터를 저장할 수 있어야 합니다.
템플릿 사용: 템플릿을 이용하여 Bag 클래스가 어떤 타입의 데이터든 처리할 수 있게 해야 합니다. 템플릿 매개변수 T를 사용하여 클래스를 정의하세요.
main.cpp 파일에서 아래의 동작을 확인할 수 있는 테스트 코드를 작성하세요:
int 타입을 사용하는 Bag을 생성하고 add, remove, contains, size, printItems 등의 메서드를 테스트.
최소 3개의 아이템을 추가하고, 하나를 제거한 후에 리스트를 출력하세요.
보고서 작성:
REPORT.md 파일에 본인이 구현한 Bag 클래스와 메서드가 각각 어떻게 작동하는지 설명하세요.
ChatGPT 또는 다른 AI 도구를 활용한 경우, 그 방법과 어떤 부분에서 도움을 받았는지 상세하게 작성하세요.

2. Linked lists

3. TIS(Templates, Iterators, and the STL)
