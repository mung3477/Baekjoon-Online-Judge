#include <stdio.h>
int first_loc[26];
char word[100] = { NULL };

int main(void)
{
	for (int i = 0; i < 26; i++) {
		first_loc[i] = -1;
	}

	scanf("%s", word);
	int j = 0;
	while (word[j]) {
		char alph = word[j];
		if (first_loc[alph - 'a'] == -1) 
			first_loc[alph - 'a'] = j;
		j++;
	}
	for (int i = 0; i < 26; i++)
		printf("%d ", first_loc[i]);

	return 0;
}