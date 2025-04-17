#include <bits/stdc++.h>
#define MAX 401

using namespace std;

int n;
char board[MAX][MAX];

void input();
void solve();
void makeStar19th(int x, int y, int len);
void printBoard();

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    input();
    solve();

    return 0;
}

void input() { cin >> n; }

void solve() { 
    // init
    int dist = 4 * n - 3;
    for(int i = 0; i < dist; i++)
        for(int j = 0; j < dist; j++)
            board[i][j] = ' ';

    makeStar19th(0, 0, n); 
    printBoard();
}

void makeStar19th(int x, int y, int len) {
    if(len == 1) { board[x][y] = '*'; return ; }
    
    int dist = (4 * len - 3);
    for(int i = x; i < x + dist; i++) {
        board[i][y] = '*';
        board[i][y + dist - 1] = '*';
    }
    for(int i = y; i < y + dist; i++) {
        board[x][i] = '*';
        board[x + dist - 1][i] = '*';
    }

    makeStar19th(x + 2, y + 2, len - 1);
}

void printBoard() {
    int dist = (4 * n - 3);
    for(int i = 0; i < dist; i++) {
        for(int j = 0; j < dist; j++)
            cout << board[i][j];
        cout << '\n';
    }
}