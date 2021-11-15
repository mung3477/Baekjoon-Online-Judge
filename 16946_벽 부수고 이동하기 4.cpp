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
char** map;
int** reachable;
bool** visited;
queue<point> trace;
vector<int> blankAreas;

void fillReachableCaller(int row, int col);
void fillReachable(int row, int col);
bool notUsedYet(vector<int>& blankAreaUsed, int nextAreaIndex);
void WereItNotAWall(int row, int col);

int main()
{
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin >> N >> M;
    map = new char*[N];
    reachable = new int*[N];
    visited = new bool*[N];
    for (int i = 0; i < N; i++) {
        map[i] = new char[M];
        reachable[i] = new int[M]{};
        visited[i] = new bool[M]{};
        for (int j = 0; j < M; j++) cin >> map[i][j];
    }
    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            //빈 공간 크기 측정
            if (map[i][j] == '0' && !visited[i][j]) {
                fillReachableCaller(i, j);
            }
        }
    }
    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M ; j++) {
            if (map[i][j] == '1') WereItNotAWall(i, j);
            else cout << "0";
        }
        cout << "\n";
    }
    
    return 0;
}

void fillReachableCaller(int row, int col) {
    fillReachable(row, col);
    
    
    int blankAreaIndex = blankAreas.size();
    blankAreas.push_back(trace.size());
    
    while (!trace.empty()) {
        point cur = trace.front();
        reachable[cur.row][cur.col] = blankAreaIndex;
        
        trace.pop();
    }   
}

//DFS
void fillReachable(int row, int col) {
    trace.emplace(row, col);
    visited[row][col] = true;

    //try up
    if (0 < row && map[row - 1][col] == '0' && !visited[row - 1][col]) 
        fillReachable(row - 1, col);
    
    
    //try down
    if (row < N - 1 && map[row + 1][col] == '0' && !visited[row + 1][col]) 
        fillReachable(row + 1, col);
    
    
    //try left
    if (0 < col && map[row][col - 1] == '0' && !visited[row][col - 1]) 
        fillReachable(row, col - 1);
    
    
    //try right
    if (col < M - 1 && map[row][col + 1] == '0' && !visited[row][col + 1]) 
        fillReachable(row, col + 1);
    
}

bool notUsedYet(vector<int>& blankAreaUsed, int nextAreaIndex) {
    for (int usedArea : blankAreaUsed) {
        if (usedArea == nextAreaIndex) return false;
    }
    return true;
}

void WereItNotAWall(int row, int col) {
    int ifReachable = 1, nextAreaIndex;
    vector<int> blankAreaUsed;
    
    if (0 < row && map[row - 1][col] == '0' && notUsedYet(blankAreaUsed, reachable[row - 1][col])) {
        nextAreaIndex = reachable[row - 1][col];
        
        ifReachable += blankAreas.at(nextAreaIndex);
        blankAreaUsed.push_back(nextAreaIndex);
    }
    
    if (row < N - 1 && map[row + 1][col] == '0' && notUsedYet(blankAreaUsed, reachable[row + 1][col])) {
        nextAreaIndex = reachable[row + 1][col];
        
        ifReachable += blankAreas.at(nextAreaIndex);
        blankAreaUsed.push_back(nextAreaIndex);
    }
        
    if (0 < col && map[row][col - 1] == '0' && notUsedYet(blankAreaUsed, reachable[row][col - 1])) {
        nextAreaIndex = reachable[row][col - 1];
        
        ifReachable += blankAreas.at(nextAreaIndex);
        blankAreaUsed.push_back(nextAreaIndex);
    }
        
   
    if (col < M - 1 && map[row][col + 1] == '0' && notUsedYet(blankAreaUsed, reachable[row][col + 1])) {
        nextAreaIndex = reachable[row][col + 1];
        ifReachable += blankAreas.at(nextAreaIndex);
    }
    
    cout << ifReachable % 10;
}
