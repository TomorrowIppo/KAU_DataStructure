#include <iostream>
#define ENDL '\n'

using namespace std;

#pragma region Stack_By_Array

constexpr int MAX = 999;

template <typename T>
class myStack {
private:
    T* stack;
    int top;
    size_t size;
public:
    myStack(size_t size = 100);
    ~myStack();
    bool isEmpty();
    bool isFull();
    void push(T data);
    T pop();
    T peek();
    void printInfo();
};

template <typename T>
myStack<T>::myStack(size_t size)
{
    this->top = -1;
    this->size = size;
    this->stack = new T[size];
}

template <typename T>
myStack<T>::~myStack()
{
    delete[] stack;
}

template <typename T>
bool myStack<T>::isEmpty()
{
    return this->top == -1;
}

template <typename T>
bool myStack<T>::isFull()
{
    return this->top == size - 1;
}

template <typename T>
void myStack<T>::push(T data)
{
    if(isFull()) throw runtime_error("Overflow Error");
    this->stack[++this->top] = data;
}

template <typename T>
T myStack<T>::pop()
{
    if(isEmpty()) throw runtime_error("Underflow Error");
    return this->stack[this->top--];
}

template <typename T>
T myStack<T>::peek()
{
    if(isEmpty()) throw runtime_error("Underflow Error");
    return this->stack[this->top];
}

template <typename T>
void myStack<T>::printInfo()
{
    if(isEmpty()) { 
        cout << "Empty." << ENDL;
        return ;
    }
    cout << "top pos : " << this->top << ENDL;
    cout << "stack : top - [ ";

    int tmp_top = this->top;
    while(tmp_top != -1) {
        cout << this->stack[tmp_top--];
        if(tmp_top != -1) cout << " -> ";
    }
    cout << " ]" << ENDL;
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

    return 0;
}