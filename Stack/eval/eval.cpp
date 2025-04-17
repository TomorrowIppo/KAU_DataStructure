#include <iostream>
#include <stack>
#include <string>

using namespace std;

int main() {
    stack<int> stack;
    int val1 = 0, val2 = 0, offset = 0;
    string text;

    cin >> text; // 공백 없이 입력!

    for (char ch : text) {
        if (ch >= '0' && ch <= '9') { // 한 자리 수만 가정
            offset = ch - '0';
            stack.push(offset);
        } else {
            val2 = stack.top();
            stack.pop();
            val1 = stack.top();
            stack.pop();
            switch (ch) {
                case '+': stack.push(val1 + val2); break;
                case '-': stack.push(val1 - val2); break;
                case '*': stack.push(val1 * val2); break;
                default: stack.push(val1 / val2); break;
            }
        }
    }

    cout << "result = " << stack.top() << endl;
    stack.pop();

    return 0;
}
