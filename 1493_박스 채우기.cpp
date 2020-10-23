#include <iostream>

using namespace std;

int a[20];
int N, ans, l, w, h;
bool solvable = true;

void fill(int l, int w, int h) {

	if ((l > 0) && (w > 0) && (h > 0)) { 

		int i;
		for (i = 19; i >= 0; i--) {

			int cur = 1 << i;

			if ((a[i] > 0) && (l >= cur) && (w >= cur) && (h >= cur)) {

				a[i] -= 1;
				ans += 1;
				fill(l, w, h - cur);
				fill(l - cur, cur, cur);
				fill(l, w - cur, cur);
				break;

			}
		}

		if (i == -1) { 
			solvable = false; 
		}
	}

}

int main(void) {

	std::ios_base::sync_with_stdio(false);
	
	cin >> l >> w >> h >> N;

	for (int i = 0, x, y; i < N; i++) {

		cin >> x >> y;
		a[x] = y;

	}

	fill(l, w, h);
	cout << (solvable ? ans : -1);

	return 0;
}