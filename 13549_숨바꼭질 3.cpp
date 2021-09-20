#include <iostream>
#include <queue>
#include <algorithm>
using std::cin;
using std::cout;
using std::queue;
using std::fill;

struct pair {
    int pos;
    int timeSpent;
    pair(): pos(-1), timeSpent(0) {};
    pair(int pos, int timeSpent): pos(pos), timeSpent(timeSpent) {};
};

int earliestTime[100001];
queue<pair> frontier;

void expand(pair& next) {
    if (next.timeSpent < earliestTime[next.pos]) {
        frontier.push(next); 
        earliestTime[next.pos] = next.timeSpent;
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    int N, K, nextPos;
    pair cur, next;
    fill(earliestTime, &earliestTime[100001], 100001);
    
    
    cin >> N >> K;
    frontier.push(pair(N, 0));
    earliestTime[N] = 0;
    bool flag = false;
    
    while (!frontier.empty()) {
        cur = frontier.front();
        frontier.pop();
        
        nextPos = cur.pos * 2;
        while (nextPos <= 100000 && earliestTime[nextPos] == 100001) {
            next = pair(nextPos, cur.timeSpent);
            expand(next);
            flag = next.pos == K;
            nextPos *= 2;
        }
        
        if (0 < cur.pos) {
            next = pair(cur.pos - 1, cur.timeSpent + 1);
            expand(next);
            flag = next.pos == K;
        }
        
        if (cur.pos < 100000) {
            next = pair(cur.pos + 1, cur.timeSpent + 1);
            expand(next);
            flag = next.pos == K;
        }
        
        if (flag) break;
    }
    
    cout << earliestTime[K];
    
    return 0;
}
