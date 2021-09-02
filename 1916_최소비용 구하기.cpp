#include <iostream>
#include <list>
#include <utility>
#include <queue>
#include <algorithm>
#include <limits.h>
#include <vector>
using std::cin;
using std::cout;
using std::list;
using std::pair;
using std::make_pair;
using std::priority_queue;
using std::fill;
using std::vector;

struct Comp {
    bool operator()(pair<int, int> a, pair<int, int> b) {
        return a.second > b.second;
    }
};


void dijkstra(int start, list<pair<int, int>>* adjList, long long* dist, int N) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, Comp> distPQ;
    
    pair<int, int> temp = make_pair(start, 0);
    dist[start] = 0;
    distPQ.push(temp);
    
    while (!distPQ.empty()) {
        temp = distPQ.top();
        int cur = temp.first;
        int distance = temp.second;
        distPQ.pop();
        
        //only do edge relaxation for newly visited vertex
        if (distance <= dist[cur]) {
            
            for (auto it = adjList[cur].begin(); it != adjList[cur].end(); it++) {
                  long long newPathDist = dist[cur] + it->second;
                  if (newPathDist < dist[it->first]) {
                      dist[it->first] = newPathDist;
                      temp = make_pair(it->first, dist[it->first]);
                      distPQ.push(temp);
                  }
            }
        }
    }
    
}

int main()
{
   int N, M, from, to, cost, start, end;
   list<pair<int, int>>* adjList;
   long long* dist;
   
   cin >> N >> M;
   
   adjList = new list<pair<int, int>>[N + 1];
   dist = new long long[N + 1];
   fill(dist, &dist[N + 1], INT_MAX);
   
   for (int i = 0; i < M; i++) {
       cin >> from >> to >> cost;
       pair<int, int> edge = make_pair(to, cost);
       adjList[from].push_back(edge);
   }
   
   cin >> start >> end;
   
   dijkstra(start, adjList, dist, N);
   
   cout << dist[end];
   
   for (int i = 0; i <= N; i++) {
       adjList[i].clear();
   }
   delete[] adjList;
   
   return 0;
}
