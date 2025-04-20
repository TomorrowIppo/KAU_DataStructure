#include <iostream>
#define ENDL '\n'

using namespace std;

#pragma region Queue_By_LinkedList

template <typename T>
class Node {
public:
    Node<T>* link;
    T value;

    Node(T value) { this->value = value; link = nullptr; }
};

template <typename T>
class myQueue {
private:
    Node<T>* front;
    Node<T>* rear;
    size_t size;
public:
    myQueue();
    ~myQueue();
    bool isEmpty();
    void enqueue(T data);
    T dequeue();
    T peek();
    void printInfo();
};

template <typename T>
myQueue<T>::myQueue() 
{
    this->size = 0;
    this->front = nullptr;
    this->rear = nullptr;
}

template <typename T>
myQueue<T>::~myQueue() 
{
    while(!isEmpty()) { cout << "Deleting : " << dequeue() << ENDL; }
}

template <typename T>
bool myQueue<T>::isEmpty()
{
    return (front == nullptr) && (rear == nullptr);
}

template <typename T>
void myQueue<T>::enqueue(T data)
{
    Node<T> *node = new Node<T>(data);

    if(isEmpty()) {
        front = node;
        rear = node;
    } else {
        rear->link = node;
        rear = node;
    }
    size++;
}

template <typename T>
T myQueue<T>::dequeue()
{
    if(isEmpty()) throw runtime_error("EMPTY");
    else {
        Node<T> *removed = front;
        T ret = removed->value;

        if(size == 1) {
            front = nullptr;
            rear = nullptr;
        } else {
            front = removed->link;
        }
        size--;

        delete removed;
        return ret;
    }
}

template <typename T>
T myQueue<T>::peek()
{
    if(isEmpty()) throw runtime_error("EMPTY");
    else return front->value;
}

template <typename T>
void myQueue<T>::printInfo()
{
    if(isEmpty()) { 
        cout << "Empty." << ENDL;
        return ;
    }
    cout << "queue size : " << size << ENDL;
    cout << "queue : front - [ ";

    Node<T> *cur = this->front;
    while(cur != nullptr) {
        cout << cur->value;
        cur = cur->link;

        if(cur != nullptr) cout << " <- ";
    }
    cout << " ] - rear" << endl;
}

#pragma endregion

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    myQueue<char> *queue = new myQueue<char>();

    queue->enqueue('A');
    queue->enqueue('B');
    queue->enqueue('C');
    queue->enqueue('D');

    cout << queue->dequeue() << ENDL;   // A
    cout << queue->peek() << ENDL;      // B

    queue->printInfo();
    delete queue;

    return 0;
}