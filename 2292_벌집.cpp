#include <stdio.h>

int main(void)
{
	int N;
	scanf("%d", &N);

	int k = 1;
	
	while (1 + 3 * k * (k-1) < N) {		//Sn�� N���� ũ�ų� ������ Ż��
		k += 1;
	}
	
	printf("%d", k);
}
