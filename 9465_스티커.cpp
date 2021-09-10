#include <iostream>
using std::cin;
using std::cout;

int max(int a, int b) {
    if (a > b) return a;
    else return b;
}

int main()
{
   std::ios_base::sync_with_stdio(false);
   cin.tie(NULL);
   cout.tie(NULL);
   
   int T, N;
   //0이 위, 1이 아래
   int** sticker;
   int** DP;
   
   cin >> T;
   for (T; T > 0; T--) {
       cin >> N;
       
       sticker = new int*[N + 1];
       DP = new int*[N + 1];
       for (int i = 0; i <= N; i++) {
           sticker[i] = new int[2]{};
           DP[i] = new int[2]{};
       }
       
       for (int i = 1; i <= N; i++) {
           cin >> sticker[i][0];
       }
       
       for (int i = 1; i <= N; i++) {
           cin >> sticker[i][1];
       }
       
       DP[0][0] = sticker[0][0];
       DP[0][1] = sticker[0][1];
       
       DP[1][0] = DP[0][1] + sticker[1][0];
       DP[1][1] = DP[0][0] + sticker[1][1];
       
       for (int i = 2; i <= N; i++) {
           DP[i][0] = max(DP[i - 1][1], DP[i - 2][1]) + sticker[i][0];
           DP[i][1] = max(DP[i - 1][0], DP[i - 2][0]) + sticker[i][1];
       }
       
       cout << max(DP[N][0], DP[N][1]) << "\n";
       
       for (int i = 0; i <= N; i++) {
           delete[] sticker[i], DP[i];
       }
       delete[] sticker, DP;
   }
   
   return 0;
}
