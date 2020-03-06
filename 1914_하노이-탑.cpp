#include <stdio.h>

//s: start, d: destination, w: waypoint, N: number of boards to move
void hanoi(int s, int d, int w, int N)
{
    //base case
    if(N == 1) {
        printf("%d %d\n", s, d);
    }

    //typical case
    else {
        hanoi(s, w, d, N - 1);
        hanoi(s, d, w, 1);
        hanoi(w, d, s, N - 1);
    }

}

int main(void)
{
    int N;
    scanf("%d", &N);

    int curDigit = 1;
    int hanoiCal[51] = {1, };

    for(int i = 1; i <= N; i++) {     
        //multiply 2
        for(int j = curDigit - 1; j >= 0; j--) {
            int newNum = hanoiCal[j] * 2;
            if(newNum > 9) {
                hanoiCal[j + 1]++;
                newNum -= 10;
            }
            hanoiCal[j] = newNum;
        }
        
        if(hanoiCal[curDigit]) { curDigit++; }
    }
    //subtract 1
    hanoiCal[0] -= 1;

    for(int i = curDigit - 1; i >= 0; i--) {
        printf("%d", hanoiCal[i]);
    }
    printf("\n");
    
    if(N <= 20) {
        hanoi(1, 3, 2, N);
    }
}