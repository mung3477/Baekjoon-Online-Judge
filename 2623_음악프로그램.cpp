#include <iostream>
#include <queue>
#include <list>
using std::cin;
using std::cout;
using std::queue;
using std::list;

int main()
{
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    int N, M;
    int* inDegree;
    queue<int> available;
    queue<int> answer;
    list<int>* next;
    
    cin >> N >> M;
    
    inDegree = new int[N + 1]{};
    next = new list<int>[N + 1]{};
    
    for (M; 0 < M; M--) {
        int k, from, to;
        cin >> k >> from;
        
        for (--k; 0 < k; k--) {
            cin >> to;
            next[from].push_back(to);
            inDegree[to]++;
            from = to;
        }
    }
    
    for (int i = 1; i <= N; i++) 
        if (inDegree[i] == 0) available.push(i);
        
    while (!available.empty()) {
        int cur = available.front();
        available.pop();
        
        answer.push(cur);
        
        for (auto it = next[cur].begin(); it != next[cur].end(); it++) {
            int nextSinger = *it;
            inDegree[nextSinger]--;
            
            if (inDegree[nextSinger] == 0) available.push(nextSinger);
        }
    }
    
    if (answer.size() != N) 
        cout << 0;
    else {
        while (!answer.empty()) {
            cout << answer.front() << "\n";
            answer.pop();
        }
    }

    return 0;
}
