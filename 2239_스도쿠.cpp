#include <iostream>
using std::cin;
using std::cout;

int board[9][9]{};    //0 ~ 8
bool RowUsed[9][10]{};    //index는 0~ 8, 쓰는 숫자는 1 ~ 9
bool ColUsed[9][10]{};
bool AreaUsed[9][10]{};
bool done;

void toggle(int i, int j, int num, bool value) {
    RowUsed[i][num] = value;
    ColUsed[j][num] = value;
    AreaUsed[(i / 3) * 3 + (j / 3)][num] = value;
}

bool usable(int i, int j, int num) {
    return !RowUsed[i][num] && !ColUsed[j][num] && !AreaUsed[(i / 3) * 3 + (j / 3)][num];
}

void fillBlank(int i, int j) {
    //끝
    if(i == 9) {
        for (int row = 0; row < 9; row++) {
            for (int col = 0; col < 9; col++) {
                cout << board[row][col];
            }
            cout << "\n";
        }
        done = true;
        return;
    }
    
    //이미 채워진 칸인 경우
    if (board[i][j] != 0) {
        if (j == 8) fillBlank(i + 1, 0);
        else fillBlank(i, j + 1);
    }
    
    else {
        for (int n = 1; n <= 9; n++) {
            if (usable(i, j, n)) {
                board[i][j] = n;
                toggle(i, j, n, true);    //use n
                
                (j == 8 ? fillBlank(i + 1, 0) : fillBlank(i, j + 1));
                if (done) return;
                
                board[i][j] = 0;
                toggle(i, j, n, false);     //undo
            }
        }
    }
}

int main()
{
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            char ch = cin.get();
            int num = ch - '0';
            board[i][j] = num;
            if (num) toggle(i, j, num, true);
        }
        cin.get();  //LR CF
    }
    
    fillBlank(0, 0);
    
    return 0;
}
