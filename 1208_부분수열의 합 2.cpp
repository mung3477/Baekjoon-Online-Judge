#include <iostream>
#include <vector>
#include <algorithm>
using std::cin;
using std::cout;
using std::vector;
using std::sort;

vector<int> A, B;

int lowerBound(int left, int right, int target) {
    //base condition
    if (left == right) {
        if (B.at(left) == target) return left;
        else return -1;
    } 
    
    //else
    int mid = (left + right) / 2;
    if (B.at(mid) < target) 
        return lowerBound(mid + 1, right, target);
    else 
        return lowerBound(left, mid, target);
}

int upperBound(int left, int right, int target) {
    //base condition
    if (left == right) {
        if (B.at(left) == target) return left;
        else return -1;
    }
    
    //else
    int mid = (left + right) / 2 + 1;
    if (B.at(mid) <= target) 
        return upperBound(mid, right, target);
    else 
        return upperBound(left, mid - 1, target);
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    vector<int> input, append;          
    
    int N, S, lower_bound, upper_bound;
    long long ans = 0;
    cin >> N >> S;
    
    for (int i = 0; i < N; i++) {
        int temp;
        cin >> temp;
        input.push_back(temp);
    }
    
    //왼쪽 절반의 부분수열들
    for (int i = 0; i <= N / 2; i++) {
        for (auto it = A.begin(); it != A.end(); it++) {
            append.push_back(*it + input.at(i));
        }
        A.push_back(input.at(i));
        while (!append.empty()) {
            A.push_back(append.back());
            append.pop_back();
        }
    }
    
    //오른쪽 절반의 부분수열들
    for (int i = N / 2 + 1; i < N; i++) {
        for (auto it = B.begin(); it != B.end(); it++) {
            append.push_back(*it + input.at(i));
        }
        B.push_back(input.at(i));
        while (!append.empty()) {
            B.push_back(append.back());
            append.pop_back();
        }
    }
    
    sort(B.begin(), B.end());
    
    
    for (int elem : A) {
        if (elem == S) ans++;
        
        if (!B.empty()) {
            lower_bound = lowerBound(0, B.size() - 1, S - elem);
            if (0 <= lower_bound) {
                upper_bound = upperBound(0, B.size() - 1, S - elem);
                ans += upper_bound - lower_bound + 1;
            }
        }
    }
    
    for (int elem : B) if (elem == S) ans++;

    cout << ans;
    
    return 0;
}
