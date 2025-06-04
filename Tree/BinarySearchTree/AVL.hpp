#pragma once
#include "BST.hpp"
#include "AVLNode.hpp"

template <typename T>
class AVLTree : public BST<T> {
public:
    AVLTree() : BST<T>() {}
    ~AVLTree() override {}

    void insert(int key, const T& value) override;
    void remove(int key) override;
    void printInfo() const override { 
        std::cout << "---------------------------------------------------------" << std::endl;
        std::cout << "[AVL Info]" << std::endl;
        this->printInfo_helper(); 
    }

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
    this->root = remove_node(this->root, key);
    if (this->root) this->root->set_parent(nullptr);
}

template <typename T>
Node<T>* AVLTree<T>::recursive_insert(Node<T>* cur, Node<T>* node) {
    if (!cur) return node;

    if (node->get_key() < cur->get_key()) {
        cur->set_left(recursive_insert(cur->get_left(), node));
        if (cur->get_left()) cur->get_left()->set_parent(cur);
    } else if (node->get_key() > cur->get_key()) {
        cur->set_right(recursive_insert(cur->get_right(), node));
        if (cur->get_right()) cur->get_right()->set_parent(cur);
    } else {
        throw std::invalid_argument("Duplicate key not allowed");
    }

    update_height(cur);
    int balance = get_balance(cur);

    if (balance > 1 && node->get_key() < cur->get_left()->get_key()) 
        return rotate_right(cur);

    if (balance < -1 && node->get_key() > cur->get_right()->get_key())
        return rotate_left(cur);

    if (balance > 1 && node->get_key() > cur->get_left()->get_key()) {
        cur->set_left(rotate_left(cur->get_left()));
        if (cur->get_left()) cur->get_left()->set_parent(cur);
        return rotate_right(cur);
    }

    if (balance < -1 && node->get_key() < cur->get_right()->get_key()) {
        cur->set_right(rotate_right(cur->get_right()));
        if (cur->get_right()) cur->get_right()->set_parent(cur);
        return rotate_left(cur);
    }

    return cur;
}


template <typename T>
Node<T>* AVLTree<T>::remove_node(Node<T>* cur, int key) {
    if (!cur) return nullptr;

    if (key < cur->get_key()) {
        Node<T>* left = remove_node(cur->get_left(), key);
        cur->set_left(left);
        if (left) left->set_parent(cur);
    }
    else if (key > cur->get_key()) {
        Node<T>* right = remove_node(cur->get_right(), key);
        cur->set_right(right);
        if (right) right->set_parent(cur);
    }
    else {
        // 실제 삭제
        if (!cur->get_left() || !cur->get_right()) {
            Node<T>* temp = cur->get_left() ? cur->get_left() : cur->get_right();
            if (temp) temp->set_parent(cur->get_parent());
            delete cur;
            return temp;
        } else {
            // 왼쪽 서브트리 최대값 or 오른쪽 서브트리 최소값으로 대체
            Node<T>* successor = cur->get_right();
            while (successor->get_left()) successor = successor->get_left();

            cur->set_key(successor->get_key());
            cur->set_value(successor->get_value());

            Node<T>* right = remove_node(cur->get_right(), successor->get_key());
            cur->set_right(right);
            if (right) right->set_parent(cur);
        }
    }

    update_height(cur);
    int balance = get_balance(cur);

    // LL
    if (balance > 1 && get_balance(cur->get_left()) >= 0)
        return rotate_right(cur);

    // LR
    if (balance > 1 && get_balance(cur->get_left()) < 0) {
        cur->set_left(rotate_left(cur->get_left()));
        if (cur->get_left()) cur->get_left()->set_parent(cur);
        return rotate_right(cur);
    }

    // RR
    if (balance < -1 && get_balance(cur->get_right()) <= 0)
        return rotate_left(cur);

    // RL
    if (balance < -1 && get_balance(cur->get_right()) > 0) {
        cur->set_right(rotate_right(cur->get_right()));
        if (cur->get_right()) cur->get_right()->set_parent(cur);
        return rotate_left(cur);
    }

    return cur;
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
Node<T>* AVLTree<T>::rotate_right(Node<T>* z) {
    Node<T>* y = z->get_left();
    Node<T>* T2 = y->get_right();

    y->set_right(z);
    z->set_left(T2);

    if (T2) T2->set_parent(z);
    y->set_parent(z->get_parent());
    z->set_parent(y);

    update_height(z);
    update_height(y);

    return y;
}

template <typename T>
Node<T>* AVLTree<T>::rotate_left(Node<T>* z) {
    Node<T>* y = z->get_right();
    Node<T>* T2 = y->get_left();

    y->set_left(z);
    z->set_right(T2);

    if (T2) T2->set_parent(z);
    y->set_parent(z->get_parent());
    z->set_parent(y);

    update_height(z);
    update_height(y);

    return y;
}