#include <iostream>
#include <list>
#include <set>
#include <algorithm>
using std::cin;
using std::cout;
using std::list;
using std::set;

int V, *DFSNum;
list<int> *graph;
set<int> ArticulationPoints;

int DFS(int cur, int root, int& curNum);
int min(int a, int b) {
    if (a < b) return a;
    else return b;
}

int main(void) {
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    int E, from, to, curNum = 1;
    cin >> V >> E;

    // create given graph
    graph = new list<int>[V + 1]{};
    for (int i = 1; i <= E; i++) {
        cin >> from >> to;
        graph[from].push_back(to);
        graph[to].push_back(from);
    }

    // make DFS tree
    DFSNum = new int[V + 1]{};
    for (int i = 1; i <= V; i++) {
        if (!DFSNum[i]) DFS(i, i, curNum);
    }

    cout << ArticulationPoints.size() << "\n";
    for (const int& data : ArticulationPoints) {
        cout << data << " ";
    }

    ArticulationPoints.clear();
    for (int i = 1; i <= V; i++) graph[i].clear();
    delete[] graph, visited, DFSNum;
    
    return 0;
}


int DFS(int cur, int root, int& curNum) {
    int highestReachable = curNum, child = 0;
    DFSNum[cur] = curNum++;

    for (int next : graph[cur]) {
        if (DFSNum[next]) {
            highestReachable = min(highestReachable, DFSNum[next]);
            continue;
        }

        child += 1;
        int childHighestReachable = DFS(next, root, curNum);
        
        /** 
         * Articulation point detect criteria :
         * 1. child's highest reachable point is me
         * 2. if current node is root, it should have at least 2 children
         * 
        */
        if ((childHighestReachable >= DFSNum[cur]) && (cur != root))) {
            ArticulationPoints.insert(cur);
        }
        highestReachable = min(highestReachable, childHighestReachable);
    }

    if (cur == root && child > 1) ArticulationPoints.insert(cur);

    return highestReachable;
}
