#include <iostream>
#include <list>
#include <utility>
#include <queue>
#include <vector>
#define MAX 1000000000
using std::cin;
using std::cout;
using std::list;
using std::pair;
using std::priority_queue;
using std::vector;

struct pathInfo {
    int dest;
    int cost;
    int through;

    pathInfo(int dest, int cost, int through): dest(dest), cost(cost), through(through) {};
};

struct PQComparison { 
    bool operator() (const pathInfo& A, const pathInfo& B) const {
        return A.cost > B.cost;
    }
};

list<pair<int, int>> *graph;
int N, **minDistWithEdges;

int min(int a, int b) { return a < b ? a : b; }
void dijkstra(int S, int D);
void findMinCost(int tax, int D);

int main(void) {
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int M, K, S, D, a, b, w, p, tax = 0;
    cin >> N >> M >> K;
    cin >> S >> D;

    graph = new list<pair<int, int>>[N + 1]{};
    minDistWithEdges = new int*[N + 1];
    for (int i = 0; i <= N; i++) {
        minDistWithEdges[i] = new int[N + 1]{};
        for (int j = 0; j <= N; j++) {
            minDistWithEdges[i][j] = MAX;
        }
    }

    for (int i = 1; i <= M; i++) {
        cin >> a >> b >> w;
        graph[a].emplace_back(b, w);
        graph[b].emplace_back(a, w);
    }

    dijkstra(S, D);

    findMinCost(tax, D);
    for (int i = 1; i <= K; i++) {
        cin >> p;
        tax += p;
        findMinCost(tax, D);
    }

    delete[] graph;
    return 0;
}

void dijkstra(int S, int D) {
    //normal dijkstra
    pair<int, int> dist[N + 1]; //<cost, through>
    for (int i = 0; i <= N; i++) dist[i] = {MAX, MAX};

    priority_queue<pathInfo, vector<pathInfo>, PQComparison> PQ;

    dist[S] = {0, 0};
    PQ.emplace(S, 0, 0);

    while (!PQ.empty()) {
        int cur = PQ.top().dest;
        int curCost = PQ.top().cost;
        int curThrough = PQ.top().through;
        PQ.pop();

        if (dist[cur].first < curCost) continue;

        for (const pair<int, int>& e : graph[cur]) {
            int next = e.first;
            int newCost = curCost + e.second;
            if (newCost < dist[next].first) {
                dist[next] = { newCost, curThrough + 1 };
                PQ.emplace(next, newCost, curThrough + 1);
            }
        }
    }

    //deformed dijkstra
    minDistWithEdges[S][0] = 0;
    PQ.emplace(S, 0, 0);

    while (!PQ.empty()) {
        int cur = PQ.top().dest;
        int curCost = PQ.top().cost;
        int curThrough = PQ.top().through;
        PQ.pop();

        if (minDistWithEdges[cur][curThrough] < curCost || dist[cur].second < curThrough) continue;

        for (const pair<int, int>& e : graph[cur]) {
            int next = e.first;
            int newCost = curCost + e.second;
            if (newCost < minDistWithEdges[next][curThrough + 1]) {
                minDistWithEdges[next][curThrough + 1] = newCost;
                PQ.emplace(next, newCost, curThrough + 1);
            }
        }
    }
}

void findMinCost(int tax, int D) {
    int minCost = MAX;
    for (int i = 1; i <= N; i++) {
        if (minDistWithEdges[D][i] == MAX) continue;
        minCost = min(minCost, minDistWithEdges[D][i] + tax * i);
    }
    cout << minCost << "\n";
}
