#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
using namespace std;
using section = pair<int, int>;

struct sectionComp {
	bool operator()(section s1, section s2) {
		int dist1 = s1.second - s1.first;
		int dist2 = s2.second - s2.first;

		if (dist1 < dist2) { return false; }
		else if (dist1 == dist2) {
			return (s1.first > s2.first);
		}
	}
};

int main(void) {
	std::ios_base::sync_with_stdio(false);

	int N, K, ans = 0, count = 0, temp;
	vector<int> sensorLoc;
	vector<section> sectionVec, used;

	cin >> N >> K;

	while (count < N) {
		cin >> temp;
		sensorLoc.push_back(temp);
		count++;
	}

	if (K < N) {
		sort(sensorLoc.begin(), sensorLoc.end());

		for (int i = 0; i < sensorLoc.size() - 1; i++) {
			//구간 길이 0인 경우는 넣지 않음
			if (sensorLoc[i] != sensorLoc[i + 1]) {
				sectionVec.push_back(make_pair(sensorLoc[i], sensorLoc[i + 1]));
			}
		}
		count = sectionVec.size() + 1;

		sort(sectionVec.begin(), sectionVec.end(), sectionComp());

		//count == 집중국 개수
		while (count > K) {
			section tmp = *sectionVec.rbegin();
			ans += tmp.second - tmp.first;
			sectionVec.pop_back();
			count--;
		}
	}

	cout << ans;

	return 0;
}