#include <iostream>
using std::cin;
using std::cout;

int bigger(int a, int b) {
    if (a > b) return a;
    else return b;
}

int main()
{
   int N, size, depth, j, curDepthLast;
   int* input;
   int* max;
   
   cin >> N;
   
   size = N * (N + 1) / 2;
   input = new int[size]{};
   max = new int[size]{};
   
   //fill the triangle
   for (int i = 0; i < size; i++) {
       cin >> input[i];
   }
   
   //fill max path cost from bottom to top
   depth = j = N;
   for (int i = size - 1; i >= 0; i--) {
       if (j == 0) {
           depth--;
           j = depth;
           curDepthLast = i;
       }
       
       if (size - N <= i) {
           max[i] = input[i];
       }
       else {
           max[i] = input[i] + bigger(max[curDepthLast + j], max[curDepthLast + j + 1]);
       }
       j--;
   }
   
   cout << max[0];
   
   return 0;
}
