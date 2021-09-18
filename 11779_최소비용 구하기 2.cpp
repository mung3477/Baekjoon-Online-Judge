#include <iostream>
#include <queue>
#include <limits.h>
#include <algorithm>
#include <stack>
#include <vector>
using std::cin;
using std::cout;
using std::priority_queue;
using std::fill;
using std::stack;

struct distElem {
    int node;
    int dist;
    distElem(): node(0), dist(INT_MAX) {};
    distElem(int node, int dist): node(node), dist(dist) {};
};

struct Compare {
    bool operator()(distElem& a, distElem& b) {
        return a.dist > b.dist;
    }
};

int N, M;
int* dist;
int* before;
int** adjMat;

int min(int a, int b) {
    if (a > b) return b;
    else return a;
}

void dijkstra(int depart) {
    //initialize
    priority_queue<distElem, std::vector<distElem>, Compare> distPQ;
    dist[depart] = 0;
    before[depart] = depart;
    distPQ.push(distElem(depart, dist[depart]));
    
    while (!distPQ.empty()) {
        distElem cur = distPQ.top();
        distPQ.pop();
        
        if (cur.dist <= dist[cur.node]) {
            for (int i = 1; i <= N; i++) {
                if (adjMat[cur.node][i] != -1) {
                    int newPathCost = cur.dist + adjMat[cur.node][i];
                    if (newPathCost < dist[i]) {
                        dist[i] = newPathCost;
                        before[i] = cur.node;
                        distPQ.push(distElem(i, dist[i]));
                    }
                }
            }
        }
    }
}

int main()
{
   int from, to, cost, depart, arrive, cur;
   stack<int> path;
   
   cin >> N >> M;
   
   dist = new int[N + 1];
   fill(dist, &dist[N + 1], INT_MAX);
   before = new int[N + 1]{};
   adjMat = new int*[N + 1]{};
   for (int i = 0; i <= N; i++) {
       adjMat[i] = new int[N + 1]{};
       fill(adjMat[i], &adjMat[i][N + 1], -1);
   }
   
   for (M; M > 0; M--) {
       cin >> from >> to >> cost;
       
       adjMat[from][to] = (adjMat[from][to] != -1 ? min(adjMat[from][to], cost) : cost);
   }
   
   cin >> depart >> arrive;
   
   dijkstra(depart);
   
   cout << dist[arrive] << '\n';
   
   cur = arrive;
   path.push(arrive);
   while (cur != depart) {
       path.push(before[cur]);
       cur = before[cur];
   }
   cout << path.size() << '\n';
   
   while (!path.empty()) {
       cout << path.top() << " ";
       path.pop();
   }
   
   return 0;
}
