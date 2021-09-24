#include <iostream>
#include <vector>
#include <algorithm>
using std::cin;
using std::cout;
using std::vector;
using std::sort;

int N, M;
int* permutation;
vector<int> numbers;
int left[10001];

void pickOne(int index) {
    if (index <= M) {
        for (int i = 1; i < numbers.size(); i++) {
            if (left[numbers.at(i)]) {
                left[numbers.at(i)]--;
                permutation[index] = numbers.at(i);
                pickOne(index + 1);
                left[numbers.at(i)]++;
            }
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
    numbers.push_back(-1);
    
    for (int i = 1; i <= N; i++) {
        cin >> input;
        if (!left[input]) numbers.push_back(input);
        left[input]++;
    }
    
    sort(numbers.begin(), numbers.end());
    
    pickOne(1);
   
    return 0;
}
