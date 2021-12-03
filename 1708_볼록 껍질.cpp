#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <stack>
#define MAX 40001
using std::cin;
using std::cout;
using std::pow;
using std::sort;
using std::vector;

struct Point {
    int x;
    int y;
    long long dist;
    
    Point(): x(MAX), y(MAX), dist(-1) {};
    Point(int x, int y, long long dist): x(x), y(y), dist(dist) {};
        
    long long distance(Point A) {
        return ((long long)(A.x - x) * (A.x - x) + (long long)(A.y - y) * (A.y - y));
    }
};

short ccw(const Point& A, const Point& B, const Point& C) {
    long long result = (long long)(B.x - A.x) * (C.y - A.y) - (long long)(B.y - A.y) * (C.x - A.x);
    
    if (result > 0) return 1;
    else if (result == 0) return 0;
    else return -1;
}

Point lowest;

struct CompAngle {
    //각도가 작은 점을, 각도 같으면 거리가 가까운 점을 먼저 사용
    bool operator()(const Point& A, const Point& B) {
        short ccwResult = ccw(lowest, A, B);
        if (ccwResult == 0) {
            return A.dist < B.dist;
        }
        else {
            return ccwResult > 0;
        }
    }  
} compAngle;

int main()
{
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    int N, x, y;
    cin >> N;
    
    vector<Point> points;
    for (int i = 0; i < N; i++) {
        cin >> x >> y;
        points.emplace_back(x, y, -1);
        //좌하단 점 기록
        if (lowest.y > y || (lowest.y == y && lowest.x > x)) {
            lowest = points[i];
        }
    }
    
    //distance 채워주기
    for (int i = 0; i < N; i++) {
        points[i].dist = lowest.distance(points[i]);
    }
    
    sort(points.begin(), points.end(), compAngle);
    
    
    vector<Point> convexHull;

    for (int i = 0; i < N; i++) {
        const Point& cur = points[i];
        
        if (i < 2) {
            convexHull.push_back(cur);
            continue;
        }
        
        //일직선 상 또는 오목한 모양이면 prev 제거
        while (convexHull.size() >= 2 && ccw(convexHull[convexHull.size() - 2], convexHull[convexHull.size() - 1], cur) <= 0) {
            convexHull.pop_back();
        }
        
        convexHull.push_back(cur);
    }
    
    cout << convexHull.size();
    
    return 0;
}
