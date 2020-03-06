#include <stdio.h>

char S[20];

int main(void)
{
	int T; //테스트 케이스 개수
	scanf("%d", &T);

	while (T) 
	{
		int R; //반복 횟수
		scanf("%d", &R);
		scanf("%s", S);

		int j = 0;
		while (S[j]) {
			for (int k = R; k > 0; k--)
				printf("%c", S[j]);
			j++;
		}

		printf("\n");
		T--;
	}

	return 0;
}
