#include <iostream>
#include <algorithm>
using namespace std;

int N;
int A[100002];

long long max_3(long long a, long long b, long long c) {
	return max(a, (max(b, c)));
}

//[s, e]의 범위 속 부분 배열 최대 점수
long long subArray(int s, int e) {
	//base case
	if (e - s == 0) {
		return (long long)A[s] * A[s];
	}

	//typical case
	long long mid = (s + e) / 2, smallest = mid;
	long long curScore, maxScore, curSum, tempScore1, tempScore2;

	tempScore1 = subArray(s, mid);
	tempScore2 = subArray(mid + 1, e);

	//l, r은 여태까지 본 배열 범위. next는 이번 탐색에서 확장되는 부분.
	int l, r, next;
	l = r = mid;
	maxScore = curSum = curScore = A[mid];

	while ((s <= l) && (r <= e) && (s != l || r != e)) {

		if (l == s) {
			next = r + 1;
			r++;
		}

		else if (r == e) {
			next = l - 1;
			l--;
		}

		
		else if (A[l - 1] <= A[r + 1]) {

			next = r + 1;
			r++;

		}

		else {

			next = l - 1;
			l--;

		}

		curSum += A[next];
		smallest = (A[smallest] <= A[next]) ? smallest : next;

		curScore = curSum * A[smallest];
		maxScore = max(maxScore, curScore);
	}

	return max_3(maxScore, tempScore1, tempScore2);
}

int main(void) {

	std::ios_base::sync_with_stdio(false);
	A[0] = A[100001] = -1;

	cin >> N;
	for (int i = 1; i <= N; i++) {
		cin >> A[i];
	}

	cout << subArray(1, N);
	
	return 0;
}