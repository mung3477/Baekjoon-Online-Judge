#include <iostream>
#include <algorithm>
#include <utility>
using std::cin;
using std::cout;
using std::fill;
using std::pair;    //x, y

int ccw(pair<int, int>& A, pair<int, int>& B, pair<int, int>& C) {
    int x1 = A.first, y1 = A.second, x2 = B.first, y2 = B.second, x3 = C.first, y3 = C.second;
    
    long long result = (long long)(x2 - x1) * (y3 - y1) - (long long)(y2 - y1) * (x3 - x1);
    if (result > 0) return 1;
    else if (result == 0) return 0;
    else return -1;
}

struct line {
    pair<int, int> p;
    pair<int, int> q;
    
    line(): p(), q() {};
    line(int x1, int y1, int x2, int y2): p(std::make_pair(x1, y1)), q(std::make_pair(x2, y2)) {};
    
    bool intersectsWith(line& L) {
        int ccwThisToLP = ccw(p, q, L.p), ccwThisToLQ = ccw(p, q, L.q), ccwLToThisP = ccw(L.p, L.q, p), ccwLToThisQ = ccw(L.p, L.q, q);

        //한 직선 위
        if (ccwThisToLP == 0 && ccwThisToLQ == 0 && ccwLToThisP == 0 && ccwLToThisQ == 0) {
            if (q < p) swap(p, q);
            if (L.q < L.p) swap(L.p, L.q);
            
            //acbd cadb
            return p <= L.q && L.p <= q;
        }
        //normal
        else return (ccwThisToLP * ccwThisToLQ <= 0 && ccwLToThisP * ccwLToThisQ <= 0);
    }
};

int N;
line* lines;
int* root;
int* rank;  //group에 속한 선분 개수

int max(int a, int b) {
    if (a > b) return a;
    else return b;
}

int getRoot(int x) {
    if (root[x] == x) return x;
    else return root[x] = getRoot(root[x]);
}

void Union(int a, int b) {
    //이제부터 변수 a, b는 선분 a와 선분 b의 Root를 나타냄
    a = getRoot(a); b = getRoot(b);
    
    if (a == b) return;
    else if (rank[a] < rank[b]) {
        root[a] = b;
        rank[b] += rank[a];
    }
    else {
        root[b] = a;
        rank[a] += rank[b];
    }
}

int main()
{
    cin >> N;
    lines = new line[N + 1]{};
    root = new int[N + 1]{};
    rank = new int[N + 1]{};
    fill(&rank[1], &rank[N + 1], 1);
    
    for (int i = 1; i <= N; i++) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        
        lines[i] = line(x1, y1, x2, y2);
        root[i] = i;
    }

    
    for (int i = 2; i <= N; i++) {
        for (int j = 1; j < i; j++) {
            if (lines[i].intersectsWith(lines[j])) {
                Union(i, j);
            }
        }
    }
    
    //각 group에 몇 개의 선분이 들어있는지 셈
    int* group = new int[N + 1]{};
    for (int i = 1; i <= N; i++) {
        group[getRoot(i)]++;
    }
    
    //group의 숫자와 최대 선분 개수를 셈
    int groupNum = 0, maxElem = 0;
    for (int i = 1; i <= N; i++) {
        if (group[i]) {
            groupNum++;
            maxElem = max(maxElem, group[i]);
        }
    }

    cout << groupNum << "\n" << maxElem;
    
    return 0;
}
