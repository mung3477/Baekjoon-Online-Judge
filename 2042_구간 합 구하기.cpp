#include <iostream>
#include <vector>
#include <cmath>
using std::cin;
using std::cout;
using std::vector;
using std::log2;
using std::ceil;
using std::pow;

long long initialize(const int cur, const int left, const int right, const vector<long long>& nums);
void makeSegmentTree(const vector<long long>& nums);
long long query(const int qLeft, const int qRight, const int cur, const int left, const int right);
void update(const int target, const long long diff, const int cur, const int left, const int right);

long long *segmentTree;
int totalNodeCount;
int numberCount;

void showSegTree() {
    for (int i = 0; i < totalNodeCount; i++) {
        cout << segmentTree[i] << " ";
    }
    cout << "\n";
}

int main(void) {
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    vector<long long> nums;
    nums.push_back(-1);

    int N, M, K;
    cin >> N >> M >> K;

    for (int i = 1; i <= N; i++) {
        long long given;
        cin >> given;
        nums.push_back(given);
    }
    numberCount = nums.size() - 1;

    makeSegmentTree(nums);

    int type, qLeft, qRight, target;
    long long newVal;
    for (int i = 1; i <= M + K; i++) {
        cin >> type;
        //update
        if (type == 1) {
            cin >> target >> newVal;

            long long diff = newVal - nums[target];
            nums[target] = newVal;

            update(target, diff, 0, 1, numberCount);
        }
        //query
        else {
            cin >> qLeft >> qRight;
            cout << query(qLeft, qRight, 0, 1, numberCount) << "\n";
        }
    }

    delete[] segmentTree;
    return 0;
}

long long initialize(const int cur, const int left, const int right, const vector<long long>& nums) {
    //terminate condition
    if (left == right) {
        return segmentTree[cur] = nums[left];
    }

    int mid = (left + right) / 2;
    segmentTree[cur] = initialize(cur * 2 + 1, left, mid, nums);
    return segmentTree[cur] += initialize(cur * 2 + 2, mid + 1, right, nums);    
}

void makeSegmentTree(const vector<long long>& nums) {
    int depth = ceil(log2(numberCount));
    totalNodeCount = (int)pow(2, depth + 1) - 1;

    segmentTree = new long long[totalNodeCount]{};
    initialize(0, 1, numberCount, nums);
}
long long query(const int qLeft, const int qRight, const int cur, const int left, const int right) {
    //현재 노드가 대표하는 구간이 쿼리 범위 안에 있는 경우
    if (qLeft <= left && right <= qRight) return segmentTree[cur];
    
    //현재 노드가 대표하는 구간과 쿼리 범위가 겹치지 않는 경우
    if (right < qLeft || qRight < left) return 0;

    long long sum = 0;
    int mid = (left + right) / 2;
    
    sum += query(qLeft, qRight, cur * 2 + 1, left, mid);
    sum += query(qLeft, qRight, cur * 2 + 2, mid + 1, right);
    return sum;
}

void update(const int target, const long long diff, const int cur, const int left, const int right) {
    //현재 노드가 대표하는 구간 안에 target이 없는 경우
    if (target < left || right < target) return;

    //구간 값에 변화가 생겼으니 update
    segmentTree[cur] += diff;

    //leaf면 그만하기
    if (left == right) return;

    int mid = (left + right) / 2;
    update(target, diff, cur * 2 + 1, left, mid);
    update(target, diff, cur * 2 + 2, mid + 1, right);
}
