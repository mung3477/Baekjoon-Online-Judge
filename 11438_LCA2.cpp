#include <iostream>
#include <list>
using std::cin;
using std::cout;
using std::list;


int N, **ancestor, *depth;
list<int> *graph;

void DFS(int cur, int curDepth);
int LCA(int A, int B);

int main(void) {
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    int M, a, b;
    cin >> N;

    ancestor = new int*[N + 1]{};
    for (int i = 0; i <= N; i++) ancestor[i] = new int[18]{};

    depth = new int[N + 1]{};
    for (int i = 0; i <= N; i++) depth[i] = -1;
    graph = new list<int>[N + 1]{};

    for (int i = 1; i < N; i++) {
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }   

    ancestor[1][0] = 0;
    DFS(1, 0);

    for (int j = 1; j <= 17; j++) {
        for (int i = 2; i <= N; i++) {
            ancestor[i][j] = ancestor[ancestor[i][j - 1]][j - 1];
        }
    }

    cin >> M;
    for (int i = 1; i <= M; i++) {
        cin >> a >> b;
        cout << LCA(a, b) << "\n";
    }

    for (int i = 0; i <= N; i++) delete[] ancestor[i];
    delete ancestor, depth, graph;
    return 0;
}

void DFS(int cur, int curDepth) {
    depth[cur] = curDepth;

    for (int next : graph[cur]) {
        if (depth[next] != -1) continue;

        ancestor[next][0] = cur;
        DFS(next, curDepth + 1);
    }
}

/**
 * @brief 
 *  1. Make their depth same. 
 *  2. Find their least common ancestor.
 * 
 * @param A 
 * @param B 
 * @return int 
 */
int LCA(int A, int B) {
    if (depth[A] > depth[B]) {
        int temp = A;
        A = B;
        B = temp;
    }

    for (int i = 0, jump, diff = depth[B] - depth[A]; (jump = 1 << i) <= diff; i++) {
        if (jump & diff) {
            B = ancestor[B][i];
        }
    }

    if (A == B) return A;

    for (int distance = 17; 0 <= distance; distance--) {
        if (ancestor[A][distance] != ancestor[B][distance]) {
            A = ancestor[A][distance];
            B = ancestor[B][distance];
        }
    }

    return ancestor[A][0];
}
