#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using std::cin;
using std::cout;
using std::vector;
using std::priority_queue;
using std::sort;

struct Section {
    int start;
    int end;

    Section(int start, int end): start(start), end(end) {};
};

// end 오름차순, 동률일 경우 start 오름차순 정렬
struct SortCompare {
    bool operator()(const Section& A, const Section& B) {
        return (A.end < B.end || (A.end == B.end && A.start < B.start));
    }
} sortCompare;

// start 오름차순
struct PQCompare {
    bool operator()(const Section& A, const Section& B) {
        return (A.start > B.start);
    }
};

// @return next와 top이 묶일 수 있는지: next안에 top이 있거나, next의 end를 끝으로 하는 길이 d의 선분과 top이 묶일 수 있는지
bool canGroupTogether(const Section& top, const Section& next, const int& d) {
    return (next.start <= top.start) || (next.end - d <= top.start);
}

int max(int a, int b) {
    if (a > b) return a;
    else return b;
}

int main(void) {
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int N, home, occupation, d, answer = 0;
    vector<Section> input;

    cin >> N;

    for (int i = 1; i <= N; i++) {
        cin >> home >> occupation;

        if (home > occupation) {
            int t = home;
            home = occupation;
            occupation = t;
        }

        input.emplace_back(home, occupation);
    }

    cin >> d;

    sort(input.begin(), input.end(), sortCompare);
    
    priority_queue<Section, vector<Section>, PQCompare> leftSide;
    for (const Section& s : input) {
        if (d < s.end - s.start) continue;

        while (!leftSide.empty() && !canGroupTogether(leftSide.top(), s, d)) leftSide.pop();
        leftSide.push(s);
        answer = max(answer, leftSide.size());
    }

    cout << answer;

    return 0;
}
