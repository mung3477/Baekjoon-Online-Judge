#include <iostream>
#include <list>
#include <queue>
using std::cin;
using std::cout;
using std::list;
using std::queue;

int main()
{
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    int N, from, to, cur, next;
    list<int>* adjList;
    int* parent;
    bool* visited;
    queue<int> frontier;
    
    cin >> N;
    adjList = new list<int>[N + 1];
    parent = new int[N + 1]{0, 1, };
    visited = new bool[N + 1]{};
    
    for (int i = 2; i <= N; i++) {
        cin >> from >> to;
        adjList[from].push_back(to);
        adjList[to].push_back(from);
    }
    
    // BFS
    frontier.push(1);
    visited[1] = true;
    
    while(!frontier.empty()) {
        cur = frontier.front();
        frontier.pop();
        for (auto it = adjList[cur].begin(); it != adjList[cur].end(); it++) {
            next = *it;
            if (!visited[next]) {
                parent[next] = cur;
                frontier.push(next);
                visited[next] = true;
            }
        }
    }
    
    for (int i = 2; i <= N; i++) {
        cout << parent[i] << '\n';
    }
    
    return 0;
}
