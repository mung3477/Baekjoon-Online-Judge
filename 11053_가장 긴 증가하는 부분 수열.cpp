#include <iostream>
using std::cin;
using std::cout;

int closest(int* lis, int left, int right, int target) {
    if (left == right) return left;
    
    int mid = (left + right) / 2 + 1;
    if (lis[mid] < target) {
        return closest(lis, mid, right, target);
    }
    else {
        return closest(lis, left, mid - 1, target);
    }
}

int main()
{
    int N, position, i, curLisLength = 1;
    int* A;
    int* lis;

    
    cin >> N;
    A = new int[N + 1]{};
    lis = new int[N + 1]{};
    for (int i = 1; i <= N; i++) {
        cin >> A[i];
    }
    
    lis[1] = A[1];
    for (i = 2; i <= N; i++) {
        position = closest(lis, 0, curLisLength, A[i]) + 1;
        lis[position] = A[i];
        if (position > curLisLength) { curLisLength = position; }
    }
    
    cout << curLisLength;
    
    return 0;
}
