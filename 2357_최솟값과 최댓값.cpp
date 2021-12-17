#include <iostream>
using std::cin;
using std::cout;

int *minSegTree, *maxSegTree, *nums;

int min(const int a, const int b) {
    if (a < b) return a;
    else return b;
}
int max(const int a, const int b) {
    if (a > b) return a;
    else return b;
}
int initialize(const int cur, const int left, const int right, int *segTree, const bool mode);
int query(const int cur, const int left, const int right, const int qLeft, const int qRight, int *segTree, const bool mode);

int main(void) {
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int N, M, left, right;
    cin >> N >> M;   

    minSegTree = new int[4 * N];
    maxSegTree = new int[4 * N];
    nums = new int[N];

    for (int i = 0; i < N; i++) cin >> nums[i];

    initialize(0, 0, N - 1, minSegTree, 0);
    initialize(0, 0, N - 1, maxSegTree, 1);
    
    for (int i = 0; i < M; i++) {
        cin >> left >> right;
        left -= 1; right -= 1;  //0번 index부터 데이터를 저장했기 때문에 이에 맞게 index 조정

        cout << query(0, 0, N - 1, left, right, minSegTree, 0) << " " << query(0, 0, N - 1, left, right, maxSegTree, 1) << "\n";
    }

    return 0;
}

int initialize(const int cur, const int left, const int right, int *segTree, const bool mode) {
    if (left == right) { return segTree[cur] = nums[left]; }

    int mid = (left + right) / 2;

    if (mode)
        return segTree[cur] = max(initialize(cur * 2 + 1, left, mid, segTree, mode), initialize(cur * 2 + 2, mid + 1, right, segTree, mode));
    else 
        return segTree[cur] = min(initialize(cur * 2 + 1, left, mid, segTree, mode), initialize(cur * 2 + 2, mid + 1, right, segTree, mode));
}

int query(const int cur, const int left, const int right, const int qLeft, const int qRight, int *segTree, const bool mode) {
    //target 범위 안에 현재 노드의 범위가 있음
    if (qLeft <= left && right <= qRight) {
        return segTree[cur];
    }

    //target 범위 안에 현재 노드의 범위가 없음
    else if (qRight < left || right < qLeft) {
        return (mode ? 0 : 1000000001);
    }

    //target 범위와 현재 노드의 범위가 일부 겹침
    int mid = (left + right) / 2;
    
    if (mode)
        return max(query(cur * 2 + 1, left, mid, qLeft, qRight, segTree, mode), query(cur * 2 + 2, mid + 1, right, qLeft, qRight, segTree, mode));
    else 
        return min(query(cur * 2 + 1, left, mid, qLeft, qRight, segTree, mode), query(cur * 2 + 2, mid + 1, right, qLeft, qRight, segTree, mode));
}
