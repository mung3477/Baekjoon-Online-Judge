#include <iostream>
#include <list>
#include <stack>
using std::cin;
using std::cout;
using std::list;
using std::stack;

list<int> *adjList;
stack<int> DFSHistory;
int *visitedAs, *sccNum, sccFound, passedThrough;
bool *finished, able;

int DFSWithSCC(int cur, int& passedThrough);
int min(int a, int b);

int main(void) {
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int N, M, a, b;
    while (cin >> N) {
        cin >> M;

        able = true;
        sccFound = 0, passedThrough = 0;
        adjList = new list<int>[2 * N + 1]{};
        visitedAs = new int[2 * N + 1]{};
        sccNum = new int[2 * N + 1]{};
        finished = new bool[2 * N + 1]{};

        for (int i = 1; i <= M; i++) {
            cin >> a >> b;

            //not a -> 홀수, a -> 짝수 에 따라 index 조정
            a = (a > 0 ? 2 * a : -2 * a - 1);
            b = (b > 0 ? 2 * b : -2 * b - 1);

            //2-SAT 분리 명제를 그래프화.
            adjList[(a % 2 ? a + 1 : a - 1)].emplace_back(b);
            adjList[(b % 2 ? b + 1 : b - 1)].emplace_back(a);
        }

        //상근이가 무조건 뽑혀야 함. 1 or 1(not 1 -> 1) 을 추가
        adjList[1].emplace_back(2);


        for (int i = 1; i <= 2 * N && passedThrough < 2 * N; i++) {
            if (!visitedAs[i]) DFSWithSCC(i, passedThrough);
        }

        for (int i = 1; i <= N; i++) {
            if (sccNum[2 * i] == sccNum[2 * i - 1]) {
                able = false;
                break;
            }
        }
        if (able) cout << "yes\n";
        else cout << "no\n";

        delete[] adjList, visitedAs, finished, sccNum;
    }

    return 0;
}

int DFSWithSCC(int cur, int& passedThrough) {
    //visited 표시
    visitedAs[cur] = ++passedThrough;
    DFSHistory.push(cur);

    int highest = visitedAs[cur];
    for (int next : adjList[cur]) {
        //DFS (순방향 간선)
        if (!visitedAs[next]) {
            highest = min(highest, DFSWithSCC(next, passedThrough));
        }
        //next가 Ancestor in same SCC일 수도 있음 (역방향 / 교차 간선)
        else if (!finished[next]) {
            highest = min(highest, visitedAs[next]);
        }
        //다른 간선은 무시
    }

    //SCC 추출 조건 : 나보다 더 부모인 노드에 닿을 수 없는 경우 & DFS를 끝마쳤을 경우
    if (highest == visitedAs[cur]) {
        sccFound += 1;
        int top = 0;

        do {
            top = DFSHistory.top();
            sccNum[top] = sccFound;
            finished[top] = 1;
            DFSHistory.pop();
        } while (top != cur);
    }

    return highest;
}

int min(int a, int b) {
    if (a < b) return a;
    else return b;
}

