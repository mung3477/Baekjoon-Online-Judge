#include <stdio.h>

int main(void)
{
	int x, y;
	scanf("%d %d", &x, &y);
	int days[13] = { 0 , 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	int january_day = 0;

	for (int i = 1; i < x; i++) {
		january_day += days[i];
	}

	january_day += y;

	switch (january_day % 7) {
	case 1: 
		printf("MON");
		break;
	case 2:
		printf("TUE");
		break;
	case 3:
		printf("WED");
		break;
	case 4:
		printf("THU");
		break;
	case 5:
		printf("FRI");
		break;
	case 6:
		printf("SAT");
		break;
	case 0:
		printf("SUN");
		break;
	}

	return 0;
}