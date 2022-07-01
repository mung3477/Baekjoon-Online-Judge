#include <stdio.h>

void    sort(int *scores, int N)
{
    int t;

    for (int i = 2; i < N - i + 1; i++)
    {
        for (int j = 2; j <= N - i + 1; j++)
        {
            if (scores[j - 1] < scores[j])
            {
                t = scores[j - 1];
                scores[j - 1] = scores[j];
                scores[j] = t;
            }
        }
    }
}

int     find_ranking(int *scores, int P, int score)
{
    int rank[51] = {0, };
    int my_rank, i;

    my_rank = -1;

    for (i = 1; i <= P; i++)
        rank[i] = (scores[i] == scores[i - 1] ? rank[i - 1] : i);

    for (i = 1; i <= P; i++)
    {
        if (scores[i] < score)
        {
            my_rank = (score == scores[i - 1] ? rank[i - 1] : rank[i]);
            break;
        }
    }
    return (my_rank);
}

int main(void)
{
    int N, score, P, ans = -1;
    int scores[51] = {-1, };

    scanf("%d %d %d", &N, &score, &P);
    if (N == 0)
        ans = 1;
    else {
        for (int i = 1; i <= N; i++)
            scanf("%d", &scores[i]);
        for (int i = N + 1; i <= 50; i++)
            scores[i] = -1;
        sort(scores, N);
        ans = find_ranking(scores, P, score);
    }

    printf("%d", ans);
    return (0);
}