#include <iostream>
#include <math.h>
#include <list>
#include <utility>
using std::cin;
using std::cout;
using std::log2;
using std::list;
using std::pair;

int*energy, N; 
list<pair<int, int>> *graph;    
pair<int, int> **dist;  // <step, distance>

void dfs(int cur);
void findAnswer(int cur);

int main(void) {
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int a, b, c, log2Height;
    
    cin >> N;

    log2Height = (int)log2(N) + 1;
    dist = new pair<int, int>*[N + 1];
    for (int i = 0; i <= N; i++) {
        dist[i] = new pair<int, int>[log2Height]{};
    }

    energy = new int[N + 1]{};
    for (int i = 1; i <= N; i++) cin >> energy[i];

    graph = new list<pair<int, int>>[N + 1]{};
    for (int i = 1; i < N; i++) {
        cin >> a >> b >> c;
        graph[a].emplace_back(b, c);
        graph[b].emplace_back(a, c);
    }
    
    dist[1][0] = {1, 0};
    dfs(1);

    for (int j = 1; j < log2Height; j++) {
        for (int i = 1; i <= N; i++) {
            const pair<int, int>& ancestor = dist[dist[i][j - 1].first][j - 1];
            dist[i][j] = { ancestor.first , dist[i][j - 1].second + ancestor.second };
        }
    }

    for (int i = 1; i <= N; i++) {
        findAnswer(i);
    }

    for (int i = 0; i <= N; i++) delete[] dist[i];
    delete[] energy, graph, dist;
    return 0;
}

void dfs(int cur) {
    for (const pair<int, int>& edge : graph[cur]) {
        // dist[u][0] (parent) 가 곧 visited를 대신함
        if (dist[edge.first][0].first) continue;

        dist[edge.first][0] = { cur, edge.second };
        dfs(edge.first);
    }
}

void findAnswer(int cur) {
    int energyLeft = energy[cur];
    for (int j = (int)log2(N); j >= 0; j--) {
        if (energyLeft < dist[cur][j].second) continue;

        energyLeft -= dist[cur][j].second;
        cur = dist[cur][j].first;
    }

    cout << cur << "\n";
}
