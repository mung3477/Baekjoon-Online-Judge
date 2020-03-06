#include <stdio.h>

int use_able[9];

void load() 
{
	for (int i = 0; i < 10; i++) {
		use_able[i]++;
	}
	use_able[6]++;
	use_able[9]++;
}

int main(void)
{
	int N, set = 1;
	scanf("%d", &N);

	load();

	while (N) {
		if (use_able[N % 10] == 0) {
			load();

		}

		use_able[N % 10]--;
	}
	
}