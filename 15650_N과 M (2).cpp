#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::string;

int N, M;

void pickOne(int startFrom, int pickMore, string sequence) {
    if (pickMore) {
        for (int i = startFrom; i <= N; i++) {
            sequence += (i +'0');
            sequence += " ";
            pickOne(i + 1, pickMore - 1, sequence);
            sequence = sequence.substr(0, sequence.length() - 2);
        }
    }
    else {
        cout << sequence << '\n';
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin >> N >> M;
    pickOne(1, M, "");
   
    return 0;
}
