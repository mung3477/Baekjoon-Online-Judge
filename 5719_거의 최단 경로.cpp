#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <functional>
#include <limits.h>
using std::cin;
using std::cout;
using std::vector;
using std::priority_queue;
using std::pair;    // <distance, number>
using std::greater;

int N;
int** map;

int min(int a, int b) {
    if (a < b) return a;
    else return b;
}

int* dijkstra(int s);
void eraseMinPathes(int* minDist, int cur, int curDist);

int main(void) {
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    int M, s, d, from, to, cost, *minDist;

    while (1) {
        cin >> N >> M;
        if (!N && !M) break;

        map = new int*[N + 1];
        for (int i = 0; i <= N; i++) map[i] = new int[N + 1]{};

        cin >> s >> d;
        // compose the map
        for (int i = 1; i <= M; i++) {
            cin >> from >> to >> cost;
            map[from][to] = cost;
        }

        // find min dist to all nodes
        minDist = dijkstra(s);

        // erase minimum pathes
        eraseMinPathes(minDist, d, minDist[d]);

        // find almost min path
        cout << dijkstra(s)[d] << "\n";
        
        for (int i = 0; i <= N; i++) delete[] map[i];
        delete[] map, minDist;
    }

    return 0;
}

int* dijkstra(int s) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> minDistPQ;
    int* minDist = new int[N + 1]{};
    for (int i = 0; i <= N; i++) minDist[i] = INT_MAX;

    // initialize
    minDistPQ.emplace(0, s);

    // iterate
    while (!minDistPQ.empty()) {
        int curNodeDist = minDistPQ.top().first, curNode = minDistPQ.top().second;
        minDistPQ.pop();
        
        // if not visited
        if (curNodeDist < minDist[curNode]) {
            minDist[curNode] = curNodeDist;

            for (int i = 0; i < N; i++) {
                if (i == curNode || !map[curNode][i]) continue;

                int newPathCost = minDist[curNode] + map[curNode][i];
                if (newPathCost < minDist[i]) {
                    minDistPQ.emplace(newPathCost, i);
                }
            }
        }
    }

    for (int i = 0; i <= N; i++) if (minDist[i] == INT_MAX) minDist[i] = -1;
    return minDist;
}
void eraseMinPathes(int* minDist, int cur, int curDist) {
    for (int i = 0; i < N; i++) {
        if (map[i][cur] && minDist[i] + map[i][cur] == curDist) {
            int pathCost = map[i][cur];
            map[i][cur] = 0;    //erase the path
            eraseMinPathes(minDist, i, curDist - pathCost);
        }
    }
}
