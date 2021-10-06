#include <iostream>
#include <queue>
#include <utility>
#include <vector>
#include <list>
#include <limits.h>
using std::cin;
using std::cout;
using std::pair;    //node, distance
using std::priority_queue;
using std::list;

list<pair<int, int>>* adjList;   //길이 없음 == INT_MAX
int N;

struct Comp {
    bool operator()(pair<int, int>& a, pair<int, int>& b) {
        return a.second > b.second || (a.second == b.second && a.first > b.first);
    }  
};

int min(int a, int b) {
    if (a < b) return a;
    else return b;
}

int max(int a, int b) {
    if (a > b) return a;
    else return b;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    int M, v1, v2, cost, sum = 0, maxEdge = 0;
    
    cin >> N >> M;
    
    adjList = new list<pair<int, int>>[N + 1];
    
    for (M; M > 0; M--) {
        cin >> v1 >> v2 >> cost;
        adjList[v1].emplace_back(v2, cost);
        adjList[v2].emplace_back(v1, cost);
    }
    
    //prim
    priority_queue<pair<int, int>, std::vector<pair<int, int>>, Comp> distPQ;
    bool visited[N + 1]{};
    int* dist = new int[N + 1];
    std::fill(dist, &dist[N + 1], INT_MAX);
    
    //start from 1
    dist[1] = 0;
    distPQ.emplace(1, 0);
    
    while (!distPQ.empty()) {
        pair<int, int> cur = distPQ.top();
        distPQ.pop();
        
        if (visited[cur.first]) continue;
        
        visited[cur.first] = true;
        //expand from cur.front
        for (auto it = adjList[cur.first].begin(); it != adjList[cur.first].end(); it++) {
            if (!visited[it->first]) {
                int newDist = it->second;
                if (newDist < dist[it->first]) {
                    dist[it->first] = newDist;
                    distPQ.emplace(it->first, newDist);
                }
            }
        }
    }
    
    for (int i = 1; i <= N; i++) {
        sum += dist[i];
        maxEdge = max(maxEdge, dist[i]);
    }
    
    cout << sum - maxEdge;
    
    return 0;
}
