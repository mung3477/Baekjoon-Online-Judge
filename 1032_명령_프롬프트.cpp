#include <stdio.h>

int my_strlen(char *str)
{
    int i;

    i = 0;
    while (str[i])
        i += 1;
    return (i);
}

int main(void)
{
    int     n;
    int     i;
    int     j;
    int     ans_len;
    char    cur;
    char    names[51][51] = {0, };
    char    answer[51] = {0, };

    i = 0;
    scanf("%d", &n);
    while (i < n)
        scanf("%s", names[i++]);
    ans_len = my_strlen(names[0]);
    answer[ans_len] = '\0';
    
    j = 0;
    while (names[0][j])
    {
        i = 1;
        cur = names[0][j];
        while (i < n && names[i][j] == cur)
            i += 1;
        if (i != n)
            answer[j] = '?';
        else
            answer[j] = cur;
        j += 1;
    }
    printf("%s", answer);
    return (0);
}