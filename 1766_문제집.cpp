#include <iostream>
#include <queue>
#include <vector>
#include <list>
using std::cin;
using std::cout;
using std::priority_queue;
using std::vector;
using std::list;

struct Comp {
    bool operator()(int A, int B) {
        return A > B;
    }
};

int main()
{
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    int N, M, from, to;
    list<int>* adjList;
    int* inDegree;
    vector<int> solveOrder;
    priority_queue<int, vector<int>, Comp> solvable;
    
    cin >> N >> M;
    
    inDegree = new int[N + 1]{};
    adjList = new list<int>[N + 1];
    
    for (M; M > 0; M--) {
        cin >> from >> to;
        adjList[from].push_back(to);
        inDegree[to]++;
    }
    
    for (int i = 1; i <= N; i++) {
        if (!inDegree[i]) {
            solvable.push(i);
        }
    }
    
    for (int i = 1; i <= N; i++) {
        int cur = solvable.top();
        solvable.pop();
        
        solveOrder.push_back(cur);
        
        for (auto it = adjList[cur].begin(); it != adjList[cur].end(); it++) {
            inDegree[*it]--;
            
            if (!inDegree[*it]) {
                solvable.push(*it);
            }
        }
    }
    
    for (int prob : solveOrder)
        cout << prob << " ";
        
    delete[] adjList, inDegree;    
    
    return 0;
}
