#include <iostream>
#include <string>
#include <stack>
#include <cmath>
using std::cin;
using std::cout;
using std::string;
using std::stack;
using std::pow;

string makeBinary(long long A) {
    string retVal = "";
    stack<int> lefts;
    while (2 <= A) {
        lefts.push(A % 2);
        A /= 2;
    }
    lefts.push(A);
    
    while (!lefts.empty()) {
        retVal += lefts.top() + '0';
        lefts.pop();
    }
    
    return retVal;
}

long long combSum(int n, int onesBefore) {
    if (n == 0) n = 1;
    return (long long)pow(2, n - 1) * (n + 2 * onesBefore);
}

long long howManyOnes(string& binary, int index, int onesBefore) {
    if (index == binary.length()) return 0;
    
    else if (binary.at(index) == '1') {
        return combSum(binary.length() - index - 1, onesBefore) + howManyOnes(binary, index + 1, onesBefore + 1);
    }
    else if (index == binary.length() - 1) return onesBefore;
    else return howManyOnes(binary, index + 1, onesBefore);
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    long long A, B;
    cin >> A >> B;
    
    A = A - 1;  //등호 조건을 위해서
    
    string BinaryA = makeBinary(A);
    string BinaryB = makeBinary(B);
    
    cout << howManyOnes(BinaryB, 0, 0) - howManyOnes(BinaryA, 0, 0);
    
    return 0;
}
