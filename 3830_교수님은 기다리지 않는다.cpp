#include <iostream>
#include <utility>
using std::cin;
using std::cout;
using std::pair;

int *root, *dist, *rank;

void Union(int a, int b, int w);
//pair<int, int> getRoot(int cur);
int getRoot(int cur);

int main(void) {
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    char type;
    int N, M, a, b, w;

    while (1) {
        cin >> N >> M;
        if (!N && !M) break;

        root = new int[N + 1]{};
        dist = new int[N + 1]{};
        rank = new int[N + 1]{};

        for (int i = 1; i <= N; i++) {
            root[i] = i;
            rank[i] = 1;
        }

        for (int i = 1; i <= M; i++) {
            cin >> type;
            if (type == '!') {
                cin >> a >> b >> w;
                Union(a, b, w);
            }
            if (type == '?') {
                cin >> a >> b;
                
                if (getRoot(a) != getRoot(b)) cout << "UNKNOWN\n";
                else cout << dist[a] - dist[b] << "\n";
            }
        }
        
        delete[] root, dist, rank;
    }

    return 0;
}

void Union(int a, int b, int w) {
    int A = getRoot(a);
    int B = getRoot(b);

    if (A == B) return;

    if (rank[A] < rank[B]) {
        root[A] = B;
        dist[A] = w - dist[a] + dist[b];
    }
    else {
        root[B] = A;
        dist[B] = -1 * w + dist[a] - dist[b];

        if (rank[A] == rank[B]) {
            rank[A]++;
        }
    }
}   
int getRoot(int cur) {
    if (cur == root[cur]) return cur;

    int Root = getRoot(root[cur]);
    dist[cur] += dist[root[cur]];

    return root[cur] = Root;
}
