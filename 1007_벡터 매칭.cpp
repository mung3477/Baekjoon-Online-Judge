#include <iostream>
#include <limits.h>
#include <math.h>
using std::cin;
using std::cout;

struct point {
    int x;
    int y;
    point(): x(0), y(0) {};
    point(int x, int y): x(x), y(y) {};
    
    void reverseSign() {
        x = -1 * x;
        y = -1 * y;
    }
    
    double length() {
        return sqrt((double)x * x + (double)y * y);
    }
};

int N;
double minSum = INT_MAX;
point* points;

double min(double a, double b) {
    if (a < b) return a;
    else return b;
}

point vectorSum() {
    point result;
    for (int i = 1; i <= N; i++) {
        result.x += points[i].x;
        result.y += points[i].y;
    }
    
    return result;
}

void pickOne(int left, int leastPickable) {
    if (left) {
        for (int i = leastPickable; i <= N - left + 1; i++) {
            points[i].reverseSign();
            pickOne(left - 1, i + 1);
            
            points[i].reverseSign();
        }
    }
    //다 골랐으니 이동 결과값에 피타고라스
    else {
        point result = vectorSum();
        minSum = min(minSum, result.length());
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cout<<std::fixed;
    cout.precision(12);
    
    int T, x, y;
    
    cin >> T;
    
    for (T; T > 0; T--) {
        cin >> N;
        //점 입력
        points = new point[N + 1];
        for (int i = 1; i <= N; i++) {
            cin >> x >> y;
            points[i] = point(x, y);
        }
        
        //NCN/2 각각에 피타고라스
        pickOne(N / 2, 1);
        
        cout << minSum << "\n";
        
        minSum = INT_MAX;
        delete[] points;
    }
    
    
    return 0;
}
