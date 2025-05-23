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
    void update_height(Node<T>* node);
    int get_balance(Node<T>* node) const;
    Node<T>* rotate_right(Node<T>* z);
    Node<T>* rotate_left(Node<T>* z);
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
    // 1. 기본 BST 삽입 재귀
    if(!cur) return node;

    if(node->get_key() < cur->get_key()) {
        Node<T>* left_child = recursive_insert(cur->get_left(), node);
        cur->set_left(left_child);
        if(left_child) left_child->set_parent(cur); // null이 리턴될 일은 없지만 GPT가 Defensive Programming 추천해서 ...
    } 
    
    else if(node->get_key() > cur->get_key()) {
        Node<T>* right_child = recursive_insert(cur->get_right(), node);
        cur->set_right(right_child);
        if(right_child) right_child->set_parent(cur);
    } 
    
    else {
        // 중복 키 예외 처리
        throw std::invalid_argument("Duplicate key not allowed");
    }

    // 2. AVL 파트 

    // 높이 갱신
    update_height(cur);

    // BFactor 계산
    int BFactor = get_balance(cur);

    // LL Rotate
    

    // RR Rotate


    // LR Rotate


    // RL rotate

}

template <typename T>
Node<T>* AVLTree<T>::remove_node(Node<T>* cur, int key) {

}

template <typename T>
int AVLTree<T>::get_height(Node<T> *node) const {
    if(!node) return 0;
    return cast_node(node)->get_height();
}

template <typename T>
void AVLTree<T>::update_height(Node<T> *node) {
    if(!node) return;

    int left_height = get_height(node->get_left());
    int right_height = get_height(node->get_right());
    cast_node(node)->set_height(1 + std::max(left_height, right_height));
}

template <typename T>
int AVLTree<T>::get_balance(Node<T> *node) const {
    if(!node) return 0;
    return get_height(node->get_left()) - get_height(node->get_right());
}

template <typename T>
Node<T> *AVLTree<T>::rotate_right(Node<T> *z) {
    Node<T>* y = z->get_left();
    Node<T>* T2 = y->get_right();

    if(T2) {
        T2->set_parent(z);
        z->set_left(T2);
    }
    y->set_parent(z->get_parent());
    y->set_right(z);
    z->get_parent(y);

    update_height(y);
    update_height(z);

    return y;
}

template <typename T>
Node<T> *AVLTree<T>::rotate_left(Node<T> *z) {
    Node<T>* y = z->get_right();
    Node<T>* T2 = y->get_left();

    if(T2) {
        T2->set_parent(z);
        z->set_right(T2);
    }
    y->set_parent(z->get_parent());
    y->set_left(z);
    z->get_parent(y);

    update_height(y);
    update_height(z);

    return y;
}