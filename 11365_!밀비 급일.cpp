#include <stdio.h>
#include <string.h>

int main(void)
{
	char end[5] = "END\n";
	while (1) {
		char crypt[600] = { 0, };
		fgets(crypt, 600, stdin);
		if (!strcmp(crypt, end)) return 0;
		else {
			for (int i = strlen(crypt) - 2; i >= 0; i--) {
				printf("%c", crypt[i]);
			}
			printf("\n");
		}
	}
}
