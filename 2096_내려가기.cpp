#include <iostream>
#include <string.h>
using std::cin;
using std::cout;

int bigger(int a, int b) {
    if (a > b) return a;
    else return b;
}

int smaller(int a, int b) {
    if (a < b) return a;
    else return b;
}


int bigger_3(int a, int b, int c) {
    int biggest = bigger(a, b);
    if (biggest > c) return biggest;
    else return c;
}

int smaller_3(int a, int b, int c) {
    int smallest = smaller(a, b);
    if (smallest < c) return smallest;
    else return c;
}

int main()
{
   std::ios_base::sync_with_stdio(false);
   cin.tie(NULL);
   cout.tie(NULL);
   
   int N, i, j, biggest;
   int maxData[3]{};
   int minData[3]{};
   int input[3]{};
   
  
   cin >> N;
   
   //initialize
   for (j = 0; j < 3; j++) {
           cin >> maxData[j];
           minData[j] = maxData[j];
       }
   //DP
   for (i = 1; i < N; i++) {
       for (j = 0; j < 3; j++) {
           cin >> input[j];
       }
       int newMaxData[3]{};
       
        newMaxData[0] = bigger(maxData[0], maxData[1]) + input[0];
        newMaxData[1] = bigger_3(maxData[0], maxData[1], maxData[2]) + input[1];
        newMaxData[2] = bigger(maxData[1], maxData[2]) + input[2];

       memcpy(maxData, newMaxData, sizeof(int) * 3);
       
       int newMinData[3]{};
       newMinData[0] = smaller(minData[0], minData[1]) + input[0];
       newMinData[1] = smaller_3(minData[0], minData[1], minData[2]) + input[1];
       newMinData[2] = smaller(minData[1], minData[2]) + input[2];
       
       memcpy(minData, newMinData, sizeof(int) * 3);
   }
   
   
   cout << bigger_3(maxData[0], maxData[1], maxData[2]) << " "<< smaller_3(minData[0], minData[1], minData[2]);
   
   return 0;
}
