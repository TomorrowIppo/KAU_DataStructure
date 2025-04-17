#include <iostream>
#include <stack>
#include <string>

using namespace std;

int main() {
    stack<char> stack;
    string text;
    char prev = '\0';

    getline(cin, text);

    for (char ch : text) {
        switch (ch) {
            case '[': case '(': case '{':
                stack.push(ch);
                break;
            case ']': case ')': case '}':
                if (stack.empty()) {
                    cout << "ERROR" << endl;
                    return -1;
                }
                prev = stack.top();
                stack.pop();
                if ((ch == ']' && prev != '[') ||
                    (ch == ')' && prev != '(') ||
                    (ch == '}' && prev != '{')) {
                    cout << "ERROR" << endl;
                    return -1;
                }
                break;
            default:
                // pass
                break;
        }
    }

    if (!stack.empty())
        cout << "ERROR" << endl;
    else
        cout << "OK!" << endl;

    return 0;
}
