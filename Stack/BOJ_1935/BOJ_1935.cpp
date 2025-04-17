/*
 "소수점 둘째 자리까지"라는 표현은 절대오차 10^-2 정도를 의미하며, 식의 계산 결과의 절댓값이 최대 2×10^9이기 때문에 상대오차로는 대략 10^-11 이하의 오차를 가져야 통과가 가능합니다.

 애초에 float는 극히 일부 문제를 제외하고, 문제 풀이에 사용하기에는 너무나도 부정확합니다.
 by kep1er07
 */

#include <bits/stdc++.h>

using namespace std;

void solve();
bool is_oper(char c);

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    solve();
    
    return 0;
}

void solve() {
    int N;
    string inp;
    cin >> N >> inp;
    
    vector<int> val(N);
    for(int i = 0; i < N; i++) cin >> val[i];
    
    stack<double> stk;
    for(auto c : inp) {
        if(is_oper(c)) {
            double val2 = stk.top(); stk.pop();
            double val1 = stk.top(); stk.pop();
            
            switch (c) {
                case '+':
                    stk.push(val1 + val2);
                    break;
                case '-':
                    stk.push(val1 - val2);
                    break;
                case '*':
                    stk.push(val1 * val2);
                    break;
                case '/':
                    stk.push(val1 / val2);
                    break;
                default:
                    break;
            }
        } else {
            int num = val[c - 'A'];
            stk.push(num);
        }
    }
    cout << fixed;
    cout.precision(2);
    cout << stk.top() << '\n';
}

bool is_oper(char c) {
    switch (c) {
        case '+': case '-': case '*': case '/':
            return true;
            
        default:
            return false;
    }
}
