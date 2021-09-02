#include <iostream>
#include <list>
#include <utility>
using std::cin;
using std::cout;
using std::list;
using std::pair;
using std::make_pair;

void dfs(int cur, int curCost, list<pair<int, int>>* adjList, bool* visited, int& farthest, int& maxCost){
    bool isLeaf = true;
    visited[cur] = true;
    
    for (auto it = adjList[cur].begin(); it != adjList[cur].end(); it++) {
        if (!visited[it->first]) {
            dfs(it->first, curCost + it->second, adjList, visited, farthest, maxCost);
            isLeaf = false;
        }
    }
    
    if (isLeaf && maxCost < curCost) {
        maxCost = curCost;
        farthest = cur;
    }
    visited[cur] = false;
}

pair<int, int> dfs_call(int start, list<pair<int, int>>* adjList, int N) {
    int maxCost = 0;
    int farthest;
    bool visited[N + 1]{};
    
    dfs(start, 0, adjList, visited, farthest, maxCost);
    return make_pair(farthest, maxCost);
}

int main()
{
   int N, from, to, cost;
   list<pair<int, int>>* adjList;
   
   cin >> N;
   adjList = new list<pair<int, int>>[N + 1];
   
   for (int i = 1; i < N; i++) {
       cin >> from >> to >> cost;
       pair<int, int> edge = make_pair(to, cost);
       pair<int, int> reversed = make_pair(from, cost);
       adjList[from].push_back(edge);
       adjList[to].push_back(reversed);
   }
   
   pair<int, int> start = dfs_call(1, adjList, N);
   pair<int, int> answer = dfs_call(start.first, adjList, N);
   
   cout << answer.second;
   
   return 0;
}
