#pragma once
#include "Node.hpp"

template <typename T>
class AVLNode : public Node<T> {
private:
    int height;

public:
    AVLNode(int key, const T& value)
        : Node<T>(key, value), height(1) {}

    int get_height() const { return height; }
    void set_height(int h) { height = h; }
};
