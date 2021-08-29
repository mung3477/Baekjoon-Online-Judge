#include <iostream>
#include <queue>
#include <utility>
#include <list>
#include <limits.h>
#include <algorithm>
#include <vector>
using std::cin;
using std::cout;
using std::priority_queue;
using std::pair;
using std::make_pair;
using std::list;
using std::fill;

struct Comp {
    bool operator()(pair<int, int> a, pair<int, int> b) {
        return a.second > b.second;
    }
};

void dijkstra(int source, long long* dist, list<pair<int, int>>* adjList, int V) {
    //initialize
    priority_queue<pair<int, int>, std::vector<pair<int, int>>, Comp> distPQ;
    bool visited[V + 1]{};
    dist[source] = 0;
    
    pair<int, int> start = make_pair(source, 0);
    distPQ.push(start);
    
    //iterate
    while (!distPQ.empty()) {
        pair<int, int> cur = distPQ.top();
        distPQ.pop();
        if (!visited[cur.first]) {
            visited[cur.first] = true;
            
            //expand from current node
            for (auto it = adjList[cur.first].begin(); it != adjList[cur.first].end(); it++) {
                long long newPathCost = dist[cur.first] + it->second;
                if (newPathCost < dist[it->first]) {
                    dist[it->first] = newPathCost;
                    pair<int, int> newDist = make_pair(it->first, dist[it->first]);
                    distPQ.push(newDist);
                }
            }
        }
    }
}

int main()
{
   std::ios_base::sync_with_stdio(false);
   cin.tie(NULL);
   cout.tie(NULL);
   
   int V, E, source, from, to, cost;
   long long* dist;
   list<pair<int, int>>* adjList;
   cin >> V >> E >> source;
   
   dist = new long long[V + 1];
   fill(dist, &dist[V + 1], INT_MAX);
   
   adjList = new list<pair<int, int>>[V + 1];
   for (int i = 0; i < E; i++) {
       cin >> from >> to >> cost;
       
       pair<int, int> edge = make_pair(to, cost);
       adjList[from].push_back(edge);
   }
   
    dijkstra(source, dist, adjList, V);
    
    for (int i = 1; i <= V; i++) {
        if (dist[i] != INT_MAX) {
            cout << dist[i];
        }
        else {
            cout << "INF";
        }
        
        cout << "\n";
    }
   
   for (int i = 0; i <= V; i++) {
       adjList[i].clear();
   }
   delete[] adjList;
   return 0;
}
