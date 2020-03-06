#include <stdio.h>

int main(void)
{
	int N, answer; //얘보다 작거나 같은 한 수의 개수 찾기
	scanf("%d", &N);

	if (N < 100)
		answer = N;
	else {
		int A, B, C;
		answer = 99;
		for (int i = 100; i <= N; i++) {
			C = i % 10;
			B = i % 100 / 10;
			A = i / 100;
			if (2 * B == A + C) {
				answer++;
			}
		}
	}
	printf("%d", answer);
	return 0;
}
