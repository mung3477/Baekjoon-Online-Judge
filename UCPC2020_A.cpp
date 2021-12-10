#include <cstdio>

int main(void)
{
    int a, b, c, d, e, f, x, y;
    bool solv = false;

    scanf(" %d %d %d %d %d %d", &a, &b, &c, &d, &e, &f);
    
    for(x = -999; x <= 999; x++){
        for(y = -999; y <= 999; y++){
            if(a*x + b*y == c && d*x + e*y == f){
                solv = true;
                break;
            }
        }
        if(solv) break;
    }

    printf("%d %d", x, y);
    return 0;
}