#include <iostream>
#include <queue>
#include <list>
using std::cin;
using std::cout;
using std::queue;
using std::list;

int main()
{
    int N, M;
    int* inDegree;
    list<int>* tallerThan;
    queue<int> inDegreeZeros;
    queue<int> sorted;
    
    cin >> N >> M;
    inDegree = new int[N + 1]{};
    tallerThan = new list<int>[N + 1];
    
    for (M; M > 0; M--) {
        int small, tall;
        cin >> small >> tall;
        tallerThan[small].push_back(tall);
        inDegree[tall]++;
    }
    
    for (int i = 1; i <= N; i++) {
        if (inDegree[i] == 0) 
            inDegreeZeros.push(i);
    }
    
    while (!inDegreeZeros.empty()) {
        int cur = inDegreeZeros.front();
        sorted.push(cur);
        inDegreeZeros.pop();
        
        for (auto it = tallerThan[cur].begin(); it != tallerThan[cur].end(); it++) {
            int next = *it;
            
            inDegree[next]--;
            if (inDegree[next] == 0) 
                inDegreeZeros.push(next);
        }
    }
    
    while (!sorted.empty()) {
        cout << sorted.front() << " ";
        sorted.pop();
    }
    
    return 0;
}
