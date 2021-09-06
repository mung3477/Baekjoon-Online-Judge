#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::string;
using std::to_string;

string stringAdd(string& a, string& b) {
    //두 string 길이 맞추기
    string newA = a;
    string newB = b;
    
    if (a.length() > b.length()) {
        string temp(a.length() - b.length(), '0');
        newB = temp + newB;
    }
    else {
        string temp(b.length() - a.length(), '0');
        newA = temp + newA;
    }
    
    int sum, carry = 0, A, B, i;
    string result(newA.length(), '0');
       
    for (i = newA.length() - 1; i >= 0; i--) {
        A = newA.at(i) - '0';
        B = newB.at(i) - '0';
        
        sum = A + B + carry;
        
        if (sum > 9) {
            carry = 1;
            sum -= 10;
        }
        else {
            carry = 0;
        }
        
        result.at(i) = sum + '0'; 
    }
    
    if (carry) {
        string carryStr = "1";
        result = carryStr + result;
    }
    
    return result;
}

int main()
{
   std::ios_base::sync_with_stdio(false);
   cin.tie(NULL);
   cout.tie(NULL);
   
   int N, M;
   string** pascal;
   
   cin >> N >> M;
   
   pascal = new string*[N + 1];
   for (int i = 1; i <= N; i++) {
       pascal[i] = new string[i + 1]{};
   }
   
   for (int i = 1; i <= N; i++) {
       for (int j = 1; j <= i; j++) {
            if (j == 1) {
                pascal[i][j] = to_string(i);
            }
            else if (j == i) {
                pascal[i][j] = "1";
            }
            else {
                pascal[i][j] = stringAdd(pascal[i - 1][j - 1], pascal[i - 1][j]); 
            }
       }
   }
   
   cout << pascal[N][M] << '\n';
   
   return 0;
}
