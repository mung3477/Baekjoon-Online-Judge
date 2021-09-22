#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <limits.h>
using std::cin;
using std::cout;
using std::priority_queue;
using std::vector;
using std::fill;

struct distElem {
    int node;
    int dist;
    
    distElem(): node(0), dist(INT_MAX) {};
    distElem(int node, int dist): node(node), dist(dist) {};
};

struct Comp {
    bool operator() (distElem& a, distElem& b) {
        return a.dist > b.dist;
    }
};

int N, M, R;
int** adjMat;
int* items;

int dijkstra(int source, int range) {
    int newPathCost, itemGrabbed = 0;
    int dist[N + 1];
    fill(dist, &dist[N + 1], INT_MAX);
    priority_queue<distElem, vector<distElem>, Comp> distPQ;
    
    //initiate
    dist[source] = 0;
    distPQ.push(distElem(source, 0));
    
    while (!distPQ.empty()) {
        distElem cur = distPQ.top();
        distPQ.pop();
        
        if (cur.dist <= dist[cur.node]) {
            for (int j = 1; j <= N; j++) {
                if (adjMat[cur.node][j]) {
                    newPathCost = cur.dist + adjMat[cur.node][j];
                    if (newPathCost < dist[j]) {
                        dist[j] = newPathCost;
                        distPQ.push(distElem(j, dist[j]));
                    }
                }
            }
        }
    }
    
    for (int i = 1; i <= N; i++) {
        if (dist[i] <= range) itemGrabbed += items[i];
    }
    
    return itemGrabbed;
}

int max(int a, int b) {
    if (a > b) return a;
    else return b;
}

int min(int a, int b) {
    if (a > b) return b;
    else return a;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    int from, to, cost, maxItems = 0;
    cin >> N >> M >> R;
    
    items = new int[N + 1];
    adjMat = new int*[N + 1];
    for (int i = 1; i <= N; i++) {
        adjMat[i] = new int[N + 1]{};
        
        cin >> items[i];
    }
    
    for (R; R > 0; R--) {
        cin >> from >> to >> cost;
        adjMat[from][to] = adjMat[to][from] = (adjMat[from][to] ? min(cost, adjMat[from][to]) : cost);
    }
    
    
    for (int i = 1; i <= N; i++) {
        int item;
        bool* visited = new bool[N + 1]{};
        
        maxItems = max(maxItems, dijkstra(i, M));
        
        delete[] visited;
    }
    
    cout << maxItems;
   
    return 0;
}
