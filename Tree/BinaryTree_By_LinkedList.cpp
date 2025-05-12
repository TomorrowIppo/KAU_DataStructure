#include <bits/stdc++.h>
#define ENDL '\n'

using namespace std;

#pragma region BinaryTreeByLinkedList

constexpr int ROOT = -1;
constexpr int LEFT = 0;
constexpr int RIGHT = 1;

template <typename T>
class Node {
public:
    Node<T>* left;
    Node<T>* right;
    T id;

    Node(T id) {
        this->id = id;
        this->left = nullptr;
        this->right = nullptr;
    }
};

// TODO : Implement BinaryTree Class
template <typename T>
class BinaryTree {
private:
    Node<T>* root;
    void destroy(Node<T>* node);
public:
    BinaryTree();
    ~BinaryTree();
    bool isEmpty();
    void Insert(T parent, T child, int dir);
    void Delete(T id);
    void printInfo(Node<T>* node = nullptr, string indent = "", bool is_last = true, int dir = ROOT);
    void preorder(Node<T>* node = nullptr);
    void inorder(Node<T>* node = nullptr);
    void postorder(Node<T>* node = nullptr);
    void levelorder(Node<T>* node = nullptr);
    Node<T>* Search(T id, bool find_parent = false);
};

template <typename T>
BinaryTree<T>::BinaryTree()
{
    this->root = nullptr;
}

template <typename T>
BinaryTree<T>::~BinaryTree() {
   destroy(this->root);
}

template <typename T>
bool BinaryTree<T>::isEmpty() {
    return root == nullptr;
}

template <typename T>
void BinaryTree<T>::destroy(Node<T>* node) {
    /*
    Delete() 재사용하면 Biased Case의 경우 O(N^2)
    
    postorder 방식으로 구현
    - 자식 -> 부모순으로 메모리 해제 특징에 적합
    - dangling 방지
    */
    if(node == nullptr) return;

    destroy(node->left);
    destroy(node->right);
    delete node;
}

template <typename T>
void BinaryTree<T>::Insert(T parent, T child, int dir) {
    if(this->root == nullptr) this->root = new Node<T>(parent);

    Node<T>* c_node = new Node<T>(child);
    Node<T>* p_node = Search(parent);
    if(p_node == nullptr) 
        throw invalid_argument("Insert failed: parent node not found.");

    if(dir == LEFT) 
        p_node->left = c_node;
    else if(dir == RIGHT) 
        p_node->right = c_node;
    else 
        throw invalid_argument("Insert failed: direction must be 0 (left) or 1 (right).");
}

template <typename T>
void BinaryTree<T>::Delete(T id) {
    Node<T>* target = Search(id);
    if(target == nullptr) 
        throw invalid_argument("Node not found.");

    if(target->left != nullptr || target->right != nullptr)
        throw logic_error("Only leaf node can be deleted.");

    Node<T>* parent = Search(id, true);

    if(parent == nullptr) {
        // target이 root
        delete this->root;
        this->root = nullptr;
    } else {
        if(parent->left == target) 
            parent->left = nullptr;
        else if(parent->right == target)
            parent->right = nullptr;
        
        delete target;
    }

    cout << "Node " << target->id << " deleted." << ENDL;
}

template <typename T>
void BinaryTree<T>::printInfo(Node<T>* node, string indent, bool is_last, int dir) {
    // 전위순회 기반으로 구현
    if(dir != LEFT && dir != RIGHT && dir != ROOT) 
        throw invalid_argument("Insert failed: direction must be 0 (left) or 1 (right).");

    if(node == nullptr) node = this->root;

    cout << indent << (is_last ? "└── " : "├── "); 
    if(dir == LEFT) 
        cout << "(L)";
    else if(dir == RIGHT) 
        cout << "(R)";
    cout << "Node " << node->id << '\n';

    queue<pair<Node<T>*, int>> children;
    if (node->left)  children.push({node->left, LEFT});
    if (node->right) children.push({node->right, RIGHT});

    while(!children.empty()) {
        auto cur = children.front(); children.pop();
        printInfo(cur.first, indent + ((is_last) ? "    " : "│   "), children.empty(), cur.second);
    }
}

template <typename T>
void BinaryTree<T>::preorder(Node<T>* node) {
    node = (node ? node : root);

    cout << node->id << " ";
    if(node->left) preorder(node->left);
    if(node->right) preorder(node->right);
}

template <typename T>
void BinaryTree<T>::inorder(Node<T>* node) {
    node = (node ? node : root);

    if(node->left) inorder(node->left);
    cout << node->id << " ";
    if(node->right) inorder(node->right);
}

template <typename T>
void BinaryTree<T>::postorder(Node<T>* node) {
    node = (node ? node : root);

    if(node->left) postorder(node->left);
    if(node->right) postorder(node->right);
    cout << node->id << " ";
}

template <typename T>
void BinaryTree<T>::levelorder(Node<T>* node) {
    node = (node ? node : root);

    queue<Node<T>*> q;
    q.push(node);
    while(!q.empty()) {
        auto cur = q.front(); q.pop();

        if(cur) {
            cout << cur->id << " ";
            q.push(cur->left);
            q.push(cur->right);
        }
    }
}

template <typename T>
Node<T>* BinaryTree<T>::Search(T id, bool find_parent) {
    stack<Node<T>*> s;
    s.push(this->root);

    while(!s.empty()) {
        auto cur = s.top(); s.pop();

        // 일반 검색 (자기 자신 찾기)
        if(!find_parent && cur->id == id) return cur;

        // 부모 검색
        if(find_parent) {
            if(cur->left && cur->left->id == id) return cur;
            if(cur->right && cur->right->id == id) return cur;
        }
        
        if(cur->left) 
            s.push(cur->left);
        if(cur->right) 
            s.push(cur->right);
    }
    return nullptr;
}

#pragma endregion

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    /*
    [최종 트리]
        A
       / \
      B   C
     / \
    D   E
    */
    BinaryTree<char>* bt = new BinaryTree<char>();
    bt->Insert('A', 'B', LEFT); // Insert(Parent, Child, Direction) 순서 고정
    bt->Insert('A', 'C', RIGHT);
    bt->Insert('B', 'D', LEFT);
    bt->Insert('B', 'E', RIGHT);
    bt->Insert('E', 'F', RIGHT);

    cout << "[TreeInfo]\n";
    bt->printInfo();
    cout << ENDL;

    bt->Delete('F');

    cout << "preorder   : ";
    bt->preorder();
    cout << ENDL;

    cout << "inorder    : ";
    bt->inorder();
    cout << ENDL;

    cout << "postorder  : ";
    bt->postorder();
    cout << ENDL;

    cout << "levelorder : ";
    bt->levelorder();
    cout << ENDL;

    delete bt;

    return 0;
}
