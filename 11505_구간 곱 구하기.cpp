#include <iostream>
#define MOD 1000000007
using std::cin;
using std::cout;

int *segTree;

long long update(int cur, int left, int right, int targetIndex, int newValue);
long long query(int cur, int left, int right, int targetLeft, int targetRight);

int main(void) {
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int N, M, K, mode, targetLeft, targetRight, targetIndex, newValue;
    cin >> N >> M >> K;
    

    segTree = new int[4 * (N + 1)]{};
    for (int i = 0; i < 4 * (N + 1); i++) segTree[i] = 1;

    for (int i = 1; i <= N; i++) {
        cin >> newValue;
        update(1, 1, N, i, newValue);
    }

    for (int i = 1; i <= M + K; i++) {
        cin >> mode;
        if (mode == 1) {
            cin >> targetIndex >> newValue;
            update(1, 1, N, targetIndex, newValue);
        }
        else {
            cin >> targetLeft >> targetRight;
            cout << query(1, 1, N, targetLeft, targetRight) << "\n";
        }
    }

    delete[] segTree;
    return 0;
}

/** 
 * Case 1. out of bound
 * Case 2. in the bound
*/
long long update(int cur, int left, int right, int targetIndex, int newValue) {
    if (targetIndex < left || right < targetIndex) return segTree[cur];
    else if (left == right) {
        return segTree[cur] = newValue;
    }
    else {
        int mid = (left + right) / 2;
        return segTree[cur] = (update(cur * 2, left, mid, targetIndex, newValue) * update(cur * 2 + 1, mid + 1, right, targetIndex, newValue)) % MOD;
    }
}

/** 
 * Case 1. out of bound
 * Case 2. totally in the bound
 * Case 3. partially intersect
*/
long long query(int cur, int left, int right, int targetLeft, int targetRight) {
    if (targetRight < left || right < targetLeft) return 1;
    else if (targetLeft <= left && right <= targetRight) return segTree[cur];
    
    int mid = (left + right) / 2;
    return query(cur * 2, left, mid, targetLeft, targetRight) * query(cur * 2 + 1, mid + 1, right, targetLeft, targetRight) % MOD;
}
