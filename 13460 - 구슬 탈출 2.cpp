#include <iostream>
#include <queue>
using std::cin;
using std::cout;
using std::queue;

int N, M, answer = -1;
bool done = false;

struct pos {
    int row;
    int col;
    
    pos(): row(-1), col(-1) {};
    pos(int row, int col): row(row), col(col) {};
};

struct situation {
    char** board;
    int depth;
    pos red;
    pos blue;
    
    situation(): board(nullptr), depth(0), red(), blue() {};
    situation(const situation& sit) {
        board = copyBoard(sit.board);
        depth = sit.depth;
        red = sit.red;
        blue = sit.blue;
    };
    
    void showBoard() {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                cout << board[i][j];
            }
            cout << "\n";
        }
    }
    char** copyBoard(char** origBoard) {
        char** newBoard = new char*[N];
        for (int i = 0; i < N; i++) {
            newBoard[i] = new char[M];
            for (int j = 0; j < M; j++) {
                newBoard[i][j] = origBoard[i][j];
            }
        }
        return newBoard;
    }
    bool movable(int row, int col) {
        return !(board[row][col] == '#' || board[row][col] == 'R' || board[row][col] == 'B');
    }
    
    /* 
        move 함수 :
        @return {bool} - 움직인 구슬이 구멍이 끼면 true, 아니면 false
    */
    bool moveUp(pos& biz);
    bool moveDown(pos& biz);
    bool moveLeft(pos& biz);
    bool moveRight(pos& biz);
    
    /*
        tilt 함수 : 이 상황에서 X 방향으로 기울임
        Blue 구슬이 구멍에 끼면 board가 nullPtr, 아니면 tilt 결과물.
        Red 구슬이 구멍에 끼면 어차피 done에서 걸림.
    */
    void tiltUp();
    void tiltDown();
    void tiltLeft();
    void tiltRight();
};

bool moved(situation& A, situation& B) {
    return (A.red.row != B.red.row || A.red.col != B.red.col || A.blue.row != B.blue.row || A.blue.col != B.blue.col);
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin >> N >> M;
    
    situation init;
    queue<situation> frontier;
    
    init.depth = 0;
    init.board = new char*[N];
    for (int i = 0; i < N; i++) {
        init.board[i] = new char[M]{};
        for (int j = 0; j < M; j++) {
            cin >> init.board[i][j];
            if (init.board[i][j] == 'R') {
                init.red.row = i;
                init.red.col = j;
            }
            else if (init.board[i][j] == 'B') {
                init.blue.row = i;
                init.blue.col = j;
            }
        }
    }
    
    frontier.push(init);
    while (!frontier.empty()) {
        situation* cur = &frontier.front();
        /*cout << "depth : " << cur->depth << "\n";
        cur->showBoard();
        cout << done << "\n\n";*/
        
        //BFS
        if (cur->depth < 10) {
            situation up(*cur);
            up.tiltUp();
            
            situation down(*cur);
            down.tiltDown();
            
            situation left(*cur);
            left.tiltLeft();
            
            situation right(*cur);
            right.tiltRight();
            
            if (up.board != nullptr && moved(*cur, up)) frontier.emplace(up);
            if (down.board != nullptr && moved(*cur, down)) frontier.emplace(down);
            if (left.board != nullptr && moved(*cur, left)) frontier.emplace(left);
            if (right.board != nullptr && moved(*cur, right)) frontier.emplace(right);
        }
        
        if (done) {
            answer = cur->depth + 1;
            break;
        }
        
        for (int i = 0; i < N; i++) delete[] cur->board[i];
        delete[] cur->board, cur;
        frontier.pop();
    }
    cout << answer;
    
    return 0;
}

//구멍에 낌 : 1, 특별한 일 없음: 0
bool situation::moveUp(pos& biz) {
    //움직일 수 없으면 바로 terminate
    if (!movable(biz.row - 1, biz.col)) return false;
    
    int newRow;
    for (newRow = biz.row - 1; board[newRow][biz.col] == '.'; newRow--);
    
    //구멍이면 구슬 빼고 return true
    if (board[newRow][biz.col] == 'O') {
        board[biz.row][biz.col] = '.';
        biz.row = newRow;
        return true;
    }
    //벽이나 다른 구슬이면 그 아래칸까지 구슬 이동
    else {
        board[newRow + 1][biz.col] = board[biz.row][biz.col];
        board[biz.row][biz.col] = '.';
        biz.row = newRow + 1;
        return false;
    }
}
bool situation::moveDown(pos& biz) {
    //움직일 수 없으면 바로 terminate
    if (!movable(biz.row + 1, biz.col)) return false;
    
    int newRow;
    for (newRow = biz.row + 1; board[newRow][biz.col] == '.'; newRow++);
    
    //구멍이면 구슬 빼고 return true
    if (board[newRow][biz.col] == 'O') {
        board[biz.row][biz.col] = '.';
        biz.row = newRow;
        return true;
    }
    //벽이나 다른 구슬이면 그 위칸까지 구슬 이동
    else {
        board[newRow - 1][biz.col] = board[biz.row][biz.col];
        board[biz.row][biz.col] = '.';
        biz.row = newRow - 1;
        return false;
    }
}
bool situation::moveLeft(pos& biz) {
    //움직일 수 없으면 바로 terminate
    if (!movable(biz.row, biz.col - 1)) return false;
    
    int newCol;
    for (newCol = biz.col - 1; board[biz.row][newCol] == '.'; newCol--);
    
    //구멍이면 구슬 빼고 return true
    if (board[biz.row][newCol] == 'O') {
        board[biz.row][biz.col] = '.';
        biz.col = newCol;
        return true;
    }
    //벽이나 다른 구슬이면 그 오른쪽 칸까지 구슬 이동
    else {
        board[biz.row][newCol + 1] = board[biz.row][biz.col];
        board[biz.row][biz.col] = '.';
        biz.col = newCol + 1;
        return false;
    }
}
bool situation::moveRight(pos& biz) {
    //움직일 수 없으면 바로 terminate
    if (!movable(biz.row, biz.col + 1)) return false;
    
    int newCol;
    for (newCol = biz.col + 1; board[biz.row][newCol] == '.'; newCol++);
    
    //구멍이면 구슬 빼고 return true
    if (board[biz.row][newCol] == 'O') {
        board[biz.row][biz.col] = '.';
        biz.col = newCol;
        return true;
    }
    //벽이나 다른 구슬이면 그 왼족 칸까지 구슬 이동
    else {
        board[biz.row][newCol - 1] = board[biz.row][biz.col];
        board[biz.row][biz.col] = '.';
        biz.col = newCol - 1;
        return false;
    }
}

void situation::tiltUp() {
    bool redDone = false, blueDone = false;
    
    //위에 있는 거 먼저 옮김
    if (red.row <= blue.row) {
        redDone = moveUp(red);
        
        if(blueDone = moveUp(blue)) {
            for (int i = 0; i < N; i++) delete[] board[i];
            delete[] board;
            board = nullptr;
        }
    }
    else {
        if (blueDone = moveUp(blue)) {
            for (int i = 0; i < N; i++) delete[] board[i];
            delete[] board;
            board = nullptr;
        };
        if (board != nullptr) redDone = moveUp(red);
    }
    
    done = done || (redDone && !blueDone);
    depth++;
}
void situation::tiltDown() {
    bool redDone = false, blueDone = false;
    //아래에 있는 거 먼저 옮김
    if (blue.row <= red.row) {
        redDone = moveDown(red);
        
        if(blueDone = moveDown(blue)) {
            for (int i = 0; i < N; i++) delete[] board[i];
            delete[] board;
            board = nullptr;
        }
    }
    else {
        if (blueDone = moveDown(blue)) {
            for (int i = 0; i < N; i++) delete[] board[i];
            delete[] board;
            board = nullptr;
        };
        if (board != nullptr) redDone = moveDown(red);
    }
    done = done || (redDone && !blueDone);
    depth++;
}
void situation::tiltLeft() {
    bool redDone = false, blueDone = false;
    
    //왼쪽에 있는 거 먼저 옮김
    if (red.col <= blue.col) {
        redDone = moveLeft(red);
        
        if(blueDone = moveLeft(blue)) {
            for (int i = 0; i < N; i++) delete[] board[i];
            delete[] board;
            board = nullptr;
        }
    }
    else {
        if (blueDone = moveLeft(blue)) {
            for (int i = 0; i < N; i++) delete[] board[i];
            delete[] board;
            board = nullptr;
        };
        if (board != nullptr) redDone = moveLeft(red);
    }
    done = done || (redDone && !blueDone);
    depth++;
}
void situation::tiltRight() {
    bool redDone = false, blueDone = false;
    
    //오른쪽에 있는 거 먼저 옮김
    if (blue.col <= red.col) {
        redDone = moveRight(red);
        
        if(blueDone = moveRight(blue)) {
            for (int i = 0; i < N; i++) delete[] board[i];
            delete[] board;
            board = nullptr;
        }
    }
    else {
        if (blueDone = moveRight(blue)) {
            for (int i = 0; i < N; i++) delete[] board[i];
            delete[] board;
            board = nullptr;
        };
        if (board != nullptr) redDone = moveRight(red);
    }
    done = done || (redDone && !blueDone);
    depth++;
}
