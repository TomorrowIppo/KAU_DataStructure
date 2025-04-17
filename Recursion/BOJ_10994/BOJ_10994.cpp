#include <bits/stdc++.h>
using namespace std;

constexpr int MAX = 401;
constexpr int PADDING = 2;

int n;
char board[MAX][MAX];

void input();
void solve();
void drawStars(int x, int y, int len);
void printBoard();

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    input();
    solve();

    return 0;
}

void input() {
    cin >> n;
}

void solve() {
    int size = 4 * n - 3;

    // 초기화
    for (int i = 0; i < size; ++i)
        fill(board[i], board[i] + size, ' ');

    drawStars(0, 0, n);
    printBoard();
}

void drawStars(int x, int y, int len) {
    int size = 4 * len - 3;

    // 기저 조건: 가장 안쪽 별
    if (len == 1) {
        board[x][y] = '*';
        return;
    }

    // 테두리 그리기
    for (int i = 0; i < size; ++i) {
        board[x][y + i] = '*';                 // 상단 가로
        board[x + size - 1][y + i] = '*';      // 하단 가로
        board[x + i][y] = '*';                 // 좌측 세로
        board[x + i][y + size - 1] = '*';      // 우측 세로
    }

    // 안쪽 재귀 호출
    drawStars(x + PADDING, y + PADDING, len - 1);
}

void printBoard() {
    int size = 4 * n - 3;

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j)
            cout << board[i][j];
        cout << '\n';
    }
}
