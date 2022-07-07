#include <stdio.h>
#include <stdlib.h>

int*    merge(int* lHalf, int* rHalf, int lSize, int rSize)
{
    int*    sorted = (int *)malloc(sizeof(int) * (lSize + rSize));
    int     l = 0, r = 0, s = 0;

    while (l < lSize && r < rSize)
    {
        if (lHalf[l] < rHalf[r])
            sorted[s++] = lHalf[l++];
        else
            sorted[s++] = rHalf[r++];
    }
    while (l < lSize)
        sorted[s++] = lHalf[l++];
    while (r < rSize)
        sorted[s++] = rHalf[r++];
    return (sorted);
}

int*    mergeSort(int* numbers, int left, int right)
{
    int     mid;
    int*    lHalf;
    int*    rHalf;
    int*    sorted;

    if (left == right)
    {
        sorted = (int *)malloc(sizeof(int) * 1);
        sorted[0] = numbers[left];
        return (sorted);
    }

    mid = ((long long)left + right) / 2;
    lHalf = mergeSort(numbers, left, mid);
    rHalf = mergeSort(numbers, mid + 1, right);
    sorted = merge(lHalf, rHalf, mid - left + 1, right - mid);
    free(lHalf);
    free(rHalf);
    return (sorted);
}

int find(int* sorted, int targ, int l, int r)
{
    int mid;
    
    if (l == r)
        return (targ == sorted[l]);
    
    mid = (l + r) / 2;
    if (targ == sorted[mid])
        return (1);
    else if (targ < sorted[mid])
        return (find(sorted, targ, l, mid));
    else
        return (find(sorted, targ, mid + 1, r));
}

int main(void)
{
    int N;
    int M;
    int targ;
    int*    numbers;
    int*    sorted;
    
    scanf("%d", &N);
    numbers = (int *)malloc(sizeof(int) * N);
    for (int i = 0; i < N; i++)
        scanf("%d", &numbers[i]);
    sorted = mergeSort(numbers, 0, N - 1);

    scanf("%d", &M);
    for (int i = 0; i < M; i++)
    {
        scanf("%d", &targ);
        printf("%d", find(sorted, targ, 0, M - 1));
        if (i != M - 1)
            printf("\n");
    }
    
    free(numbers);
    free(sorted);
    return (0);
}