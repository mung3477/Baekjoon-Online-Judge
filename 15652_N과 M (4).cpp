#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::string;

int N, M;
int* sequence;

void pickOne(int startFrom, int index) {
    if (index <= M) {
        for (int i = startFrom; i <= N; i++) {
            sequence[index] = i;
            pickOne(i, index + 1);
        } 
    }
    else {
        for (int i = 1; i <= M; i++) {
            cout << sequence[i] << ' ';
        }
        cout << "\n";
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin >> N >> M;
    sequence = new int[M + 1]{};
    pickOne(1, 1);
   
    return 0;
}
