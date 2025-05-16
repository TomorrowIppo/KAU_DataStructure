#include <bits/stdc++.h>
#define RESET       "\033[0m"
#define CYAN        "\033[36m"
#define GREEN       "\033[32m"
#define YELLOW      "\033[33m"
#define ENDL        '\n'

using namespace std;

constexpr int MAX_ELEMENT = 200;

#pragma region PriorityQueue_by_Heap

enum class HeapType {
    MAX,
    MIN
};

template <typename T>
class Node 
{
private:
    int key;
    T value;

public:
    Node() 
    {
        this->key = 0;
        this->value = T();
    }
    Node(int key, T value) 
    {
        this->key = key;
        this->value = value;
    }

    // getter & setter
    int getKey() const
    { 
        return this->key; 
    }
    T getValue() const
    {
        return this->value;
    }
    void setKey(int key)
    {
        this->key = key;
    }
    void setValue(T value)
    {
        this->value = value;
    }
};

template <typename T>
class PriorityQueue 
{
private:
    Node<T> node[MAX_ELEMENT];
    int size;
    HeapType type;
    void printRecursive(int idx = 1, string indent = "", bool is_last = true) const;
    int getParentIndex(int idx) const;            
    int getLeftIndex(int idx) const;
    int getRightIndex(int idx) const;
    bool getCondition(int p_key, int c_key) const;

public:
    PriorityQueue(HeapType type);
    ~PriorityQueue();
    void Insert(int key, T value);          // push()
    Node<T> Delete();                       // pop()
    bool isEmpty() const;
    bool isFull() const;
    void printInfo() const;
};

template <typename T>
void PriorityQueue<T>::printRecursive(int idx, string indent, bool is_last) const
{
    if (idx > size) return;

    cout << indent;
    if (idx != 1) {
        cout << (is_last ? "└── " : "├── ");
    }

    cout << CYAN << idx << RESET << ":(" << this->node[idx].getKey() << "," << this->node[idx].getValue() << ")\n";

    int left = getLeftIndex(idx);
    int right = getRightIndex(idx);

    // 자식 존재 여부 확인
    bool has_left = (left <= this->size);
    bool has_right = (right <= this->size);

    if (has_left) {
        printRecursive(left, indent + (is_last ? "    " : "│   "), !has_right);
    }
    if (has_right) {
        printRecursive(right, indent + (is_last ? "    " : "│   "), true);
    }
}

template <typename T>
PriorityQueue<T>::PriorityQueue(HeapType type)
{
    this->type = type;
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
    if(isFull()) 
        throw logic_error("Heap is Full.");

    int idx = ++this->size;

    // 조건에 부합하는 부모 노드를 다 밑으로 내림
    while(idx != 1 && getCondition(this->node[getParentIndex(idx)].getKey(), key)) 
    {
        this->node[idx] = this->node[getParentIndex(idx)];
        idx = getParentIndex(idx);
    }

    // 최종 위치에서 설정
    node[idx].setKey(key);
    node[idx].setValue(value);
}

template <typename T>
Node<T> PriorityQueue<T>::Delete() 
{
    // 여기 구현
    if(isEmpty()) 
        throw logic_error("Heap is Empty.");

    Node<T> ret = this->node[1];
    this->node[1] = this->node[this->size--];

    int idx = 1;
    while(getLeftIndex(idx) <= this->size) 
    {
        int largest_idx = idx;
        int left = getLeftIndex(idx);
        int right = getRightIndex(idx);

        if(left <= this->size && getCondition(node[largest_idx].getKey(), node[left].getKey()))
            largest_idx = left;
        if(right <= this->size && getCondition(node[largest_idx].getKey(), node[right].getKey()))
            largest_idx = right;

        if(largest_idx == idx) break;   // 변경사항이 없음은 조건을 충족했음을 의미

        swap(this->node[idx], this->node[largest_idx]);
        idx = largest_idx;
    }

    return ret;
}

template <typename T>
int PriorityQueue<T>::getParentIndex(int idx) const
{
    return idx / 2;
}

template <typename T>
int PriorityQueue<T>::getLeftIndex(int idx) const
{
    return idx * 2;
}

template <typename T>
int PriorityQueue<T>::getRightIndex(int idx) const
{
    return idx * 2 + 1;
}

template <typename T>
bool PriorityQueue<T>::isEmpty() const
{
    return size == 0;
}

template <typename T>
bool PriorityQueue<T>::isFull() const
{
    return size == MAX_ELEMENT - 1;
}

template <typename T>
bool PriorityQueue<T>::getCondition(int p_key, int c_key) const
{
    return (this->type == HeapType::MAX) ? (p_key < c_key) : (p_key > c_key);
}

template <typename T>
void PriorityQueue<T>::printInfo() const
{    
    if(isEmpty()) 
    {
        cout << "Heap is Emtpy." << ENDL;
        return ;
    }

    printRecursive();
}

#pragma endregion

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    PriorityQueue<char>* pq = new PriorityQueue<char>(HeapType::MIN);
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
    cout << "------------------------------------------" << ENDL;

    auto top = pq->Delete();
    cout << "POP : (" << top.getKey() << "," << top.getValue() << ")" << ENDL;

    pq->printInfo();

    delete pq;

    return 0;
}