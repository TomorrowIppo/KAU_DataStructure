#include <bits/stdc++.h>

using namespace std;

/*

ex)
Char. Set
├
─
│
└

input
6
1 3 3 -1 1 2

output
Node 3
├── Node 1
│   ├── Node 0
│   └── Node 4
└── Node 2
    └── Node 5

input
6
-1 0 0 1 1 2

output
Node 0
├── Node 1
│   ├── Node 3
│   └── Node 4
└── Node 2
    └── Node 5

*/

int find_root(const vector<int>& parent);
void printTree(int node, const vector<int>&, string indent = "", bool is_last = true);

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> parent(n);
    for(auto& p : parent) cin >> p;

    int root = find_root(parent);
    if(root == -1) {
        cerr << "Error : Root Node를 찾을 수 없습니다.\n";
        return 1;
    }

    printTree(root, parent);

    return 0;
}

int find_root(const vector<int>& parent) {
    for(int i = 0; i < parent.size(); i++) 
        if(parent[i] == -1) return i;
    return -1;
}

void printTree(int node, const vector<int>& parent, string indent, bool is_last) {
    // 전위순회 기반으로 구현
    
    cout << indent << (is_last ? "└── " : "├── ") << "Node " << node << '\n';

    queue<int> children;
    for(int i = 0; i < parent.size(); i++) 
        if(parent[i] == node) children.push(i);
    
    while(!children.empty()) {
        auto cur = children.front(); children.pop();
        printTree(cur, parent, indent + ((is_last) ? "    " : "│   "), children.empty());
    }
}