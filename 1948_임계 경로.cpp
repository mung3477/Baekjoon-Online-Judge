#include <iostream>
#include <queue>
#include <list>
#include <utility>
using std::cin;
using std::cout;
using std::queue;
using std::list;
using std::pair;

int main(void) {
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int *inDegree;
    long long* trace;
    bool *visited;
    list<pair<short, short>>* map;
    list<pair<short, short>>* reversedMap;
    bool **used;
    queue<short> frontier;

    int N, M, start, end, roadCount = 0;
    cin >> N >> M;

    inDegree = new int[N + 1]{};
    trace = new long long[N + 1]{};
    visited = new bool[N + 1]{};
    map = new list<pair<short, short>>[N + 1]{};
    reversedMap = new list<pair<short, short>>[N + 1]{};
    used = new bool*[N + 1];
    for (int i = 0; i <= N; i++) {
        used[i] = new bool[N + 1]{};
    }

    for (int i = 1; i <= M; i++) {
        int from, to, cost;
        cin >> from >> to >> cost;
        map[from].emplace_back(to, cost);
        reversedMap[to].emplace_back(from, cost);
        inDegree[to] += 1;
    }

    cin >> start >> end;

    frontier.push(start);

    while (!frontier.empty()) {
        short cur = frontier.front();
        frontier.pop();

        for (auto it = map[cur].begin(); it != map[cur].end(); it++) {
            short next = it->first;
            long long newCost = trace[cur] + it->second;

            if (trace[next] < newCost) {
                trace[next] = newCost;
            }

            inDegree[next] -= 1;
            if (inDegree[next] == 0) frontier.push(next);
        }
    }

    //최대 거리 경로에 쓰인 도로 개수 찾기
    frontier.push(end);
    visited[end] = true;

    while (!frontier.empty()) {
        short cur = frontier.front();
        frontier.pop();

        for (auto it = reversedMap[cur].begin(); it != reversedMap[cur].end(); it++) {
            short prev = it->first;
            
            //도로가 있고, 그게 아직 세지 않은, 최대 거리 경로를 구성하는 도로라면
            if (!used[prev][cur] && (trace[cur] - it->second == trace[prev])) {
                roadCount += 1;
                used[prev][cur] = true;
                if (!visited[prev]) {
                    frontier.push(prev);
                    visited[prev] = true;
                }
            }
        }
    }

    cout << trace[end] << "\n" << roadCount;

    for (int i = 0; i <= N; i++) delete[] used[i];
    delete[] inDegree, trace, visited, map, used;

    return 0;
}
