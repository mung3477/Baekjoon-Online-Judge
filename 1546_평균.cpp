#include <stdio.h>

double score[1001];

int main(void)
{
	int n;
	scanf("%d", &n);

	for (int i = 1; i <= n; i++) {
		scanf("%lf", &score[i]);
	}

	double t = 0;
	for (int i = 1; i <= n - 1; i++) {
		if (score[i] > score[i + 1]) {
			t = score[i];
			score[i] = score[i + 1];
			score[i + 1] = t;
		}
	}

	double M = score[n];
	double sum = 0;
	for (int i = 1; i <= n; i++) {
		score[i] = score[i] / M * 100;
		sum += score[i];
	}

	printf("%.2f", sum / n);
}