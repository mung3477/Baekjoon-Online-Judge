#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <utility>
using std::cin;
using std::cout;
using std::vector;
using std::list;
using std::sort;
using std::pair;
using std::make_pair;

int visitOrder, *DFSNum;
list<int> *graph;
vector<pair<int, int>> ArticulationEdges;

int min(int a, int b) {
    if (a < b) return a;
    else return b;
}

int findArticulationEdgeWithDFS(int cur, int parent);

int main(void) {
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    int V, E, x, y, able = 1;
    cin >> V >> E;

    DFSNum = new int[V + 1]{};
    graph = new list<int>[V + 1]{};

    for (int i = 1; i <= E; i++) {
        cin >> x >> y;
        graph[x].push_back(y);
        graph[y].push_back(x);
    }

    findArticulationEdgeWithDFS(1, V + 1);

    cout << ArticulationEdges.size() << "\n";
    sort(ArticulationEdges.begin(), ArticulationEdges.end());

    for (const pair<int, int>& answer : ArticulationEdges) {
        cout << answer.first << " " << answer.second << "\n";
    }

    delete[] DFSNum, graph;
    return 0;
}

int findArticulationEdgeWithDFS(int cur, int parent) {
    DFSNum[cur] = ++visitOrder;

    int reachableHighest = DFSNum[cur];

    for (const int& next : graph[cur]) {
        if (next == parent) continue;

        // if the node was visited during current DFS, just compare reachable highset
        else if (DFSNum[next]) {
            reachableHighest = min(reachableHighest, DFSNum[next]);
            continue;
        }

        int childReachableHighest = findArticulationEdgeWithDFS(next, cur);
        reachableHighest = min(reachableHighest, childReachableHighest);

        // if this edge is the only way to reach next subgraph
        if (childReachableHighest > DFSNum[cur]) {
            ArticulationEdges.push_back((cur < next ? make_pair(cur, next) : make_pair(next, cur)));
        }
    }

    return reachableHighest;
}
