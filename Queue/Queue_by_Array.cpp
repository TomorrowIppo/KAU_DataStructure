#include <iostream>
#define ENDL '\n'

using namespace std;

#pragma region Queue_By_Array

template <typename T>
class myQueue {
private:
    T* queue;
    size_t size;
    int front, rear;

public:
    myQueue(size_t size = 10);
    ~myQueue();
    bool isEmpty();
    bool isFull();
    void enqueue(T data);
    T dequeue();
    T peek();
    void printInfo();
};

template <typename T>
myQueue<T>::myQueue(size_t size) 
{
    this->size = size;
    this->front = -1;
    this->rear = -1;
    this->queue = new T[size];
}

template <typename T>
myQueue<T>::~myQueue() 
{
    delete [] queue;
}

template <typename T>
bool myQueue<T>::isEmpty()
{
    return front == rear;
}

template <typename T>
bool myQueue<T>::isFull() 
{
    return rear == size - 1;
}

template <typename T>
void myQueue<T>::enqueue(T data)
{
    if(isFull()) throw runtime_error("FULL");
    else queue[++rear] = data;
}

template <typename T>
T myQueue<T>::dequeue()
{
    if(isEmpty()) throw runtime_error("EMPTY");
    else return queue[++front];
}

template <typename T>
T myQueue<T>::peek()
{
    if(isEmpty()) throw runtime_error("EMPTY");
    else return queue[front + 1];
}

template <typename T>
void myQueue<T>::printInfo()
{
    if(isEmpty()) { 
        cout << "Empty." << ENDL;
        return ;
    }

    cout << "queue size : " << rear - front << ENDL;
    cout << "queue : front - [ ";

    int cur = this->front;
    while(cur != rear) {
        cout << this->queue[++cur];
        if(cur != rear) cout << " <- ";
    }
    cout << " ] - rear" << endl;
}

#pragma endregion

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int size = 5;
    myQueue<int> *queue = new myQueue<int>(size);

    for(int i = 0; i < size; i++) queue->enqueue(i + 3);
    cout << queue->peek() << ENDL;
    cout << queue->dequeue() << ENDL;

    queue->printInfo();
    delete queue;

    return 0;
}