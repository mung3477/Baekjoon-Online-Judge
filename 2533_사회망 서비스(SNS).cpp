#include <iostream>
#include <list>
using std::cin;
using std::cout;
using std::list;

int N;
list<int> *tree;
bool *visited;      //root -> leaf 방향을 알 수 없어서 양방향 그래프로 tree를 저장하고 visited로 순환 역류 방지
int **leastEarlyAdapters;   //탐색의 DP테이블. [N + 1][2]

int min(const int a, const int b) {
    if (a < b) return a;
    else return b;
}

int howManyEarlyAdapters(const int cur, const bool isParentEarlyAdapter);

int main(void) {
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N;
    tree = new list<int>[N + 1]{};  //1 ~ N 번호 그대로 index에 사용
    visited = new bool[N + 1]{};    //1 ~ N 번호 그대로 index에 사용
    leastEarlyAdapters = new int*[N + 1];   //1 ~ N 번호 그대로 index에 사용
    for (int i = 0; i <= N; i++) {
        leastEarlyAdapters[i] = new int[2]{-1, -1};  //isParentEarlyAdapter가 false: 0, true: 1
    }

    int a, b, ans = 1000000;
    for (int i = 1; i < N; i++) {
        cin >> a >> b;
        tree[a].push_back(b);
        tree[b].push_back(a);
    }

    ans = min(ans, howManyEarlyAdapters(1, true));

    cout << ans;

    return 0;
}

/*
    @param cur - 현재 노드 번호
    @param isParentEarlyAdapter - cur의 부모 노드가 얼리어답터인지 여부
    @return 현재 노드가 root인 서브트리에서 나올 수 있는 최소 얼리어답터 수
*/
int howManyEarlyAdapters(const int cur, const bool isParentEarlyAdapter) {
    if (leastEarlyAdapters[cur][isParentEarlyAdapter] != -1) {
        return leastEarlyAdapters[cur][isParentEarlyAdapter];
    }

    visited[cur] = true;
    int retVal = 1000001;

    //부모 노드가 얼리어답터라면 cur가 얼리어답터가 아니어도 괜찮음
    if (isParentEarlyAdapter) {
        int ifCurIsEarlyAdapter = 0;
        for (auto it = tree[cur].begin(); it != tree[cur].end(); it++) {
            if (visited[*it]) continue;

            ifCurIsEarlyAdapter += howManyEarlyAdapters(*it, false);          
            //같은 공간을 다시 탐색해야할 수 있으니 visited의 변화를 무효화
            visited[*it] = false;
        }

        retVal = min(retVal, ifCurIsEarlyAdapter);
    }

    //cur가 얼리어답터라고 가정
    int ifCurIsNotEarlyAdapter = 0;
    for (auto it = tree[cur].begin(); it != tree[cur].end(); it++) {
        if (visited[*it]) continue;

        ifCurIsNotEarlyAdapter += howManyEarlyAdapters(*it, true);
        
        //같은 공간을 다시 탐색해야할 수 있으니 visited의 변화를 무효화
        visited[*it] = false;
    }
    
    retVal = min(retVal, ifCurIsNotEarlyAdapter + 1);
    return leastEarlyAdapters[cur][isParentEarlyAdapter] = retVal;
}
