#include <iostream>
#include <queue>
#include <vector>
#include <list>
#include <utility>
#include <limits.h>
#include <algorithm>
using std::cin;
using std::cout;
using std::priority_queue;
using std::list;
using std::pair;
using std::make_pair;
using std::fill;

//cost가 큰 게 top으로 오게끔
struct Comp {
    bool operator()(pair<int, int> a, pair<int, int> b) {
        return a.second > b.second;
    }
};

void dijkstraFromX(int* fromX, list<pair<int, int>>* adjList, int X, int N) {
    //지금 닿을 수 있는 노드들
    priority_queue<pair<int, int>, std::vector<pair<int, int>>, Comp> pq;
    bool* visited = new bool[N + 1]{};
    visited[X] = true;
    //몇 개나 visited에 들어있는지
    int visitedVertexes = 1;
    
    //X에서 갈 수 있는 노드들 pq에 추가
    for (auto it = adjList[X].begin(); it != adjList[X].end(); it++) {
        fromX[it->first] = it->second;
        pq.push(*it);
    }
    
    //iterate
    while (visitedVertexes != N) {
        //갈 수 있는 노드 중 가장 가까운 노드 선택. 
        pair<int, int> cur = pq.top();
        int curVertex = cur.first;
        pq.pop();
        
        //아직 안 갔던 노드면 fromX 업데이트 진행.
        if (!visited[curVertex]) { 
            visited[curVertex] = true;
            visitedVertexes++;
            
            //curVertex를 경유하는 새로운 길이 생겼으니 curVertex 주변 노드들의 거리 업데이트
            for (auto it = adjList[curVertex].begin(); it != adjList[curVertex].end(); it++) {
                int newPathCost = fromX[curVertex] + it->second;
                
                //이미 Visited에 들어있는 노드는 어차피 if문이 성립할 수 없어 거리 값이 업데이트 되지 않음.
                if (newPathCost < fromX[it->first]) {
                    fromX[it->first] = newPathCost;
                    pair<int, int> temp = make_pair(it->first, newPathCost);
                    pq.push(temp);
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
    
    int N, M, X, from, to, cost, ans = 0;
    cin >> N >> M >> X;
    
    list<pair<int, int>>* adjList = new list<pair<int, int>>[N + 1];
    list<pair<int, int>>* reverseAdjList = new list<pair<int, int>>[N + 1];
    int* fromX = new int[N + 1]; 
    int* toX = new int[N + 1];
    fill(fromX, &fromX[N + 1], INT_MAX); fromX[X] = 0;
    fill(toX, &toX[N + 1], INT_MAX); toX[X] = 0;
    
    for (int i = 0; i < M; i++) {
        cin >> from >> to >> cost;
        pair<int, int> edge = make_pair(to, cost);
        pair<int, int> reverseEdge = make_pair(from, cost);
        adjList[from].push_back(edge);
        reverseAdjList[to].push_back(reverseEdge);
    }
    
    dijkstraFromX(fromX, adjList, X, N);
    dijkstraFromX(toX, reverseAdjList, X, N);
    
    for (int i = 1; i <= N; i++) {
        int dist = toX[i] + fromX[i];
        if (i != X && ans < dist) {
            ans = dist;
        }
    }
    
    cout << ans;
    
    return 0;
}
