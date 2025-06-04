#pragma once

template <typename T>
class Node 
{
protected:
    int key;
    T value;
    Node* left;
    Node* right;
    Node* parent;

public:
    Node(int key = 0, T value = T()) :
        key(key), value(value), left(nullptr), right(nullptr), parent(nullptr) {}
    virtual ~Node() = default;

    // getter
    const int& get_key() const { return this->key; }
    const T& get_value() const { return this->value; }
    Node<T>* get_left() const { return this->left; }
    Node<T>* get_right() const { return this->right; }
    Node<T>* get_parent() const { return this->parent; }

    // setter
    void set_key(const int& key) { this->key = key; }
    void set_value(const T& value) { this->value = value; }
    void set_left(Node<T>* left) { this->left = left; }
    void set_right(Node<T>* right) { this->right = right; }
    void set_parent(Node<T>* parent) { this->parent = parent; }
};