#include <iostream>
#include <stack>
using std::cin;
using std::cout;
using std::stack;

struct stackElem {
    int number;
    int LISlength;
    
    stackElem(): number(0), LISlength(0) {};
    stackElem(int number, int LISlength): number(number), LISlength(LISlength) {};
};

int N, longestLength = 0;
int* given;
int* increasingSeq;    
stack<stackElem> backtrack;

int lower(int left, int right, int target) {
    if (left == right) return left;
    
    int mid = (left + right) / 2 + 1;
    if (increasingSeq[mid] < target) return lower(mid, right, target);
    else return lower(left, mid - 1, target);
}

int main()
{
    cin >> N;
    given = new int[N + 1]{};
    increasingSeq = new int[N + 1]{};

    for (int i = 1; i <= N; i++) cin >> given[i];
    
    increasingSeq[1] = given[1];
    backtrack.emplace(given[1], 1);
    longestLength++;
    
    //make possible longest increasing sequence using given[i]
    for (int i = 2; i <= N; i++) {
        int position = lower(0, longestLength, given[i]) + 1;
        increasingSeq[position] = given[i];
        backtrack.emplace(given[i], position);
        
        if (longestLength < position) longestLength = position;
    }
    
    cout << longestLength << "\n";
    int target = longestLength;
    stack<int> answer;
    
    while (!backtrack.empty() && target != 0) {
        stackElem top = backtrack.top();
        backtrack.pop();
        
        if (top.LISlength == target) {
            answer.push(top.number);
            target--;
        }
    }
    
    while (!answer.empty()) {
        cout << answer.top() << " ";
        answer.pop();
    }
    
    return 0;
}
