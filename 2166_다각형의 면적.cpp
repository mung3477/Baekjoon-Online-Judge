#include <iostream>
#include <utility>
#include <vector>
#include <cmath>
using std::cin;
using std::cout;
using std::pair;    //x, y
using std::vector;
using std::abs;

int main()
{
    int N;
    vector<pair<int, int>> points;
    
    cin >> N;
    
    for (int i = 1; i <= N; i++) {
        int x, y;
        cin >> x >> y;
        points.emplace_back(x, y);
    }
    points.push_back(points.front());
    
    long long xy = 0, yx = 0;
    for (int i = 0; i < N; i++) {
        xy += (long long)points[i].first * points[i + 1].second;
        yx += (long long)points[i].second * points[i + 1].first;
    }
    
    cout << std::fixed;
    cout.precision(1);
    cout << abs((xy - yx) / 2.0);
    
    return 0;
}
