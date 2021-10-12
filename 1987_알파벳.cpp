#include <iostream>
using std::cin;
using std::cout;

int R, C, maxDepth = 0;
char** board;
bool* visited;

int max(int a, int b) {
    if (a > b) return a;
    else return b;
}

//go through there!
void dfs(int row, int col, int depth) {
    char cur = board[row][col];
    //can't go through here
    if (visited[cur - 'A']) {
        maxDepth = max(maxDepth, depth - 1);
    }
    //can go through here
    else {
        visited[cur - 'A'] = true;
        //go upward
        if (1 < row) {
            dfs(row - 1, col, depth + 1);
        }
        //go downward
        if (row < R) {
            dfs(row + 1, col, depth + 1);
        }
        //go left
        if (1 < col) {
            dfs(row, col - 1, depth + 1);
        }
        //go right
        if (col < C) {
            dfs(row, col + 1, depth + 1);
        }
        //undo visitation
        visited[cur - 'A'] = false;
    }
}

int main()
{
    cin >> R >> C;
    visited = new bool[26]{};
    board = new char*[R + 1];
    for (int i = 1; i <= R; i++) {
        board[i] = new char[C + 1];
        for (int j = 1; j <= C; j++)
            cin >> board[i][j];
    }
    
    dfs(1, 1, 1);
    
    cout << maxDepth;
    
    return 0;
}
