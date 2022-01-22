#include <iostream>
using std::cin;
using std::cout;

int N, *segTree, *BIndex, *A;
int query(int cur, int left, int right, int targetLeft, int targetRight);
void update(int cur, int left, int right, int target);

int main(void) {
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    int B;
    long long intersected = 0;

    cin >> N;
    segTree = new int[4 * N]{};
    BIndex = new int[1000001]{};
    A = new int[N + 1]{};

    // save A row
    for (int i = 1; i <= N; i++) cin >> A[i];

    // record ID's location in B row
    for (int i = 1; i <= N; i++) {
        cin >> B;
        BIndex[B] = i;
    }

    /** 
     * 1. find A[i]'s location in B row
     * 2. query how many pairs have made using machines between the index found in 1 and the end of B row
     * 3. mark the index found in 1 as "pair made using it"
    */
    for (int i = 1; i <= N; i++) {
        int targetLeft = BIndex[A[i]] + 1;
        if (targetLeft <= N) intersected += query(1, 1, N, targetLeft, N);
        update(1, 1, N, BIndex[A[i]]);
    }

    cout << intersected;

    return 0;
}

int query(int cur, int left, int right, int targetLeft, int targetRight) {
    // terminate: out of bound
    if (targetRight < left || right < targetLeft) return 0;

    // terminate: target area covers all the bound assigned to current node OR leaf node
    else if ((targetLeft <= left && right <= targetRight) || left == right) return segTree[cur];

    int mid = (left + right) / 2;
    return query(cur * 2, left, mid, targetLeft, targetRight) + query(cur * 2 + 1, mid + 1, right, targetLeft, targetRight);
}

void update(int cur, int left, int right, int target) {
    // terminate: out of bound
    if (target < left || right < target) return;

    segTree[cur] += 1;

    // terminate: leaf node
    if (left == right) return;

    int mid = (left + right) / 2;
    update(cur * 2, left, mid, target);
    update(cur * 2 + 1, mid + 1, right, target);
}
