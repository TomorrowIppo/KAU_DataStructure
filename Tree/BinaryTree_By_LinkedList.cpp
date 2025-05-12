#include <bits/stdc++.h>
#define ENDL '\n'

using namespace std;

/*

left 부터 채우기

*/

#pragma region BinaryTreeByLinkedList
template <typename T>
class Node {
public:
    Node<T>* left;
    Node<T>* right;
    T value;

    Node(T val) {
        this->value = val;
        this->left = nullptr;
        this->right = nullptr;
    }
};


// TODO : Implement BinaryTree Class
template <typename T>
class BinaryTree {
private:
    Node<T>* root;
public:
    BinaryTree();
    ~BinaryTree();
    bool isEmpty();
    void Insert();
    void Delete();
    void printInfo();
    void preorder();
    void inorder();
    void postorder();
    void levelorder();
    Node<T>* Search(T value);
};

template <typename T>
BinaryTree<T>::BinaryTree() {
    this->root = nullptr;
}

template <typename T>
BinaryTree<T>::~BinaryTree() {
    
}

template <typename T>
bool BinaryTree<T>::isEmpty() {
    return root == nullptr;
}

template <typename T>
void BinaryTree<T>::Insert() {
    
}

template <typename T>
void BinaryTree<T>::Delete() {
}

template <typename T>
void BinaryTree<T>::printInfo() {
}

template <typename T>
void BinaryTree<T>::preorder() {
}

template <typename T>
void BinaryTree<T>::inorder() {
}

template <typename T>
void BinaryTree<T>::postorder() {
}

template <typename T>
void BinaryTree<T>::levelorder() {
}

template <typename T>
Node<T>* BinaryTree<T>::Search(T value) {
}

#pragma endregion

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    return 0;
}
