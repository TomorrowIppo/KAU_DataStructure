#pragma once
#include "BST.hpp"
#include "AVLNode.hpp"
#include <iostream>

template <typename T>
class AVLTree : public BST<T> {
public:
    AVLTree() : BST<T>() {}
    ~AVLTree() override {}

    void insert(int key, const T& value) override;
    void remove(int key) override;

protected:
    // AVLNode 타입으로 캐스팅하여 높이 관련 메서드 사용 가능
    AVLNode<T>* cast_node(Node<T>* node) const {
        return static_cast<AVLNode<T>*>(node);
    }

    Node<T>* recursive_insert(Node<T>* cur, Node<T>* node) override;
    Node<T>* remove_node(Node<T>* cur, int key) override;

    // AVL 균형 유지 함수들
    int get_height(Node<T>* node) const;
    int get_balance(Node<T>* node) const;
    Node<T>* rotate_right(Node<T>* y);
    Node<T>* rotate_left(Node<T>* x);
    void update_height(Node<T>* node);
};

// ------------------------ Implementation ----------------------------

template <typename T>
void AVLTree<T>::insert(int key, const T& value) {
    Node<T>* node = new AVLNode<T>(key, value);  // AVLNode 생성
    this->root = recursive_insert(this->root, node);
    if (this->root) this->root->set_parent(nullptr);  // 루트 노드 부모는 항상 nullptr
}

template <typename T>
void AVLTree<T>::remove(int key) {
    
}

template <typename T>
Node<T>* AVLTree<T>::recursive_insert(Node<T>* cur, Node<T>* node) {
    
}

template <typename T>
Node<T>* AVLTree<T>::remove_node(Node<T>* cur, int key) {

}

template <typename T>
int AVLTree<T>::get_height(Node<T> *node) const {
    return 0;
}

template <typename T>
int AVLTree<T>::get_balance(Node<T> *node) const {
    return 0;
}

template <typename T>
Node<T> *AVLTree<T>::rotate_right(Node<T> *y) {
    Node<T>* x = y->get_left();
    Node<T>* T2 = x->get_right();

    // 회전
    x->set_right(y);

    return nullptr;
}

template <typename T>
Node<T> *AVLTree<T>::rotate_left(Node<T> *x) {
    return nullptr;
}

template <typename T>
void AVLTree<T>::update_height(Node<T> *node) {
}
