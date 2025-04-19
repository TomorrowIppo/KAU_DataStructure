#include <iostream>
#define ENDL '\n'

using namespace std;

#pragma region DoublyLinkedList
template <typename T>
class Node {
public:
    Node<T>* prev;
    Node<T>* next;
    T value;

    Node(T val) { 
        this->value = val; 
        this->prev = nullptr; 
        this->next = nullptr; 
    }
};

template <typename T>
class DoublyLinkedList {
private:
    Node<T>* head;
public:
    DoublyLinkedList();
    ~DoublyLinkedList();
    bool isEmpty();
    void Insert(Node<T>* before, Node<T>* node);
    void Delete(Node<T>* node);
    Node<T>* Search(T value);  // 교수님이 수업 중에 구현 파트는 언급 안 했음.
    void Update();  // 교수님이 수업 중에 구현 파트는 언급 안 했음.
    void Print();
};

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList()
{
    this->head = nullptr;
}

template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList()
{
    cout << ENDL;
    while(this->head != nullptr) {
        Node<T>* removed = this->head;
        this->head = removed->next;

        cout << "Deleting : " << removed->value << ENDL;
        delete removed;
    }
}

template <typename T>
bool DoublyLinkedList<T>::isEmpty()
{
    return this->head == nullptr;
}

template <typename T>
void DoublyLinkedList<T>::Insert(Node<T> *before, Node<T> *node)
{
    if(isEmpty() && before == nullptr) this->head = node;
    else {
        Node<T>* next = before->next;

        node->prev = before;
        node->next = next;
        if(next != nullptr) next->prev = node;
        before->next = node;
    }
}

template <typename T>
void DoublyLinkedList<T>::Delete(Node<T> *node)
{
    Node<T>* removed = node;
    Node<T>* prev = removed->prev;
    Node<T>* next = removed->next;

    if(prev != nullptr) prev->next = next;
    if(next != nullptr) next->prev = prev;

    delete(removed);
}

template <typename T>
Node<T>* DoublyLinkedList<T>::Search(T value)
{
    // 교수님이 수업 중에 구현 파트는 언급 안 했음.
    Node<T>* cur = this->head;

    while(cur != nullptr) {
        if(cur->value == value) return cur;
        cur = cur->next;
    }
    return nullptr;
}

template <typename T>
void DoublyLinkedList<T>::Update()
{
    // 교수님이 수업 중에 구현 파트는 언급 안 했음.
}

template <typename T>
void DoublyLinkedList<T>::Print()
{
    cout << "[ ";
    Node<T>* cur = this->head;
    while(cur != nullptr) {
        cout << cur->value;
        cur = cur->next;

        if(cur != nullptr) cout << " <-> ";
    }
    cout << " ]" << ENDL;
}
#pragma endregion

int main() {
    // 이중연결리스트 생성
    DoublyLinkedList<char> *ls = new DoublyLinkedList<char>();

    // A 노드 생성 후 리스트에 삽입
    Node<char> *node1 = new Node<char>('A');
    ls->Insert(nullptr, node1);
    
    // A 노드를 탐색 후 A 노드 뒤에 B 삽입 [A <-> B]
    Node<char>* finder = nullptr;
    finder = ls->Search('A');
    Node<char>* node2 = new Node<char>('B');
    ls->Insert(finder, node2);

    // A 노드를 탐색 후 A 노드 뒤에 C 삽입 [A <-> C <-> B]
    finder = ls->Search('A');
    Node<char>* node3 = new Node<char>('C');
    ls->Insert(finder, node3);

    // B 노드를 탐색 후 B 노드 뒤에 D 삽입 [A <-> C <-> B <-> D]
    finder = ls->Search('B');
    Node<char>* node4 = new Node<char>('D');
    ls->Insert(finder, node4);

    // C 노드를 탐색 후 C 노드 삭제 [A <-> B <-> D]
    finder = ls->Search('C');
    ls->Delete(finder);

    // 리스트 출력
    ls->Print();

    delete ls;
}