#include <iostream>
#include <utility>
#include <limits.h>
#include <stack>
using std::cin;
using std::cout;
using std::pair;
using std::make_pair;
using std::move;
using std::stack;

/** 두 지점 간의 거리 */
int dist(const pair<int, int>& A, const pair<int, int>& B) {
    return abs(A.first - B.first) + abs(A.second - B.second);
}

int min(const int A, const int B) {
    if (A < B) return A;
    else return B;
}

int main(void) {
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int N, W;
    cin >> N >> W;

    /** 2 ~ W + 1는 pos와 동일.  [0]은 (1, 1), [1]은 (N, N)*/
    int DP[W + 2][W + 2]{};
    for (int i = 0; i <= W + 1; i++) {
        for (int j = 0; j <= W + 1; j++) {
            DP[i][j] = INT_MAX;
        }
    }

    DP[0][1] = 0;   //start point

    pair<int, int> fromWhere[W + 2][W + 2]{};
    fromWhere[0][1].first = fromWhere[0][1].second = -1;    //end of backtracing

    pair<int, int> pos[W + 2]{pair<int, int>(1, 1), pair<int, int>(N, N), };
    for (int i = 2; i <= W + 1; i++) {
        cin >> pos[i].first >> pos[i].second;
    }

    //to position i
    int dist1, dist2;
    for (int i = 2; i <= W + 1; i++) {
        for (int j = 0; j < i - 1; j++) {
            if (DP[i - 1][j] != INT_MAX) {
                //using car 1
                dist1 = dist(pos[i], pos[i - 1]) + DP[i - 1][j];
                if (dist1 < DP[i][j]) {
                    DP[i][j] = dist1;
                    fromWhere[i][j] = move(make_pair(1, i - 1));
                }

                //using car 2
                dist2 = dist(pos[i], pos[j])  + DP[i - 1][j];
                if (dist2 < DP[i - 1][i]) {
                    DP[i - 1][i] = dist2;
                    fromWhere[i - 1][i] = move(make_pair(2, j));
                }
            }

            if (DP[j][i - 1] != INT_MAX) {
                //using car 1
                dist1 = dist(pos[i], pos[j]) + DP[j][i - 1];
                if (dist1 < DP[i][i - 1]) {
                    DP[i][i - 1] = dist1;
                    fromWhere[i][i - 1] = move(make_pair(1, j));
                }

                //using car 2
                dist2 = dist(pos[i], pos[i - 1]) + DP[j][i - 1];
                if (dist2 < DP[j][i]) {
                    DP[j][i] = dist2;
                    fromWhere[j][i] = move(make_pair(2, i - 1));
                }
            }
        }
    }

    int minimumDist = INT_MAX, curRow, curCol;
    for (int i = 0; i < W + 1; i++) {
        if (DP[i][W + 1] < minimumDist) {
            minimumDist = DP[i][W + 1];
            curRow = i;
            curCol = W + 1;
        }

        if (DP[W + 1][i] < minimumDist) {
            minimumDist = DP[W + 1][i];
            curRow = W + 1;
            curCol = i;
        }
    }

    cout << minimumDist << "\n";

    pair<int, int>& cur = fromWhere[curRow][curCol];
    stack<int> used;
    while (fromWhere[curRow][curCol].first != -1) {
        cur = fromWhere[curRow][curCol];

        used.push(cur.first);

        if (cur.first == 1) {
            curRow = cur.second;
        }
        else {
            curCol = cur.second;
        }
    }

    while (!used.empty()) {
        cout << used.top() << "\n";
        used.pop();
    }

    return 0;
}
