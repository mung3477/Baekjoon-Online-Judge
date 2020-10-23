#include <iostream>
#include <queue>
#include <utility>
#include <string.h>
using namespace std;

using assignment = pair<int, int>;

struct assignmentCompare {
	bool operator() (assignment a, assignment b) {

		if (a.second == b.second) {

			return (a.first > b.first);

		}

		else { return (a.second < b.second); }

	}
};

int main(void) {
	std::ios_base::sync_with_stdio(false);
	int N, maxDay = 0, count = 0, ans = 0;
	assignment temp;
	priority_queue<assignment, vector<assignment>, assignmentCompare> pq;

	cin >> N;
	for (int i = 0; i < N; i++) {

		cin >> temp.first >> temp.second;
		
		if (maxDay < temp.first) { maxDay = temp.first; }
		pq.push(temp);

	}

	bool* timeline = new bool[maxDay];
	memset(timeline, false, sizeof(bool) * maxDay);

	while(count < maxDay && !pq.empty()) {

		temp = pq.top();

		for (int i = temp.first - 1; i >= 0; i--) {

			if (!timeline[i]) {
				timeline[i] = true;
				ans += temp.second;
				count++;
				break;
			}

		}

		pq.pop();
	}

	cout << ans;
	return 0;
}