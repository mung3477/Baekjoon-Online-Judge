#include <iostream>
#include <vector>
#include <limits.h>
#include <stdlib.h>
#include <algorithm>
using std::cin;
using std::cout;
using std::vector;

struct point {
    int row;
    int col;
    point(): row(0), col(0) {};
    point(int row, int col): row(row), col(col) {};
};

int minDist = INT_MAX;
vector<point> houses;
vector<point> chickens; 
vector<point> pickedChickens;

int min(int a, int b) {
    if (a < b) return a;
    else return b;
}

int dist(point& a, point& b) {
    return abs(a.row - b.row) + abs(a.col - b.col);
}

int calculateChickDist() {
    int townChickDist = 0;
    for_each(houses.begin(), houses.end(), [&townChickDist](point& house) {
        int chickDist = INT_MAX;
        for_each(pickedChickens.begin(), pickedChickens.end(), [&chickDist, &house](point& chicken) {
            chickDist = min(chickDist, dist(house, chicken)); 
        });
        townChickDist += chickDist;
    });
    return townChickDist;
}

void pickChickens(int left, int usableLeastIndex) {
    if (left) {
        for (int i = usableLeastIndex; i <= chickens.size() - left; i++) {
            pickedChickens.emplace_back(chickens.at(i).row, chickens.at(i).col);
            pickChickens(left - 1, i);
            pickedChickens.pop_back();
        }
    }
    else {
        minDist = min(minDist, calculateChickDist());
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    int N, M, info;
    cin >> N >> M;
    

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) { 
            cin >> info; 
            if (info == 1) {
                houses.emplace_back(i, j);
            }
            if (info == 2) {
                chickens.emplace_back(i, j);
            }
        }
    }
    
    pickChickens(M, 0);
    cout << minDist;
    
    return 0;
}
