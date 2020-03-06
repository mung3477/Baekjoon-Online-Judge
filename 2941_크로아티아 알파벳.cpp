#include <stdio.h>
#include <string.h>

int main(void)
{
	char croatia[200] = { '2', 0};
	scanf("%s", &croatia[1]);
	int count = strlen(croatia) - 1;

	for (int i = 1; i < strlen(croatia); i++) {
		switch (croatia[i]) {
		case 'j':
			if (croatia[i - 1] == 'l' || croatia[i - 1] == 'n')
				count--;
			break;
		case '-':
			count--;
			break;
		case '=':
			if (croatia[i - 1] == 'c' || croatia[i - 1] == 's')
				count--;
			else if (croatia[i - 1] == 'z')
				if (croatia[i - 2] == 'd')
					count -= 2;
				else
					count--;
			break;
		}
	}
	printf("%d", count);
	return 0;
}