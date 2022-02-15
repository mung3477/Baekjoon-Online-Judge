#include <iostream>
#include <vector>
using std::cin;
using std::cout;
using std::vector;

int main()
{
    int W, N;
    bool able[400000]{};
    cin >> W >> N;
    
    vector<int> input;
    for (int i = 1; i <= N; i++) {
        int _t;
        cin >> _t;
        input.push_back(_t);
    }
    
    for (int i = 0; i < N - 1; i++) {
        for (int j = i + 1; j < N; j++) {
            int sum = input[i] + input[j];
            
            if (sum < W && W - sum < 400000 && able[W - sum]) {
                cout << "YES";
                return 0;
            }
        }
        
        for (int j = 0; j < i; j++) {
            able[input[i] + input[j]] = true;
        }
    }

    cout << "NO";

    return 0;
}
