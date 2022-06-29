#include <stdio.h>
#include <string.h>

int calc_prob(int *count, char *team_name)
{
    int temp_count['Z' - 'A' + 1] = {0, };
    int L = 0, O = 0, V = 0, E = 0;

    for (int i = 0; i <= 'Z' - 'A'; i++)
        temp_count[i] = count[i];
    
    for (int i = 0; team_name[i]; i++)
        temp_count[team_name[i] - 'A'] += 1;
    
    L = temp_count['L' - 'A'];
    O = temp_count['O' - 'A'];
    V = temp_count['V' - 'A'];
    E = temp_count['E' - 'A'];

    return ((((L + O) * (L + V) * (L + E)) % 100) * (((O + V) * (O + E) * (V + E)) % 100) % 100);
}

int main(void)
{
    int     count['Z' - 'A' + 1] = {0, };
    int     N;
    int     prob;
    int     best_prob;
    char    name[21] = {0, };
    char    team_name[21] = {0, };
    char    best_team_name[21] = {0, };

    prob = 0;
    best_prob = -1;

    scanf("%s", name);
    for (int i = 0; name[i] != '\0'; i++)
        count[name[i] - 'A'] += 1;
    
    scanf("%d", &N);
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < 21; j++)
            team_name[j] = '\0';

        scanf("%s", team_name);
        prob = calc_prob(count, team_name);

        if ((best_prob < prob) || \
            (best_prob == prob && strcmp((const char *)team_name, (const char *)best_team_name) < 0))
        {
            for (int j = 0; j < 21; j++)
                best_team_name[j] = '\0';
            strcpy(best_team_name, (const char *)team_name);
            best_prob = prob;
        }
    }

    printf("%s", best_team_name);
    return (0);
}