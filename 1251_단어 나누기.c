#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char    *my_strdup(char* src, int len)
{
    char    *dst = malloc(sizeof(char) * (len + 1));
    
    for (int i = 0; i < len; i++) {
        dst[i] = src[i];
    }
    dst[len] = '\0';
    return (dst);
}

char    *make_new(char* word, int sec_st, int thr_st, int len)
{
    char    *new = malloc(sizeof(char) * (len + 1));
    int     i;

    for (i = 0; i < sec_st; i++)
        new[i] = word[sec_st - 1 - i];
    for (i = 0; sec_st + i < thr_st; i++)
        new[sec_st + i] = word[thr_st - 1 - i];
    for (i = 0; thr_st + i < len; i++)
        new[thr_st + i] = word[len - 1 - i];
    new[len] = '\0';
    return (new);
}

int main(void)
{
    char    word[51] = {0, };
    char*   ans;
    char*   new;
    int     len;

    scanf("%s", word);
    len = strlen((const char*)word);
    ans = (char*)malloc(sizeof(char) * (len + 1));
    for (int i = 0; i < len; i++)
        ans[i] = 'z';
    ans[len] = '\0';

    for (int i = 1; i < len - 1; i++) {
        for (int j = i + 1; j < len; j++) {
            new = make_new(word, i, j, len);
            if (strcmp((const char*)new, (const char*)ans) < 0) {
                free(ans);
                ans = new;
            }
            else
                free(new);
        }
    }
    printf("%s", ans);
    free(ans);
    return (0);
}