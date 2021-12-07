#include <iostream>
#include <cmath>
#include <list>
#include <utility>
using std::cin;
using std::cout;
using std::log2;
using std::ceil;
using std::list;
using std::pair;

int *Depth, *Distance, **Parent, N, M, cols;
list<pair<int, int>> *Tree;
void DFS(int cur, int curDepth, bool *visited);
int LCA(int A, int B);

int main()
{
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin >> N;
    Tree = new list<pair<int, int>>[N + 1];
    
    for (int i = 1; i < N; i++) {
        int A, B, dist;
        cin >> A >> B >> dist;
        Tree[A].emplace_back(B, dist);
        Tree[B].emplace_back(A, dist);
    }
    
    cols = ceil(log2(N));
    Parent = new int*[N + 1]{};
    for (int i = 0; i <= N; i++) {
        Parent[i] = new int[cols]{};
    }
    
    Parent[1][0] = 1;
    Depth = new int[N + 1]{};
    Distance = new int[N + 1]{};
    bool visited[N + 1]{false, true, };
    
    DFS(1, 0, visited);
    
    //fill Parent table
    for (int j = 1; j < cols; j++) {
        for (int i = 2; i <= N; i++) {
            Parent[i][j] = Parent[Parent[i][j - 1]][j - 1];
        }
    }
    
    cin >> M;
    for (int i = 1; i <= M; i++) {
        int A, B;
        cin >> A >> B;
        
        int leastCommonAncestor = LCA(A, B);
        
        cout << Distance[A] + Distance[B] - 2 * Distance[leastCommonAncestor] << "\n";
    }
    
    for (int i = 0; i <= N; i++) delete[] Parent[i];
    delete[] Tree, Parent, Depth;
    return 0;
}

void DFS(int cur, int curDepth, bool *visited) {
    Depth[cur] = curDepth;
    visited[cur] = true;
    
    for (auto it = Tree[cur].begin(); it != Tree[cur].end(); it++) {
        int next = it->first;
        
        if (!visited[next]) {
            Parent[next][0] = cur;
            Distance[next] = Distance[cur] + it->second;
            DFS(next, curDepth + 1, visited);
        }
    }
}

int LCA(int A, int B) {
    //B가 A보다 깊은 노드여야함
    if (Depth[A] > Depth[B]) {
        int temp = A;
        A = B;
        B = temp;
    }
    
    //depth 맞추기
    for (int i = cols - 1; i >= 0; i--) {
        int jump = 1 << i;
        
        if (Depth[B] - Depth[A] >= jump) B = Parent[B][i];
    }
    
    //A가 B의 ancestor인 경우
    if (A == B) return A;
    
    //Parent 테이블 retrace
    for (int i = cols - 1; i >= 0; i--) {
        if (Parent[A][i] == Parent[B][i]) continue;
        
        A = Parent[A][i];
        B = Parent[B][i];
    }
    
    return Parent[A][0];
}
