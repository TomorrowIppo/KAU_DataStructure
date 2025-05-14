#include <bits/stdc++.h>
#define ENDL '\n'
#define MAX_ELEMENT 200

using namespace std;

constexpr int MAX = 0;
constexpr int MIN = 1;

#pragma region PriorityQueue_by_Heap

template <typename T>
class Node 
{
public:
    int key;
    T value;

    Node() {
        this->key = 0;
        this->value = T();
    }
    Node(int key, T value) {
        this->key = key;
        this->value = value;
    }
};

template <typename T>
class PriorityQueue 
{
private:
    Node<T> node[MAX_ELEMENT];
    int size;
    int condition;
public:
    PriorityQueue(int condition);
    ~PriorityQueue();
    void Insert(int key, T value);      // push()
    void Delete();                      // pop()
    Node<T>& getParent(int idx);        // top()
    Node<T>& getLeftChild(int idx);
    Node<T>& getRightChild(int idx);
    bool isEmpty();
    bool isFull();
    void printInfo(Node<T>* node = nullptr, string indent = "", bool is_last = true);
};

#pragma endregion

template <typename T>
PriorityQueue<T>::PriorityQueue(int condition) 
{
    if(condition != MAX && condition != MIN)
        throw invalid_argument("Construct failed: condition must be 0 (MAX) or 1 (MIN).");
    this->condition = condition;
    this->size = 0;
}

template <typename T>
PriorityQueue<T>::~PriorityQueue() 
{
}

template <typename T>
void PriorityQueue<T>::Insert(int key, T value) 
{
    // 여기 구현
}

template <typename T>
void PriorityQueue<T>::Delete() 
{
    // 여기 구현
}

template <typename T>
Node<T> &PriorityQueue<T>::getParent(int idx)
{
    return node[idx / 2];
}

template <typename T>
Node<T> &PriorityQueue<T>::getLeftChild(int idx)
{
    return node[idx * 2];
}

template <typename T>
Node<T> &PriorityQueue<T>::getRightChild(int idx)
{
    return node[idx * 2 + 1];
}

template <typename T>
bool PriorityQueue<T>::isEmpty()
{
    return size == 0;
}

template <typename T>
bool PriorityQueue<T>::isFull()
{
    return size == MAX_ELEMENT - 1;
}

template <typename T>
void PriorityQueue<T>::printInfo(Node<T>* node, string indent, bool is_last) 
{
    // 여기 구현
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    PriorityQueue<char>* pq = new PriorityQueue<char>(MAX);
    pq->Insert(10, 'A');
    pq->Insert(40, 'B');
    pq->Insert(30, 'C');
    pq->Insert(5, 'D');
    pq->Insert(12, 'E');
    pq->Insert(6, 'F');
    pq->Insert(15, 'G');
    pq->Insert(9, 'H');
    pq->Insert(60, 'I');

    pq->printInfo();

    delete pq;

    return 0;
}