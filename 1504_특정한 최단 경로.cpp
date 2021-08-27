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

struct Comp {
    bool operator()(pair<int, int> a, pair<int, int> b) {
        return a.second > b.second;
    }
};

void dijkstraFrom(int s, int** adjMat, long long* dist, int N) {
    priority_queue<pair<int, int>, std::vector<pair<int, int>>, Comp> pq; 
    
    //s에서 dist와 distpq 초기화
    for (int i = 1; i <= N; i++) {
        if (i == s) {
            dist[i] = 0;
        }
        else if (adjMat[s][i]) {
            dist[i] = adjMat[s][i];
            
            pair<int, int> edge = make_pair(i, dist[i]);
            pq.push(edge);
        }
    }
    
    //반복
    while (!pq.empty()) {
        pair<int, int> cur = pq.top();
        int curNode = cur.first;
        pq.pop()
            
        for (int i = 1; i <= N; i++) {
            if (adjMat[curNode][i]) {
                int newPathCost = dist[curNode] + adjMat[curNode][i];
                if (dist[i] > newPathCost) {
                    dist[i] = newPathCost;
                    
                    pair<int, int> newDist = make_pair(i, dist[i]);
                    pq.push(newDist);
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
    
    int N, E, from, to, cost, A, B;
    int sources[3]{1, 0, 0};
    cin >> N >> E;
    
    int** adjMat = new int*[N + 1];
    for (int i = 0; i <= N; i++) {
        adjMat[i] = new int[N + 1]{};
    }
    //순서대로 index 0부터 from 1, A, B
    long long** distFromT = new long long*[3];
    for (int i = 0; i < 3; i++) {
        distFromT[i] = new long long[N + 1];
        fill(distFromT[i], &distFromT[i][N + 1], INT_MAX);
    }
    
    for (int i = 0; i < E; i++) {
        cin >> from >> to >> cost;
        adjMat[from][to] = adjMat[to][from] = cost;
    }
    
    cin >> sources[1] >> sources[2];
    A = sources[1]; B = sources[2];
    
    for (int i = 0; i < 3; i++) {
        dijkstraFrom(sources[i], adjMat, distFromT[i], N);
    }
    
    //source->A->B->dest 최단거리
    long long sABN = distFromT[0][A] + distFromT[1][B] + distFromT[2][N];
    if ((distFromT[0][A] == INT_MAX) || (distFromT[1][B] == INT_MAX) || (distFromT[2][N] == INT_MAX)) {
        sABN = INT_MAX;
    }
    
    //source->A->B->dest 최단거리
    long long sBAN = distFromT[0][B] + distFromT[2][A] + distFromT[1][N];
    if ((distFromT[0][B] == INT_MAX) || (distFromT[2][A] == INT_MAX) || (distFromT[1][N] == INT_MAX)) {
        sBAN = INT_MAX;
    }
    
    long long ans = (sABN < sBAN ? sABN : sBAN);
    if (ans == INT_MAX) ans = -1;
    
    cout << ans;
    
    return 0;
}
