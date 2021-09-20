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

int timeSpent = 100001;
int ways[100001]{};
int earliestTime[100001];
queue<pair> frontier;

void expand(pair& next, pair& cur) {
    if (next.timeSpent <= earliestTime[next.pos]) {
        if (next.timeSpent < earliestTime[next.pos]) { 
            frontier.push(next); 
        }
        //overwrite or write the same
        earliestTime[next.pos] = next.timeSpent;
        ways[next.pos] += ways[cur.pos];
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    int N, K;
    pair cur, next;
    fill(earliestTime, &earliestTime[100001], 100001);
    
    
    cin >> N >> K;
    frontier.push(pair(N, 0));
    ways[N] = 1;
    earliestTime[N] = 0;
    bool flag = false;
    
    while (!frontier.empty()) {
        cur = frontier.front();
        frontier.pop();
        
        if (0 < cur.pos) {
            next = pair(cur.pos - 1, cur.timeSpent + 1);
            expand(next, cur);
            flag = next.pos == K;
        }
        
        if (cur.pos < 100000) {
            next = pair(cur.pos + 1, cur.timeSpent + 1);
            expand(next, cur);
            flag = next.pos == K;
        }
        
        if (cur.pos <= 100000 / 2) {
            next = pair(cur.pos * 2, cur.timeSpent + 1);
            expand(next, cur);
            flag = next.pos == K;
        }
        
        if (flag) break;
    }
    
    cout << earliestTime[K] <<"\n" << ways[K];
    
    return 0;
}
