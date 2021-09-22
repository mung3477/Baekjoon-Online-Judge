#include <iostream>
#include <queue>
#include <vector>
using std::cin;
using std::cout;
using std::queue;
using std::vector;

struct point {
  int row;
  int col;
  point(): row(-1), col(-1) {};
  point(int row, int col): row(row), col(col) {};
};

int N, M;
int** map;
vector<point> virus;

int max(int a, int b) {
    if (a > b) return a;
    else return b;
}

void expand(int** tempMap, bool** visited, queue<point>& frontier, int row, int col) {
    if (!tempMap[row][col]) {
        tempMap[row][col] = 2;
        visited[row][col] = 1;
        frontier.push(point(row, col));
    }
}

int BFS() {
    int safeArea = 0;
    queue<point> frontier;
    bool** visited = new bool*[N];
    int** tempMap = new int*[N];
    for (int i = 0; i < N; i++) {
        tempMap[i] = new int[M];
        visited[i] = new bool[M]{};
        for (int j = 0; j < M; j++) {
            tempMap[i][j] = map[i][j];
        }
    }
    
    for (auto it = virus.begin(); it != virus.end(); it++) {
        point start = *it;
        frontier.push(start);
        visited[start.row][start.col] = 1;
        
        while (!frontier.empty()) {
            point cur = frontier.front();
            frontier.pop();
            
            if (0 < cur.row) {
                expand(tempMap, visited, frontier, cur.row - 1, cur.col);
            }
            if (cur.row < N - 1) {
                expand(tempMap, visited, frontier, cur.row + 1, cur.col);
            }
            if (0 < cur.col) {
                expand(tempMap, visited, frontier, cur.row, cur.col - 1);
            }
            if (cur.col < M - 1) {
                expand(tempMap, visited, frontier, cur.row, cur.col + 1);
            }
        }
        
    }
    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (!tempMap[i][j]) safeArea++;
        }
    }
    
    for (int i = 0; i < N; i++) {
        delete[] tempMap[i], visited[i];
    }
    delete[] tempMap, visited;
    
    return safeArea;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    int maxSafe = 0;
    cin >> N >> M;
    
    map = new int*[N];
    for (int i = 0; i < N; i++) {
        map[i] = new int[M];
        for (int j = 0; j < M; j++) {
           cin >> map[i][j];
           if (map[i][j] == 2) virus.push_back(point(i, j));
        }
    }
    
    /*
        벽 세 개 세우기
        row: index / M, col: index % M
    */
    for (int i = 0; i < N * M; i++) {
        if (map[i / M][i % M]) continue;
        else {
            map[i / M][i % M] = 1;
            for (int j = i + 1; j < N * M; j++) {
                if (map[j / M][j % M]) continue;
                else {
                    map[j / M][j % M] = 1;
                    for (int k = j + 1; k < N * M; k++) {
                        if (map[k / M][k % M]) continue;
                        else {
                            map[k / M][k % M] = 1;
                            maxSafe = max(BFS(), maxSafe);
                            map[k / M][k % M] = 0;
                        }
                    }   
                    map[j / M][j % M] = 0;
                }
            }
            map[i / M][i % M] = 0;
        }
    }
    
    cout << maxSafe;
   
   return 0;
}
