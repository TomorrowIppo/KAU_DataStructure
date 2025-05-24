#include <iostream>
#include "BST.hpp"
#include "AVL.hpp"

using namespace std;

int main()
{
    BST<char>* bst = new BST<char>();
    AVLTree<char>* avl = new AVLTree<char>();

    bst->insert(1, 'A');
    bst->insert(2, 'B');
    bst->insert(3, 'C');
    bst->insert(4, 'D');
    bst->insert(5, 'E');
    bst->insert(6, 'F');
    bst->insert(7, 'G');
    bst->insert(8, 'H');

    bst->remove(5);

    // bst->inorder();
    bst->printInfo();
    // cout << "---------------------------------------------------------" << endl;
    // auto find = bst->search(6);
    // if(find) 
    //     cout << "(" << find->get_key() << ", " << find->get_value() << ") found" << endl;
    // else
    //     cout << "not found" << endl;
    // cout << "---------------------------------------------------------" << endl;

    avl->insert(1, 'A');
    avl->insert(2, 'B');
    avl->insert(3, 'C');
    avl->insert(4, 'D');
    avl->insert(5, 'E');
    avl->insert(6, 'F');
    avl->insert(7, 'G');
    avl->insert(8, 'H');

    avl->remove(5);

    // avl->inorder();
    avl->printInfo();

    cout << "---------------------------------------------------------" << endl;
    cout << "[BST destructor]" << endl; 
    delete bst;
    cout << "---------------------------------------------------------" << endl;
    cout << "[BST destructor]" << endl; 
    delete avl;

    return 0;
}