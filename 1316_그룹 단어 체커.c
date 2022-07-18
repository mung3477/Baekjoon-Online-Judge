#include <stdio.h>

int isGroupWord(void)
{
    int     appeared['z' - 'a' + 1] = {0, };
    int     j;
    char    word[101];

    scanf("%s", word);

    for (int i = 0; word[i]; i++) 
    {
        if (appeared[word[i] - 'a'])
            return (0);
        appeared[word[i] - 'a'] = 1;

        j = i + 1;
        while (word[j] && word[i] == word[j])
            j += 1;
        i = j - 1;
    }
    return (1);
}

int main(void)
{
    int N, ans;
    
    scanf("%d\n", &N);
    ans = 0;

    for (int i = 1; i <= N; i++)
        ans += isGroupWord();
    printf("%d", ans);
    return (0);
}