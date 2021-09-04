#include <iostream>
#include <queue>
#include <tuple>
#include <utility>
using std::pair;
using std::cin;
using std::cout;
using std::queue;
using std::tuple;

//tuple<Row, Column, cost, breakedWall>
//visited[row][col][breaked]

//이 위치에 갈 수 있다면 frontier에 추가
bool explore(int row, int col, int cost, int breaked, bool*** visited, queue<tuple<int, int, int, int>>& frontier, int** map) {
    if (!visited[row][col][breaked] && ((!map[row][col]) || (map[row][col] && !breaked))) {
        if (map[row][col]) {
            breaked = true;
        }
        
        tuple<int, int, int, int> next = std::make_tuple(row, col, cost, breaked);
        frontier.push(next);
        visited[row][col][breaked] = true;
        
        return true;
    }
    return false;
}

int BFS(int** map, int N, int M) {
    int row, col, cost;
    bool breaked;
    queue<tuple<int, int, int, int>> frontier;
    bool*** visited;
    
    visited = new bool**[N + 1];
    for (int i = 1; i <= N; i++) {
        visited[i] = new bool*[M + 1];
        for (int j = 1; j <= M; j++) {
            visited[i][j] = new bool[2]{};
        }
    } 
    
    tuple<int, int, int, int> start = std::make_tuple(1, 1, 1, 0);
    frontier.push(start);
    visited[1][1][0] = true;
    
    while (!frontier.empty()) {
        std::tie(row, col, cost, breaked) = frontier.front();
        frontier.pop();
        
        if (row == N && col == M) {
            return cost;
        }
        
        //up
        if (1 < row) {
            if(explore(row - 1, col, cost + 1, breaked, visited, frontier, map) && row - 1 == N && col == M) {
                return cost + 1;
            }
        }
        //down
        if (row < N) {
            if(explore(row + 1, col, cost + 1, breaked, visited, frontier, map) && row + 1 == N && col == M ) {
                return cost + 1;
            }
        }
        //left
        if (1 < col) {
            if(explore(row, col - 1, cost + 1, breaked, visited, frontier, map) && row == N && col - 1 == M) {
                return cost + 1;
            };
        }
        //right
        if (col < M) {
            if(explore(row, col + 1, cost + 1, breaked, visited, frontier, map) && row == N && col + 1 == M) {
                return cost + 1;
            };
        }
    }
    
    return -1;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    int N, M;
    int** map;
    
    cin >> N >> M; cin.get();
    map = new int*[N + 1];
    
    for (int i = 1; i <= N; i++) {
        map[i] = new int[M + 1]{};
        
        for (int j = 1; j <= M; j++) {
            map[i][j] = cin.get() - '0';
        }
        cin.get(); 
    }
    
    cout << BFS(map, N, M);
    
    for (int i = 1; i <= N; i++) {
        delete[] map[i];
    }
    delete[] map;
    
    return 0;
}
