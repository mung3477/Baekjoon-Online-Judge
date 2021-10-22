#include <iostream>
#include <vector>
#include <cmath>
#include <limits.h>
#include <algorithm>
using std::cin;
using std::cout;
using std::vector;
using std::abs;
using std::sort;

vector<int> solutions;

struct mixture {
    int s1;
    int s2;
    int s3;
    
    mixture(): s1(0), s2(0), s3(0) {};
    mixture(int s1, int s2, int s3): s1(s1), s2(s2), s3(s3) {};
    
    long long pH() {
        return (long long)s1 + s2 + s3;
    }
    
    void print() {
        vector<int> temp;
        temp.push_back(s1); temp.push_back(s2); temp.push_back(s3);
        sort(temp.begin(), temp.end());
        for (int elem : temp) cout << elem << " ";
    }
};

int upperBound(int left, int right, long long target) {
    if (left == right) return left;
    
    int mid = (left + right) / 2;
    if (solutions.at(mid) == target) return mid;
    else if (solutions.at(mid) < target) return upperBound(mid + 1, right, target);
    else return upperBound(left, mid, target);
}

int main()
{
    int N;
    long long minAbs = LLONG_MAX;
    mixture answer;
    
    cin >> N;
    for (int i = 0; i < N; i++) {
       int solution;
       cin >> solution;
       solutions.push_back(solution);
    }
    sort(solutions.begin(), solutions.end());
    
    for (int i = 0; i < N - 2; i++) {
        for (int j = i + 1; j < N - 1; j++) {
            long long mixedpH = solutions.at(i) + solutions.at(j);
            /*
                -mixture가 있을 경우 upperBound 위치가 답.
                없을 경우 upperBound 위치와 (upperBound 위치 == -mixture보다 큰, 가장 -mixture에 가까운 값)
                upperBound 위치 하나 아래 (-mixture보다 작은, 가장 -mixture에 가까운 값)을 탐색해보아야함  
            */
            int upper_bound = upperBound(j + 1, N - 1, -mixedpH);
            for (int k = upper_bound - 1; k <= upper_bound; k++) {
                //upper_bound가 j + 1 위치를 가리키는 경우, upper_bound 하나 전 위치가 j와 같아져 같은 용액을 두 번 사용하게 됨.
                if (k == j) continue;
                
                //최적의 답 갱신
                if (abs(mixedpH + solutions.at(k)) < minAbs) {
                    answer = mixture(solutions.at(i), solutions.at(j), solutions.at(k));
                    minAbs = abs(answer.pH());
                }
            }
        }
    }
    
    answer.print();
    
    return 0;
}
