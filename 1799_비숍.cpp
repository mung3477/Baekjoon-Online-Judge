#include <iostream>
using std::cin;
using std::cout;

bool* RUdiag;   //0부터 시작. [i][j] 사용 시 RUdiag[i + j] = true
bool* RDdiag;   //0부터 시작. [i][j] 사용 시 RDDIag[i - j + (N - 1)] = true
int maxOddlineNum, maxEvenlineNum, N;
bool** map;

bool usable(int i, int j) { 
    return (map[i][j] && !RUdiag[i + j] && !RDdiag[i - j + (N - 1)]);
}

void use(int i, int j) {
    RUdiag[i + j] = !RUdiag[i + j];
    RDdiag[i - j + (N - 1)] = !RDdiag[i - j + (N - 1)];
}

int max(int a, int b) {
    if (a > b) return a;
    else return b;
}

void BishopTraverse(int line, int used) {
    //terminate condition
    if ((N - 1) * 2 + 1 <= line) {
        if (line % 2) maxOddlineNum = max(maxOddlineNum, used);
        else maxEvenlineNum = max(maxEvenlineNum, used);
        
        return;
    }
    
    //normal operation
    for (int i = (line <= N - 1 ? line : N - 1), orgI = i; line - orgI <= i; i--) {
        int j = line - i;
        if(usable(i, j)) {
            use(i, j);
            BishopTraverse(line + 2, used + 1);
            use(i, j);
        }
    }
    //didn't use this line
    BishopTraverse(line + 2, used);
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin >> N;
    
    RUdiag = new bool[(N - 1) * 2 + 1]{};
    RDdiag = new bool[(N - 1) * 2 + 1]{};
    map = new bool*[N];
    for (int i = 0; i < N; i++) {
        map[i] = new bool[N];
        for (int j = 0; j < N; j++)
            cin >> map[i][j];
    }
    
    BishopTraverse(0, 0);
    BishopTraverse(1, 0);
    
    
    cout << maxEvenlineNum + maxOddlineNum;
    
    return 0;
}
