#include <iostream>
#include <list>
#include <utility>
#include <queue>
using std::cin;
using std::cout;
using std::list;
using std::pair;
using std::priority_queue;

int max = 0;

//@return - cur에서 갈 수 있는 가장 긴 branch 길이 
int DFS(int cur, list<pair<int, int>>* adjList, bool* visited) {
    priority_queue<int> branches;

    //cur에서 진입로 이외의 각 branch 최대 길이 조사
    for (auto it = adjList[cur].begin(); it != adjList[cur].end(); it++) {
        if (!visited[it->first]) {
            visited[it->first] = true;
            branches.push(DFS(it->first, adjList, visited) + it->second);
        }
    }
    
    if (branches.empty()) {
        return 0;
    }
    else {
        int retVal = branches.top();
        branches.pop();
        
        //cur까지의 진입로를 쓰지 않고, 독자적인 경로를 사용하는 경우
        if (!branches.empty()) {
            int independent = retVal + branches.top();
            if (max < independent) max = independent;
            cout << independent << ": independent \n";
        }
        
        return retVal;
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    int V, a, b, cost;
    cin >> V;
    
    list<pair<int, int>>* adjList = new list<pair<int, int>>[V + 1];
    bool* visited = new bool[V + 1]{true, true, };
    
    //adjacent list 채우기
    for (int i = 0; i < V; i++) {
       cin >> a;
       while (1) {
           cin >> b;
           if (b == -1) {
               break;
           }
           else {
               cin >> cost;
               pair<int, int> edge = std::make_pair(b, cost);
               adjList[a].push_back(edge);
           }
       }
    }
  
    //정점 1에서 뻗는 branch 중 가장 긴 branch
    int longestFrom1 = DFS(1, adjList, visited);
    if (max < longestFrom1) max = longestFrom1;
    
    cout << max;
   
    for (int i = 0; i <= V; i++) {
        adjList[i].clear();
    }
    delete[] adjList, visited;
    
    
    return 0;
}
