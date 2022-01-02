#include <iostream>
#include <utility>
#include <stack>
using std::cin;
using std::cout;
using std::pair;    //height, index
using std::make_pair;
using std::stack;

int main(void) {
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int N;
    cin >> N;

    int height;
    long long ans = 0;
    stack<pair<int, int>> st;

    for (int i = 1; i <= N; i++) {
        cin >> height;

        while (!st.empty() && st.top().first < height) {
            // 중복 묶음 OR 1개 제거 -> 묶음과 new가 만들어내는 조합 수 ans에 추가
            ans += st.top().second;
            st.pop();
        }

        if (!st.empty() && st.top().first == height) {
            //기존 중복들과 new가 만들어내는 조합 수 && 기존 중복들처럼 이전 stack top과 new가 만드는 조합 ans에 추가
            ans += st.top().second;
            if (st.size() > 1) ans++;
            
            st.top().second++;
            continue;
        }

        //stack top과 new의 pair 1개 추가
        if (st.size()) ans++;
        st.emplace(height, 1);
    }

    cout << ans;

    return 0;
}
