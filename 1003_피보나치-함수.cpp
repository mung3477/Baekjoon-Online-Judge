#include <stdio.h>

int main(void)
{
    int T;
    scanf("%d", &T);

    for(int i = 1; i <= T; i++){
        int N;
        scanf("%d", &N);

        int zeros[41] = {1, 0, };
        int ones[41] = {0, 1, };

        for(int j = 2; j <= 40; j++){
            zeros[j] = zeros[j - 1] + zeros[j - 2];
            ones[j] = ones[j - 1] + ones[j - 2];
        }

        printf("%d %d\n", zeros[N], ones[N]);
    }

    return 0;
}