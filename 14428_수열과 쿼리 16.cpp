#include <iostream>
#include <utility>
#define MAX 1000000001
using std::cin;
using std::cout;
using std::pair;

int *input;
pair<int, int> *segTree;    // value, index

pair<int, int> createSegTree(int cur, int left, int right);
pair<int, int> update(int cur, int left, int right, int target, int newValue);
pair<int, int> query(int cur, int left, int right, int targetLeft, int targetRight);

int main(void) {
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int N, M, mode, target, newValue, targetLeft, targetRight;
    cin >> N;

    input = new int[N + 1]{};
    segTree = new pair<int, int>[4 * N]{};
    
    for (int i = 1; i <= N; i++) cin >> input[i];
    createSegTree(1, 1, N);

    cin >> M;
    for (int i = 1; i <= M; i++) {
        cin >> mode;
        if (mode == 1) {
            cin >> target >> newValue;
            update(1, 1, N, target, newValue);
        }
        else {
            cin >> targetLeft >> targetRight;
            cout << query(1, 1, N, targetLeft, targetRight).second << "\n"; 
        }
    }

    delete[] input, segTree;
    return 0;
}

pair<int, int> createSegTree(int cur, int left, int right) {
    if (left == right) return segTree[cur] = { input[left], left };

    int mid = (left + right) / 2;
    pair<int, int> _left = createSegTree(cur * 2, left, mid);
    pair<int, int> _right = createSegTree(cur * 2 + 1, mid + 1, right);

    return segTree[cur] = (_left.first < _right.first || ((_left.first == _right.first) && (_left.second < _right.second))) ? _left : _right;
}

/** 
 * 1. a node includes target
 * 2. a node doesn't include the target
*/
pair<int, int> update(int cur, int left, int right, int target, int newValue) {
    if (target < left || right < target) 
        return segTree[cur];
    else if (left == right) 
        return segTree[cur] = {newValue, target};
    
    int mid = (left + right) / 2;
    pair<int, int> _left = update(cur * 2, left, mid, target, newValue);
    pair<int, int> _right = update(cur * 2 + 1, mid + 1, right, target, newValue);

    return segTree[cur] = (_left.first < _right.first || ((_left.first == _right.first) && (_left.second < _right.second))) ? _left : _right;
}

/** 
 * 1. target boundary includes the node
 * 2. target boundary doesn't intersect with node
 * 3. partially intersects
*/
pair<int, int> query(int cur, int left, int right, int targetLeft, int targetRight) {
    if (targetLeft <= left && right <= targetRight) return segTree[cur];
    else if (targetRight < left || right < targetLeft) return {MAX, 0};

    if (left == right) return segTree[cur];

    int mid = (left + right) / 2;
    pair<int, int> _left = query(cur * 2, left, mid, targetLeft, targetRight);
    pair<int, int> _right = query(cur * 2 + 1, mid + 1, right, targetLeft, targetRight);

    return (_left.first < _right.first || ((_left.first == _right.first) && (_left.second < _right.second))) ? _left : _right;
}
