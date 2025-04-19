#include <iostream>
#define ENDL '\n'

using namespace std;

#pragma region SimplyLinkedList
template <typename T>
class Node {
public:
    Node<T> *link;
    T value;

    Node(T val) { 
        this->value = val; 
        this->link = nullptr; 
    }
};

template <typename T>
class SimplyLinkedList {
private:
    Node<T> *head;
public:
    SimplyLinkedList();
    ~SimplyLinkedList();
    bool isEmpty();
    void Insert(Node<T>* before, Node<T>* node);
    void Delete(Node<T>* before);
    Node<T>* Search(T value);  // 교수님이 수업 중에 구현 파트는 언급 안 했음.
    void Update();  // 교수님이 수업 중에 구현 파티는 언급 안 했음.
    void Print();
};

template <typename T>
SimplyLinkedList<T>::SimplyLinkedList()
{
    this->head = nullptr;
}

template <typename T>
SimplyLinkedList<T>::~SimplyLinkedList()
{
    cout << ENDL;
    while(this->head != nullptr) {
        Node<T>* removed = this->head;
        this->head = removed->link;
        cout << "Deleting : " << removed->value << ENDL;
        
        delete removed;
    }
}

template <typename T>
bool SimplyLinkedList<T>::isEmpty()
{
    return this->head == nullptr;
}

template <typename T>
void SimplyLinkedList<T>::Insert(Node<T>* before, Node<T>* node)
{
    if(isEmpty() && before == nullptr) this->head = node;
    else {
        node->link = before->link;
        before->link = node;
    }
}

template <typename T>
void SimplyLinkedList<T>::Delete(Node<T>* before)
{
    if(isEmpty()) return ;

    Node<T>* removed;
    removed = before->link;
    before->link = removed->link;
    delete(removed);
}

template <typename T>
Node<T>* SimplyLinkedList<T>::Search(T value)
{
    // TODO : 얜 뭐하는 애냐?? 교수님 스타일을 알 수가 없음
    Node<T>* cur = this->head;

    while(cur != nullptr) {
        if(cur->value == value) return cur;
        cur = cur->link;
    }
    return nullptr;
}

template <typename T>
void SimplyLinkedList<T>::Update()
{
    // TODO : 얜 뭐하는 애냐?? 교수님 스타일을 알 수가 없음
}

template <typename T>
void SimplyLinkedList<T>::Print()
{
    Node<T>* cur = this->head;
    cout << "[ ";
    while(cur != nullptr) {
        cout << cur->value;
        cur = cur->link;

        if(cur != nullptr) cout << " -> ";
    }
    cout << " ]" << ENDL;
}

#pragma endregion

int main() {
    // 단일연결리스트 생성
    SimplyLinkedList<char> *ls = new SimplyLinkedList<char>();

    // A 노드 생성 후 리스트에 삽입
    Node<char>* node1 = new Node<char>('A');
    ls->Insert(nullptr, node1);
    
    // A 노드를 탐색 후 A 노드 뒤에 B 삽입 [A -> B]
    Node<char>* finder = nullptr;
    finder = ls->Search('A');
    Node<char>* node2 = new Node<char>('B');
    ls->Insert(finder, node2);

    // A 노드를 탐색 후 A 노드 뒤에 C 삽입 [A -> C -> B]
    finder = ls->Search('A');
    Node<char>* node3 = new Node<char>('C');
    ls->Insert(finder, node3);

    // B 노드를 탐색 후 B 노드 뒤에 D 삽입 [A -> C -> B -> D]
    finder = ls->Search('B');
    Node<char>* node4 = new Node<char>('D');
    ls->Insert(finder, node4);

    // C 노드를 탐색 후 C 노드 뒤의 노드(B) 삭제 [A -> C -> D]
    finder = ls->Search('C');
    ls->Delete(finder);

    // 리스트 출력
    ls->Print();

    delete ls;
}