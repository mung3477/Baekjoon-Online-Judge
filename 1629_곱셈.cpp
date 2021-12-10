#include <cstdio>

unsigned long long multiply(int A, int B, int C){
    unsigned long long t;
    //base case
    if(B == 1){
        t = A % C;
    }
    else if(B == 0){
        t = 1;
    }
    //typical case
    else{
        //B is odd
        if(B % 2){
            t = multiply(A, B / 2, C) % C; 
            t = (((t * t) % C) * A) % C;
        }
        //B is even
        else{
            t = multiply(A, B / 2, C) % C; 
            t = (t * t) % C;
        }
    }
    return t;
}

int main(void)
{
    unsigned long long ans = 0;
    int A, B, C;
    scanf(" %d %d %d", &A, &B, &C);

    ans = multiply(A, B, C);
    printf("%d", ans % C);
}
