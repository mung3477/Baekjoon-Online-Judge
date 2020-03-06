#include <stdio.h>
#include <math.h>

int main(void)
{
    int T, x1, y1, r1, x2, y2, r2, ans;
    scanf("%d", &T);
    for(int i = 1; i <= T; i++){
        scanf(" %d %d %d %d %d %d", &x1, &y1, &r1, &x2, &y2, &r2);
        
        double d = (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
        d = pow(d, 0.5);

        int large, small;
        if(r1 > r2){
            large = r1;
            small = r2;
        }
        else{
            large = r2;
            small = r1;
        }

        if(x1 == x2 && y1 == y2){
                if(r1 == r2) ans = -1;
                else ans = 0;
        }

        else{
            if(d >= large){
                if(d == large + small) ans = 1;
                else if(d < large + small) ans = 2;
                else ans = 0;
            }
            else{
                if(d + small == large) ans = 1;
                else if(d + small > large) ans = 2;
                else ans = 0;
            }
        }
        printf("%d\n", ans);
    }
}