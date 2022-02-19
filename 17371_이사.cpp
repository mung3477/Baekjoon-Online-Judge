#include <iostream>
#include <vector>
#include <utility>
using std::cin;
using std::cout;
using std::vector;
using std::pair;

int max(int a, int b) { return (a > b) ? a : b; }
int dist(const pair<int, int>& A, const pair<int, int>& B) {
    return (A.first - B.first) * (A.first - B.first) + (A.second - B.second) * (A.second - B.second);
}

int main(void) {
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    vector<pair<int, int>> points;
    int N, ans, minFarthest = 1000000000;

    cin >> N;

    for (int i = 1; i <= N; i++) {
        int x, y;
        cin >> x >> y;
        points.emplace_back(x, y);
    }

    for (int i = 0; i < N; i++) {
        int curFarthestDist = 0;

        for (int j = 0; j < N; j++) {
            int curDist = dist(points[i], points[j]);
            curFarthestDist = max(curFarthestDist, curDist);
        }

        if (minFarthest > curFarthestDist) {
            minFarthest = curFarthestDist;
            ans = i;
        }
    }

    cout << points[ans].first << " " << points[ans].second;

    return 0;
}

