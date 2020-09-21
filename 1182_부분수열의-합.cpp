#include <iostream>
#include <string.h>

struct prob {
public:
	prob();
	int findAns();
	int* arr;
	int N, S, ans;

private:
	void _dfs(int i, int cur);
};

prob::prob() {
	N = S = ans = 0;
}

int prob::findAns() {
	_dfs(0, 0);

	return ans;
}

//i번 element를 사용할 / 사용 안 할 차례.
void prob::_dfs(int i, int cur) {
	//base case
	if (i == N) return;

	//typical case
	else {
		//사용
		cur += arr[i];
		if (cur == S) { 
			ans++; }
		_dfs(i + 1, cur);

		//사용 안 함
		cur -= arr[i];
		_dfs(i + 1, cur);
	}
}



int main(void) {
	std::ios_base::sync_with_stdio(false);

	prob A = prob();

	std::cin >> A.N >> A.S;
	A.arr = new int[A.N];

	for (int i = 0; i < A.N; i++) {
		std::cin >> A.arr[i];
	}

	std::cout << A.findAns();
	return 0;
}