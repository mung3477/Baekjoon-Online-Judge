#include <iostream>
#include <queue>
#include <utility>
using std::cin;
using std::cout;
using std::queue;
using std::pair;
using std::make_pair;  

void inner_(int** cheeze, int** airMeet, int N, int M, bool** visited, queue<pair<int ,int>>& frontier, int row, int col) {
    if (cheeze[row][col]) {
        airMeet[row][col]++;
    }
    else {
        pair<int, int> next = make_pair(row, col);
        frontier.push(next);
        visited[row][col] = true;
    }
}

void spread(int** cheeze, int** airMeet, int N, int M) {
    bool** visited = new bool*[N + 1];
    for (int i = 0; i <= N; i++) {
        visited[i] = new bool[M + 1]{};
    }
    
    queue<pair<int, int>> frontier;
    pair<int, int> start = make_pair(1, 1);
    frontier.push(start);
    
    while (!frontier.empty()) {
        pair<int, int> cur = frontier.front();
        int row = cur.first, col = cur.second;
        frontier.pop();
        
        //up
        if (1 < row && !visited[row - 1][col]) {
            inner_(cheeze, airMeet, N, M, visited, frontier, row - 1, col);
        }
        //down
        if (row < N && !visited[row + 1][col]) {
            inner_(cheeze, airMeet, N, M, visited, frontier, row + 1, col);
        }
        //left
        if (1 < col && !visited[row][col - 1]) {
            inner_(cheeze, airMeet, N, M, visited, frontier, row, col - 1);
        }
        //right
        if (col < M && !visited[row][col + 1]) {
            inner_(cheeze, airMeet, N, M, visited, frontier, row, col + 1);
        }
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    int N, M, left = 0, timeSpent = 0;
    int** cheeze;                         
    int** airMeet;
    
    cin >> N >> M;
    
    cheeze = new int*[N + 1];
    airMeet = new int*[N + 1];
    for (int i = 1; i <= N; i++) {
        cheeze[i] = new int[M + 1]{};
        airMeet[i] = new int[M + 1]{};
    }
    
    //fill cheeze cheezermation
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            cin >> cheeze[i][j];
            if (cheeze[i][j]) { 
                left++;
            }
        }
    }
    
    while (left) {
        spread(cheeze, airMeet, N, M);
        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= M; j++) {
                if (airMeet[i][j] >= 2) {
                    cheeze[i][j] = 0;
                    left--;
                }
                airMeet[i][j] = 0;
            }
        }
        timeSpent++;
    }
    
    cout << timeSpent;
    
    return 0;
}
