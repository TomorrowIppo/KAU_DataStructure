#include <iostream>
#include "BST.hpp"

using namespace std;

int main()
{
    BST<char>* bst = new BST<char>();

    bst->insert(9, 'A');
    bst->insert(11, 'B');
    bst->insert(4, 'C');
    bst->insert(6, 'D');
    bst->insert(2, 'E');
    bst->insert(13, 'F');
    bst->insert(10, 'G');
    bst->insert(1, 'H');

    bst->remove(1);

    cout << "[Inorder]" << ENDL;
    bst->inorder();
    cout << "---------------------------------------------------------" << ENDL;
    cout << "[BST Info]" << ENDL;
    bst->printInfo();

    delete bst;

    return 0;
}