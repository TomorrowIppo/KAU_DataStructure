#include <iostream>
#define ENDL '\n'

using namespace std;

#pragma region Stack_By_Array

template <typename T>
class Node {
public:
    Node<T>* link;
    T value;

    Node(T value) { this->value = value; this->link = nullptr; }
};

template <typename T>
class myStack {
private:
    Node<T>* top;
    size_t size;
public:
    myStack();
    ~myStack();
    bool isEmpty();
    void push(T data);
    T pop();
    T peek();
    void printInfo();
};

template <typename T>
myStack<T>::myStack()
{
    this->top = nullptr;
    this->size = 0;
}

template <typename T>
myStack<T>::~myStack()
{
    cout << ENDL;
    while(!isEmpty()) { cout << "Deleting : " << pop() << ENDL; }
}

template <typename T>
bool myStack<T>::isEmpty()
{
    return this->top == nullptr;
}

template <typename T>
void myStack<T>::push(T data)
{
    Node<T>* node = new Node<T>(data);
    if(isEmpty()) this->top = node;
    else {
        node->link = this->top;
        this->top = node;
    }
    size++;
}

template <typename T>
T myStack<T>::pop()
{
    if(isEmpty()) throw runtime_error("Underflow Error");
    Node<T>* removed = this->top;
    this->top = removed->link;
    T ret = removed->value;

    size--;
    delete removed;
    return ret;
}

template <typename T>
T myStack<T>::peek()
{
    if(isEmpty()) throw runtime_error("Underflow Error");
    return this->top->value;
}

template <typename T>
void myStack<T>::printInfo()
{
    if(isEmpty()) { 
        cout << "Empty." << ENDL;
        return ;
    }
    cout << "stack size : " << this->size << ENDL;
    cout << "stack : ";

    Node<T>* tmp_top = this->top;
    cout << "top - [ ";
    while(tmp_top != nullptr) {
        cout << tmp_top->value;
        tmp_top = tmp_top->link;

        if(tmp_top != nullptr) cout << " -> ";
    }
    cout << " ] - bottom" << ENDL;
}

#pragma endregion

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    myStack<char> *stack = new myStack<char>();

    stack->push('A');
    cout << stack->peek() << ENDL;   // A

    stack->push('B');
    stack->push('C');
    cout << stack->pop() << ENDL;    // C
    cout << stack->peek() << ENDL;   // B
    stack->push('D');

    stack->printInfo();  // D B A
    delete stack;

    return 0;
}