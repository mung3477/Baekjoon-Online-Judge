#include <stdio.h>

int main(void)
{
	int X;
	scanf("%d", &X);

	int n = 1;

	while (n * (n + 1) / 2 < X) {
		n++;
	}
	
	if (n % 2) {	
		printf("%d/%d", n - X + ((n - 1) * n / 2) + 1, X - ((n - 1) * n / 2));
	}
	
	else {
		printf("%d/%d", X - ((n - 1) * n / 2), n - X + ((n - 1) * n / 2) + 1);
	}
}
