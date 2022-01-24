#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <algorithm>
using std::cin;
using std::cout;
using std::vector;
using std::list;
using std::stack;
using std::sort;
using std::fill;

int visitOrder, *DFSNum, *SCCNum, *variables;
stack<int> DFSOrder;
vector<vector<int>> SCCs;
list<int> *CNF;

int min(int a, int b) {
    if (a < b) return a;
    else return b;
}

int index(int A) {
    return (A > 0 ? 2 * A : -2 * A - 1);
}

int negative(int A) {
    return (A % 2 ? A + 1 : A - 1);
}

int makeSCCWithDFS(int cur);

int main(void) {
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    int N, M, x, y, able = 1;
    cin >> N >> M;

    variables = new int[2 * N + 1]{};
    fill(variables, &variables[2 * N + 1], -1);
    DFSNum = new int[2 * N + 1]{};
    SCCNum = new int[2 * N + 1]{};
    CNF = new list<int>[2 * N + 1]{};

    for (int i = 1; i <= M; i++) {
        cin >> x >> y;

        x = index(x);
        y = index(y);

        CNF[negative(x)].push_back(y);
        CNF[negative(y)].push_back(x);
    }

    for (int i = 1; i <= 2 * N; i++) 
        if (!DFSNum[i]) makeSCCWithDFS(i);

    for (int i = 1; i <= N; i++) {
        if (SCCNum[2 * i - 1] == SCCNum[2 * i]) {
            able = 0;
            break;
        }
    }

    cout << able << "\n";

    if (able) {
        // SCC 번호 큰 것부터 역순으로 순회. 이러면 SCC를 위상정렬한 순서대로 도는 것과 동일.
        for (int i = SCCs.size() - 1; 0 <= i; i--) {
            for (const int& cur : SCCs[i]) {
                variables[cur] = (variables[negative(cur)] == - 1 ? 0 : 1);
            }
        }

        for (int i = 1; i <= N; i++) {
            int cur = 2 * i;
            if (variables[cur] == - 1) variables[cur] = !variables[negative(cur)];
            cout << variables[cur] << " ";
        }
    }

    SCCs.clear();
    delete[] variables, DFSNum, SCCNum, CNF;
    return 0;
}

int makeSCCWithDFS(int cur) {
    DFSNum[cur] = ++visitOrder;
    DFSOrder.push(cur);

    int reachableHighest = DFSNum[cur];
    for (const int& next : CNF[cur]) {
        // visit the node which is not visited yet
        if (!DFSNum[next]) reachableHighest = min(reachableHighest, makeSCCWithDFS(next));
        
        // if the node was visited during current DFS, just compare reachable highset
        else if (!SCCNum[next]) {
            reachableHighest = min(reachableHighest, DFSNum[next]);
            continue;
        }
    }

    // if current node is start of an SCC, extract the SCC
    if (DFSNum[cur] == reachableHighest) {
        int curSCCNum = SCCs.size() + 1, curTop;
        vector<int> SCC;

        while (reachableHighest != (DFSNum[curTop = DFSOrder.top()])) {
            SCCNum[curTop] = curSCCNum;
            SCC.push_back(curTop);
            DFSOrder.pop();
        }

        SCCNum[curTop] = curSCCNum;
        SCC.push_back(curTop);
        DFSOrder.pop();

        sort(SCC.begin(), SCC.end());
        SCCs.emplace_back(SCC);
    }

    return reachableHighest;
}
