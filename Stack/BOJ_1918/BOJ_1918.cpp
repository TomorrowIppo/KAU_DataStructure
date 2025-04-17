/*
 A+B*C/(D*E-F)+G -> ABC*DE*F-/+G+
 A+B*C-D/E -> ABC*+DE/-
*/

#include <bits/stdc++.h>

using namespace std;

string ans = "";

void solve();
void clear_stack(stack<char> &stk);
int priority(char c);

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    solve();
    
    return 0;
}

void solve() {
    string inp;
    cin >> inp;
    
    stack<char> stk;
    for(auto c : inp) {
        int cur = priority(c);
        
        if(c == '(') stk.push(c);
        else if(c == ')') {
            while(!stk.empty()) {
                char top = stk.top();
                stk.pop();
                
                if(top == '(') break;
                ans += top;
            }
        }
        else if(cur == -1) ans += c;
        else {
            while(!stk.empty()) {
                char top = stk.top();
                if(cur > priority(top)) break;
                ans += top;
                stk.pop();
            }
            stk.push(c);
        }
    }
    clear_stack(stk);
    
    cout << ans << '\n';
}

void clear_stack(stack<char> &stk) {
    while(!stk.empty()) {
        char top = stk.top();
        stk.pop();
        
        ans += top;
    }
}

int priority(char c) {
    switch (c) {
        case '(': case ')': return 0;
        case '*': case '/': return 2;
        case '+': case '-': return 1;
        default: return -1;
    }
}
