/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>
#include <algorithm>
#include <vector>
using std::cin;
using std::cout;
using std::sort;
using std::vector;

struct point {
    int x;
    int y;
    int relX;
    int relY;
    int index;
    
    point(int x, int y, int index): x(x), y(y), relX(-1), relY(-1), index(index) {};
    
    bool operator < (const point& B) const {
        return y < B.y || (y == B.y && x < B.x);
    }
};

vector<point> points;

long long distance(point& A, point& B) {
    return (A.x - B.x) * (A.x - B.x) + (A.y - B.y) * (A.y - B.y);
}

long long ccw(point& A, point& B, point& C) {
    return (long long)(B.x - A.x) * (C.y - B.y) - (long long)(B.y - A.y) * (C.x - B.x);
}

//각도순 정렬
bool compare(point& A, point& B) {
    int cw = ccw(points[0], A, B);
    
    if (cw) return cw > 0;
    else return distance(points[0], A) < distance(points[0], B);
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int c, x, y, N;
    cin >> c;
    for (int n = 1; n <= c; n++) {
        
        cin >> N;
        for (int i = 0; i < N; i++) {
            cin >> x >> y;
            points.emplace_back(x, y, i);
        }
    
        //점 좌표 순으로 좌하단 -> 우상단 정렬
        sort(points.begin(), points.end());
        
        for (point& cur : points) {
            cur.relX = cur.x - points[0].x;
            cur.relY = cur.y - points[0].y;
        }
        
        //각도 순 정렬
        sort(points.begin() + 1, points.end(), compare);
        
        
        //맨 마지막 점들이 같은 직선 상에 있다면, 그 직선만 역순으로 방문
        int reverseEnd = N;
        do {
            reverseEnd--;
        } while (ccw(points[0], points[reverseEnd - 1], points[reverseEnd]) == 0);
        
        
        for (int i = 0; i < reverseEnd; i++) {
            cout << points[i].index << " ";
        }
        for (int i = N - 1; i >= reverseEnd; i--) {
            cout << points[i].index << " ";
        }
        cout << "\n";
        
        points.clear();
    }

    return 0;
}
