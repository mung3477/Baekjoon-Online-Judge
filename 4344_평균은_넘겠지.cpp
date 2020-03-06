#include <stdio.h>

int score[1001];

int main(void)
{
	int C;
	scanf("%d", &C);

	while (C != 0) {
		int N, count = 0, sum = 0;
		double average = 0;
		scanf("%d", &N);

		for (int i = 1; i <= N; i++) {
			scanf("%d", &score[i]);
			sum += score[i];
		}

		average = (double)sum / N;

		for (int i = 1; i <= N; i++) {
			if (score[i] > average) count++;
		}

		printf("%5.3f", ((double)count / N) * 100);
		printf("%%\n");

		C--;
	}
}