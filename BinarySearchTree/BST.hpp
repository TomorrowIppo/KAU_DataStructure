#pragma once
#include "Node.hpp"
#include <iostream>
#include <queue>

#define RESET       "\033[0m"
#define CYAN        "\033[36m"
#define GREEN       "\033[32m"
#define YELLOW      "\033[33m"
#define ENDL        '\n'

using namespace std;

enum class Direction { LEFT, RIGHT, ROOT };

template <typename T>
class BST {
protected:
    Node<T>* root;

public:
    BST() : root(nullptr) {}
    virtual ~BST() { clear(root); }

    // 기본 연산
    virtual Node<T>* search(int key) const;
    virtual void insert(int key, const T& value);
    virtual void remove(int key);
    Node<T>* get_root() const { return this->root; }

    // 트리 순회 (중위순회)
    void inorder() const { inorder_helper(root); cout << ENDL; }

    // 트리 정보 출력 (전위순회)
    void printInfo(Node<T>* node = nullptr, string indent = "", bool is_last = true, Direction dir = Direction::ROOT);

protected:
    // successor 찾기
    Node<T>* find_min(Node<T>* node) {
        while (node->get_left()) {
            node = node->get_left();
        }
        return node;
    }

    // 내부 재귀 insert
    virtual Node<T>* recursive_insert(Node<T>* cur, Node<T>* node);

    // 내부 재귀 remove
    virtual Node<T>* remove_node(Node<T>* cur, int key);

    // 서브트리 삭제
    void clear(Node<T>* node);

    // 내부 헬퍼
    void inorder_helper(Node<T>* node) const;

    // 노드 교체 (삭제시 유용)
    void transplant(Node<T>* u, Node<T>* v);
};

template <typename T>
inline Node<T> *BST<T>::search(int key) const
{
    // TODO
    return nullptr;
}

template <typename T>
inline void BST<T>::insert(int key, const T &value)
{
    Node<T>* node = new Node(key, value);
    this->root = recursive_insert(this->root, node);
}

template <typename T>
inline void BST<T>::remove(int key)
{
    this->root = remove_node(this->root, key);
}

template <typename T>
inline Node<T>* BST<T>::remove_node(Node<T>* cur, int key)
{
    if(cur == nullptr) return nullptr;

    if(key < cur->get_key())
        cur->set_left(remove_node(cur->get_left(), key));
    else if(key > cur->get_key())
        cur->set_right(remove_node(cur->get_right(), key));
    else    // 삭제할 노드를 찾은 경우
    {
        // Case 1 : leaf
        if(!cur->get_left() && !cur->get_right())
        {
            delete cur;
            return nullptr;
        }

        // Case 2 : 자식 1개
        if(!cur->get_left())    // 오른쪽 자식만 있는 경우
        {
            Node<T>* temp = cur->get_right();
            temp->set_parent(cur->get_parent());
            delete cur;
            return temp;
        }
        else if(!cur->get_right())  // 왼쪽 자식만 있는 경우
        {
            Node<T>* temp = cur->get_left();
            temp->set_parent(cur->get_parent());
            delete cur;
            return temp;
        }

        // Case 3 : 자식 2개
        Node<T>* successor = find_min(cur->get_right());
        cur->set_key(successor->get_key());
        cur->set_value(successor->get_value());
        // 실제 successor 노드는 오른쪽 서브트리에서 제거, but successor 노드로의 중복탐색이 발생하므로 transplant() 구현을 통해 개선 필요
        cur->set_right(remove_node(cur->get_right(), successor->get_key()));
    }
    return cur;
}

template <typename T>
inline Node<T>* BST<T>::recursive_insert(Node<T>* cur, Node<T>* node)
{
    if(!cur) return node;

    // root보다 작으면 왼쪽으로
    if(node->get_key() < cur->get_key())
    {
        cur->set_left(recursive_insert(cur->get_left(), node));
        cur->get_left()->set_parent(node);
    }
    else 
    {
        cur->set_right(recursive_insert(cur->get_right(), node));
        cur->get_right()->set_parent(node);
    }

    return cur;
}

template <typename T>
inline void BST<T>::clear(Node<T> *node)
{
    // TODO
}

template <typename T>
inline void BST<T>::inorder_helper(Node<T> *node) const
{
    if (node == nullptr) return;

    inorder_helper(node->get_left());  // 왼쪽 서브트리 순회
    std::cout << "(" << node->get_key() << ", " << node->get_value() << ") ";
    inorder_helper(node->get_right()); // 오른쪽 서브트리 순회
}

template <typename T>
inline void BST<T>::transplant(Node<T> *u, Node<T> *v)
{
    // TODO
}

template <typename T>
void BST<T>::printInfo(Node<T>* node, string indent, bool is_last, Direction dir) {
    if(dir != Direction::LEFT && dir != Direction::RIGHT && dir != Direction::ROOT) 
        throw invalid_argument("Insert failed: direction must be Direction::LEFT, RIGHT or ROOT.");

    if(node == nullptr) node = this->root;

    cout << indent << (is_last ? "└── " : "├── "); 
    if(dir == Direction::LEFT) 
        cout << YELLOW << "L" << RESET << ": ";
    else if(dir == Direction::RIGHT) 
        cout << GREEN << "R" << RESET << ": ";
    cout << "(" << CYAN << node->get_key() << RESET << ", " << node->get_value() << ")" << ENDL;

    queue<pair<Node<T>*, Direction>> children;
    if (node->get_left())  children.push({node->get_left(), Direction::LEFT});
    if (node->get_right()) children.push({node->get_right(), Direction::RIGHT});

    while(!children.empty()) {
        auto cur = children.front(); children.pop();
        printInfo(cur.first, indent + ((is_last) ? "    " : "│   "), children.empty(), cur.second);
    }
}