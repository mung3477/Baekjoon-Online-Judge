#include <stdio.h>

int main(void)
{
	int N, answer; //�꺸�� �۰ų� ���� �� ���� ���� ã��
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
