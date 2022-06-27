#include <stdio.h>

int history[1001][6];
int friends[1001];

int main(void)
{
    int N, ans, max_friend, friend;

    ans = 1;
    max_friend = 0;
    scanf("%d", &N);
    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= 5; j++)
            scanf("%d", &history[i][j]);

    for (int i = 1; i < N; i++)
        for (int j = i + 1; j <= N; j++)
            for (int grade = 1; grade <= 5; grade++)
            {
                if (history[i][grade] == history[j][grade])
                {
                    friends[i] += 1;
                    friends[j] += 1;
                    break;
                }
            }

    for (int i = 1; i <= N; i++)
    {
        if (max_friend < friends[i])
        {
            max_friend = friends[i];
            ans = i;
        }
    }

    printf("%d", ans);
    return (0);
}