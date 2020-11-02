#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N;
long long* histogram;

//find max histogram in [l, r]
long long maxHistogram(int l, int r) {
	
	//base case
	if (r - l == 0) {
		return histogram[l];
	}

	//typical case
	int mid = (l + r) / 2;
	long long result = max(maxHistogram(l, mid), maxHistogram(mid + 1, r));

	int nextL = mid, nextR = mid;
	//next : 이번에 사용하게 되는 막대의 index / curSmallest : 지금까지의 구간 속 가장 작은 막대의 index
	int next, curSmallest = mid;

	while ((l - 1 < nextL) || (nextR < r + 1)) {
		
		if (nextL == l - 1) {
			next = nextR++;
		}
		else if (nextR == r + 1) {
			next = nextL--;
		}
		else {
			next = (histogram[nextL] < histogram[nextR]) ? nextR++ : nextL--;
		}

		curSmallest = histogram[curSmallest] < histogram[next] ? curSmallest : next;

		result = max(result, histogram[curSmallest] * ((nextR - 1) - (nextL + 1) + 1));

	}

	return result;
}

int main(void) {

	std::ios_base::sync_with_stdio(false);

	while (1) {
		
		cin >> N;
		

		if (N == 0) {
			break;
		}

		else {
			histogram = new long long[N + 2];
			histogram[0] = histogram[N + 1] = -1;

			for (int i = 1; i <= N; i++) {
				cin >> histogram[i];
			}

			cout << maxHistogram(1, N) << '\n';

			delete histogram;
		}

	}
	
	return 0;
}