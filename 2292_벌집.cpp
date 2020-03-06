#include <stdio.h>

int main(void)
{
	int N;
	scanf("%d", &N);

	int k = 1;
	
	while (1 + 3 * k * (k-1) < N) {		//Sn이 N보다 크거나 같으면 탈출
		k += 1;
	}
	
	printf("%d", k);
}
