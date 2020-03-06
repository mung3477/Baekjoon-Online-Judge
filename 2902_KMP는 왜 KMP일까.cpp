#include <stdio.h>
#include <string.h>

int main(void)
{
	int count = 0;
	char shorten[100] = { 0, };
	char n = getchar();
	shorten[count] = n;

	while (1) {
		n = getchar();
		if (n == '\n') break;
		else if (n == '-') {
			count++;
			n = getchar();
			shorten[count] = n;
		}
	}
	printf("%s", shorten);
	
	return 0;
}