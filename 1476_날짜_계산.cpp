#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void)
{
	int E, S, M;
	scanf("%d %d %d", &E, &S, &M);

	int e = 0, s = 0, m = 0;
	int* ePtr = &e;
	int* sPtr = &s;
	int* mPtr = &m;
	
	while (1) {

		if (15 * *ePtr + E == 28 * *sPtr + S) {
			m = 0;
			while (15 * *ePtr + E >= 19 * *mPtr + M) {
				if (15 * *ePtr + E == 19 * *mPtr + M) {
					printf("%d", 19 * *mPtr + M);
					return 0;
				}
				(*mPtr)++;
			}
		}

		if (15 * *ePtr + E > 28 * *sPtr + S) {	
			(*sPtr)++;
			(*ePtr)--;
			continue;
		}
		(*ePtr)++;
	}
}