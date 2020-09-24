#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

struct socket {
	int unplugged, N, plugged;
	int* plug;

	socket();
	socket(int N);
	void plugIn(int i, vector<int> schedule);
	bool alreadyThere(int M);
	int _min(int i, vector<int> schedule);
};

socket::socket() {
	unplugged = N = plugged = 0;
	plug = NULL;
}

socket::socket(int N) {
	unplugged = plugged = 0;
	this->N = N;
	plug = new int[N];
}

//�÷��׿� �����ִ� ���ǵ� �� ������ ���� ���� �ð� �Ŀ� �� ������ �÷��׿����� ��ġ�� Ž��
//�̹��� �� ����(schedule.begin() + i - 1)�� �÷��׿� ������ Ȯ�� ������ + i���� Ž��.
int socket::_min(int i, vector<int> schedule) {
	int maxIndex = 0, maxDist = 0, dist;
	for (int j = 0; j < N; j++) {
		auto result = find(schedule.begin() + i, schedule.end(), plug[j]);
		dist = distance(schedule.begin() + i, result);

		if (maxDist < dist) {
			maxDist = dist;
			maxIndex = j;
		}
	}
	return maxIndex;
}

//check if M is already plugged in
bool socket::alreadyThere(int M) {
	for (int i = 0; i < N; i++) {
		if (plug[i] == M) return true;
	}

	return false;
}

void socket::plugIn(int i, vector<int> schedule) {
	if (!alreadyThere(schedule[i])) {
		//if there's available socket
		if (plugged < N) {
			plug[plugged] = schedule[i];
			plugged++;
		}
		//there's no available socket, and we have to plug in M
		else {
			int minLoc = _min(i, schedule);
			plug[minLoc] = schedule[i];
			unplugged++;
		}
	}
}

int main(void) {
	std::ios_base::sync_with_stdio(false);

	int N, K, temp;
	vector<int> schedule;

	std::cin >> N >> K;
	socket s(N);

	for (int i = 0; i < K; i++) {
		std::cin >> temp;
		schedule.push_back(temp);
	}


	for (int i = 0; i < K; i++) {
		s.plugIn(i, schedule);
	}

	std::cout << s.unplugged;
	
	return 0;
}