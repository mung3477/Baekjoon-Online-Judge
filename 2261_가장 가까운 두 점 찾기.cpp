#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <cmath>
using std::cin;
using std::cout;
using std::vector;
using std::set;
using std::sort;
using std::sqrt;

struct Point {
    int x;
    int y;

    Point(): x(0), y(0) {};
    Point(int x, int y): x(x), y(y) {};
    
    //y좌표 오름차순 정렬. set에서 사용
    bool operator <(const Point& B) const {
        return (y < B.y || (y == B.y && x < B.x));
    }
};

//x좌표 오름차순 정렬. sort에서 사용
struct Comp {
    bool operator() (Point A, Point B) {
        return (A.x < B.x || (A.x == B.x && A.y < B.y));
    }
} comp;

//거리의 제곱을 return
int distance(const Point& A, const Point& B) {
    return (A.x - B.x) * (A.x - B.x) + (A.y - B.y) * (A.y - B.y);
}

int main(void) {
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int N;
    cin >> N;

    set<Point> candidates;
    vector<Point> points(N);
    for (int i = 0; i < N; i++) {
        cin >> points[i].x >> points[i].y;
    }

    //x좌표 오름차순 정렬
    sort(points.begin(), points.end(), comp);

    /*
        초기 설정
            ans: 여태까지 찾은 가장 작은 두 점 간의 거리
            start: 현재 candidate set에 들어간 가장 index가 작은 point의 index
    */
    int ans = distance(points[0], points[1]), start = 0;
    candidates.insert(points[0]);
    candidates.insert(points[1]);

    for (int i = 2; i < N; i++) {
        Point& cur = points[i];
        //candidate에서 cur과의 x좌표간 거리가 ans보다 큰 점을 nonpromising으로 판단하여 제거
        while (start < i) {
            Point& st = points[start];
            if (ans < cur.x - st.x) {
                candidates.erase(st);
                start += 1;
            }
            else break;
        }

        //candidate에서 cur과의 y좌표 거리가 sqrt(ans) 이내인 점들로 탐색 공간 축소
        int dist = (int)sqrt(ans);
        Point lowest(-10001, cur.y - dist), uppest(10001, cur.y + dist);
        auto upperBound = candidates.lower_bound(uppest);
        auto lowerBound = candidates.upper_bound(lowest);

        for (auto it = lowerBound; it != upperBound; it++) {
            int curDist = distance(*it, cur);
            if (curDist < ans) 
                ans = curDist;
        }

        candidates.insert(cur);
    }

    cout << ans;
    return 0;
}
