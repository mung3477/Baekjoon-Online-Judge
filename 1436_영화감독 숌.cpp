#include <stdio.h>

int main(void)
{
	int N, title, count = 0, head = 0;
	scanf("%d", &N);
	
	while(count != N) {
		if (head % 10 == 6) {
			if (head % 100 == 66) {
				if (head % 1000 == 666) {		//_666___
					for (int i = count, j = 0; count != i + 1000; j++, count++) {
						if (count == N) break;
						title = head * 1000 + j;
					}
				}
				else {							//__66___
					for (int i = count, j = 0; count != i + 100; j++, count++) {
						if (count == N) break;
						title = head * 1000 + 600 + j;
					}
				}
			}									//___6___
			else {
				for (int i = count, j = 0; count != i + 10; j++, count++) {
					if (count == N) break;
					title = head * 1000 + 660 + j;
				}
			}
		}
		else {									//______
			title = head * 1000 + 666;
			count++;
		}
		head++;
	}
	printf("%d", title);
}
