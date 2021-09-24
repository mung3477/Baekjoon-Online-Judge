#include <iostream>
#include <vector>
#include <algorithm>
using std::cin;
using std::cout;
using std::vector;
using std::sort;

int N, M;
int* permutation;
bool* used;
vector<int> numbers;

void pickOne(int index, int usableLeastIndex) {
    if (index <= M) {
        for (int i = usableLeastIndex; i <= N; i++) {
            
            permutation[index] = numbers.at(i);
            pickOne(index + 1, i);
            
        }
    }
    else {
        for (int i = 1; i <= M; i++) {
            cout << permutation[i] << " ";
        }
        cout << "\n";
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    int input;
    cin >> N >> M;
    
    permutation = new int[M + 1]{};
    used = new bool[N + 1]{};
    numbers.push_back(-1);
    
    for (int i = 1; i <= N; i++) {
        cin >> input;
        numbers.push_back(input);
    }
    
    sort(numbers.begin(), numbers.end());
    
    pickOne(1, 1);
   
    return 0;
}
