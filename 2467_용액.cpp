#include <iostream>
#include <vector>
#include <cmath>
#include <limits.h>
#include <utility>
using std::cin;
using std::cout;
using std::vector;
using std::abs;
using std::swap;

int N;
vector<int> fluids;

int lower_bound(int left, int right, int target) {
    if (left == right) return left;
    
    int mid = (left + right) / 2;
    if (fluids.at(mid) == target) return mid;
    else if (fluids.at(mid) < target) return lower_bound(mid + 1, right, target);
    else return lower_bound(left, mid, target);
}

int main()
{
    int minAbs = INT_MAX, ans1, ans2;
    cin >> N;
    for (int i = 1; i <= N; i++) {
        int input;
        cin >> input;
        fluids.push_back(input);
    }
    
    for (int i = 0; i < N - 1; i++) {
        //탐색 공간 내 다음 용액으로 제한
        int cur = fluids.at(i), index = lower_bound(i + 1, N - 1, -cur);
        //작지만 제일 큰 거, 크지만 제일 작은 거 둘을 봄
        for (int j = index - 1; j <= index; j++) {
            //out of index와 자기 자신은 보면 안됨
            if (j < 0 || i == j || N - 1 < j) continue;
            
            if (abs(cur + fluids.at(j)) < minAbs) {
                minAbs = abs(cur + fluids.at(j));
                ans1 = fluids.at(i); 
                ans2 = fluids.at(j);
            }
        }
    }
    
    if (ans1 > ans2) swap(ans1, ans2);
    cout << ans1 << " " << ans2;
    
    return 0;
}
