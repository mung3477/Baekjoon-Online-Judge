#include <iostream>
#include <string>
#include <utility>
using namespace std;

typedef pair<int, int> sb;

class Number {
public:
	Number();
	Number(int n);
	sb comp(int n);
	bool check(int n, sb res);
	bool getAble();

private:
	string num;
	bool able;
};

Number::Number() : able(true) {}

Number::Number(int n) {
	num = to_string(n);
	if (num[0] == num[1] || num[0] == num[2] || num[1] == num[2] || num.find("0") != string::npos) {
		able = false;
	}
	else { able = true; }
}

sb Number::comp(int n) {
	string temp = to_string(n);
	int strike = 0, ball = 0;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			//if both have same character
			if (temp[i] == num[j]) {
				//strike
				if (i == j) {
					strike++;
				}
				//ball
				else {
					ball++;
				}
				break;
			}
		}
	}

	return make_pair(strike, ball);
}

bool Number::check(int n, sb res) {
	if (able) {
		sb temp = comp(n);
		if (temp.first != res.first || temp.second != res.second) {
			able = false;
		}
	}
	return able;
}

bool Number::getAble(void) { return able; }

Number board[1000];

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int ans = 889;
	
	for (int i = 111; i <= 999; i++) {
		board[i] = Number(i);

		if (board[i].getAble() == false) {
			ans--;
		}
	}
	
	int N;
	cin >> N;
	for (int i = 0; i < N; i++) {
		int query;
		sb result;
		cin >> query >> result.first >> result.second;

		for (int i = 111; i <= 999; i++) {
			bool prev = board[i].getAble();
			if (!board[i].check(query, result) && (prev != board[i].getAble())) {
				ans--;
			}
		}
	}
	cout << ans;
	return 0;
}
