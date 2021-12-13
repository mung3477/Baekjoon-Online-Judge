#include <iostream>
using std::cin;
using std::cout;

int segTree[4000000];   //starts from 0. 2^25 - 1 nodes. leaf represents 1 ~ 1000000 tastes

int query(const int& rank, const int& cur, const int& left, const int& right);
void update(const int& taste, const int& diff, const int& cur, const int& left, const int& right);

int main(void) {
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int N, type, rank, taste, diff;
    cin >> N;

    for (int i = 1; i <= N; i++) {
        cin >> type;
        if (type == 1) {
            cin >> rank;
            int popped = query(rank, 0, 1, 1000000);
            cout << popped << "\n";
            update(popped, -1, 0, 1, 1000000);
        }
        else {
            cin >> taste >> diff;
            update(taste, diff, 0, 1, 1000000);
        }
    }
    
    return 0;
}

int query(const int& rank, const int& cur, const int& left, const int& right) {
    //found target
    if (left == right) return left;

    int mid = (left + right) / 2;
    if (rank <= segTree[cur * 2 + 1]) return query(rank, cur * 2 + 1, left, mid);
    else return query(rank - segTree[cur * 2 + 1], cur * 2 + 2, mid + 1, right);
}
void update(const int& taste, const int& diff, const int& cur, const int& left, const int& right) {
    //nonpromising state
    if (taste < left || right < taste) return;

    segTree[cur] += diff;

    //terminate
    if (left == right) return;

    int mid = (left + right) / 2;
    update(taste, diff, cur * 2 + 1, left, mid);
    update(taste, diff, cur * 2 + 2, mid + 1, right);
}
