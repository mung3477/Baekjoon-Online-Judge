#include <stdio.h>
#include <vector>
using namespace std;

vector<pair<int, int> > movement;

void hanoi(int N, int depart, int dest)
{
	int via = 6 - depart - dest;
	if (N == 2) {
		movement.push_back({ depart, via });
		movement.push_back({ depart, dest });
		movement.push_back({ via, dest });
	}
	else if (N == 1) {
		movement.push_back({ depart, dest });
	}
	else {
		hanoi(N - 1, depart, via);
		hanoi(1, depart, dest);
		hanoi(N - 1, via, dest);
	}
}

int main(void)
{
	int N;
	scanf("%d", &N);

	hanoi(N, 1, 3);
	printf("%d\n", movement.size());
	for (int i = 0; i < movement.size(); i++) {
		printf("%d %d\n", movement[i].first, movement[i].second);
	}
}
