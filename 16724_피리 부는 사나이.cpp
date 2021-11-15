#include <iostream>
using std::cin;
using std::cout;

struct mapType {
    char direction;
    bool visited;
};
mapType** map;

struct coord {
    int row;
    int col;
    
    coord(): row(-1), col(-1) {};
    coord(int row, int col): row(row), col(col) {};
    
    bool operator== (coord& B) {
        return (row == B.row) && (col == B.col);
    }
    
    bool operator!= (coord& B) {
        return !(*this == B);
    }
    
    coord next() {
        if (map[row][col].direction == 'U') return coord(row - 1, col);
        else if (map[row][col].direction == 'D') return coord(row + 1, col);
        else if (map[row][col].direction == 'L') return coord(row, col - 1);
        else return coord(row, col + 1);
    }
};
coord** root;

int N, M;
int** rank;


coord getRoot(coord& A);
bool Union(coord A, coord B);
void traverseUntilCycle(coord& cur);

int main()
{
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin >> N >> M;

    root = new coord*[N];
    rank = new int*[N];
    map = new mapType*[N];
    
    for (int i = 0; i < N; i++) {
        root[i] = new coord[M];
        rank[i] =  new int[M];
        map[i] = new mapType[M];
        for (int j = 0; j < M; j++) {
            root[i][j].row = i;
            root[i][j].col = j;
            rank[i][j] = 1;
            cin >> map[i][j].direction;
        }
    }
    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (!map[i][j].visited) {
                coord cur(i, j);
                traverseUntilCycle(cur);
            }
        }
    }
    
    //count disjoint sets
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            coord cur(i, j);
            coord curRoot = getRoot(cur);
            rank[curRoot.row][curRoot.col] = 0;
        }
    }
    
    int ans = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (!rank[i][j]) ans++;
        }
    }
    
    cout << ans;
    return 0;
}

coord getRoot(coord& A) {
    if (A == root[A.row][A.col]) return A;
    else return root[A.row][A.col] = getRoot(root[A.row][A.col]);
}

bool Union(coord A, coord B) {
    A = getRoot(A);
    B = getRoot(B);
    
    if (A != B) {
        if (rank[A.row][A.col] < rank[B.row][B.col]) {
            root[A.row][A.col] = B;
        }
        else {
            root[B.row][B.col] = A;
            if (rank[A.row][A.col] == rank[B.row][B.col]) {
                rank[B.row][B.col]++;
            }
        }
        return true;
    }
    else return false;
}

void traverseUntilCycle(coord& cur) {
    map[cur.row][cur.col].visited = true;
    coord next = cur.next();
    
    //not cycle yet
    if (Union(cur, next)) {
        traverseUntilCycle(next);
    }
}
