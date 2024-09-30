# Data-structure

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

2. LinkedList Class 

구현 사항
LinkedList 클래스를 LinkedList.h와 LinkedList.cpp 파일로 나누어 구현하세요.

필드:
Node<T>* head: 리스트의 첫 번째 노드를 가리키는 포인터. 리스트가 비어 있을 경우 nullptr이 되어야 함.
Node 구조체:
T data: 노드가 저장하는 값.
Node<T>* next: 다음 노드를 가리키는 포인터.
Node 생성자를 통해 값을 초기화하고, next는 nullptr로 설정.
메서드:
insertFront(T value):
리스트의 앞쪽에 새로운 값을 가진 노드를 삽입하는 메서드.
반환값 없음.

insertBack(T value):
리스트의 끝에 새로운 값을 가진 노드를 삽입하는 메서드.
반환값 없음.

remove(T value):
리스트에서 특정 값을 가진 첫 번째 노드를 삭제하는 메서드.
성공적으로 삭제되면 true, 값이 리스트에 없으면 false를 반환.

search(T value):
리스트에서 특정 값을 가진 노드를 찾는 메서드.
값이 존재하면 true, 없으면 false를 반환.

size():
리스트에 있는 노드의 개수를 반환하는 메서드.
반환 타입은 int.

isEmpty():
리스트가 비어 있는지 확인하는 메서드.
비어 있으면 true, 아니면 false를 반환.

printList():
리스트에 있는 모든 노드를 출력하는 메서드.
각 노드를 '->'로 연결하여 출력하며, 리스트의 마지막 노드 뒤에는 nullptr을 출력해야 합니다.

소멸자:
~LinkedList(): 리스트의 모든 노드를 삭제하여 메모리를 해제하는 소멸자.
유효하지 않은 입력 처리
remove() 메서드에서 리스트에 없는 값을 삭제하려고 할 경우, 아무런 변화 없이 false를 반환합니다.
추가 기능 및 요구 사항:
LinkedList 클래스는 템플릿 클래스로 작성해야 합니다. 즉, 정수, 문자열, 사용자 정의 객체 등 다양한 타입의 데이터를 저장할 수 있어야 합니다.
템플릿 사용: 템플릿을 이용하여 LinkedList 클래스가 어떤 타입의 데이터든 처리할 수 있게 해야 합니다. 템플릿 매개변수 T를 사용하여 클래스를 정의하세요.
main.cpp 파일에서 아래의 동작을 확인할 수 있는 테스트 코드를 작성하세요:
int 타입을 사용하는 리스트를 생성하고 insertFront, insertBack, remove, search, printList 등의 메서드를 테스트.
최소 3개의 노드를 추가하고, 하나를 제거한 후 리스트를 출력하세요.
빈 리스트 상태에서의 remove, search 메서드를 테스트하세요.
보고서 작성:
REPORT.md 파일에 본인이 구현한 LinkedList 클래스와 각 메서드가 어떻게 동작하는지 설명하세요.
ChatGPT 또는 다른 AI 도구를 활용한 경우, 그 방법과 어떤 부분에서 도움을 받았는지 상세하게 작성하세요.
제출 및 테스트 방법:
LinkedList.h, LinkedList.cpp, 그리고 main.cpp 파일을 프로젝트에 작성하세요.
main() 함수에서 다양한 테스트 케이스를 만들어 직접 실행하여 올바르게 동작하는지 확인하세요.
git을 이용한 제출:
git add [파일명], git commit -m [커밋 메시지], git push 명령어를 차례대로 실행하여 과제를 제출하세요.
git push로 제출한 후, GitHub Actions를 통해 제출한 코드가 테스트됩니다.
제출 후 본인의 GitHub 리포지토리에서 테스트 결과를 확인하세요.
과제를 제출할 때 코드가 올바르게 동작하고, 제출 기한을 엄수하세요!

Good luck!

3. TIS(Templates, Iterators, and the STL)
