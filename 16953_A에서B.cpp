#include <iostream>
#include <queue>
#include <set>
using std::cin;
using std::cout;
using std::queue;
using std::set;

struct container {
    int num;
    int calculated;
    container(): num(0), calculated(0) {};
    container(int num, int calculated): num(num), calculated(calculated) {};
};

int main()
{
    int A, B;
    long long next[2];
    set<int> visited;
    bool found = false;
    queue<container> frontier;
    
    cin >> A >> B;
    
    if (A == B) {
        cout << 1;
        return 0;
    }
    
    frontier.emplace(A, 1);
    visited.insert(A);
    
    while (!frontier.empty()) {
        container cur = frontier.front();
        frontier.pop();
        
        
        next[0] = (long long)cur.num * 2;
        next[1] = (long long)cur.num * 10 + 1;
        
        for (int i = 0; i < 2; i++) {
            if (next[i] == B) {
                cout << cur.calculated + 1;
                found = true;
                break;
            }
            else if (next[i] < B && visited.find(next[i]) == visited.end()) {
                frontier.emplace(next[i], cur.calculated + 1);
                visited.insert(next[i]);
            }
        }
    }
    
    if (!found) cout << -1;
    
    return 0;
}
