#include <iostream>
using std::cin;
using std::cout;

int N, largest;

struct square {
    int number;
    bool merged;
    
    square(): number(0), merged(false) {};
    square(int number, bool merged): number(number), merged(merged) {};
    
    void clear() {
        this->number = 0;
        this->merged = false;
    }
};

void move(square** board, int fromRow, int fromCol, int toRow, int toCol);
void merge(square** board, int fromRow, int fromCol, int toRow, int toCol);

void move_up(square** board, int row, int col);
void move_down(square** board, int row, int col);
void move_left(square** board, int row, int col);
void move_right(square** board, int row, int col);

void DFS_UP(square** board, int depth);
void DFS_DOWN(square** board, int depth);
void DFS_LEFT(square** board, int depth);
void DFS_RIGHT(square** board, int depth);

void DFS_call(square** board, int depth);

void showBoard(square** board) {
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            cout << board[i][j].number << "\t";
        }
        cout << "\n";
    }
    cout << "\n";
}

int main()
{
    square** board;
    
    cin >> N;
    board =  new square*[N + 1]{};
    for (int i = 1; i <= N; i++) {
        board[i] = new square[N + 1]{};
        for (int j = 1; j <= N; j++) {
            cin >> board[i][j].number;
        }
    }
    
    DFS_call(board, 1);
    
    cout << largest;
    
    return 0;
}

void move(square** board, int fromRow, int fromCol, int toRow, int toCol) {
    board[toRow][toCol] = board[fromRow][fromCol];
    board[fromRow][fromCol].clear();
}

void merge(square** board, int fromRow, int fromCol, int toRow, int toCol) {
    board[toRow][toCol].number *= 2;
    board[toRow][toCol].merged = true;
    board[fromRow][fromCol].clear();
}

void move_up(square** board, int row, int col) {
    if (row == 1) return;
    
    //find the most closest upper square
    int dest;
    for (dest = row - 1; 1 <= dest && board[dest][col].number == 0; dest--);
    
    //if there's no upper squares, move current square to the top
    if (dest == 0) {
        move(board, row, col, 1, col);
    }
    //if mergable, merge them
    else if ((board[dest][col].number == board[row][col].number) && !board[dest][col].merged) {
        merge(board, row, col, dest, col);
    }
    //if not mergable, move current square to right below of destination
    else if (dest + 1 != row) {
        move(board, row, col, dest + 1, col);
    }
}

void move_down(square** board, int row, int col) {
    //function works with rows lower than N
    if (row == N) return;
    
    //find the most closest lower square
    int dest;
    for (dest = row + 1; dest <= N && board[dest][col].number == 0; dest++);
    
    //if there's no lower squares, move current square to the bottom
    if (dest == N + 1) {
        move(board, row, col, N, col);
    }
    //if mergable, merge them
    else if ((board[dest][col].number == board[row][col].number) && !board[dest][col].merged) {
        merge(board, row, col, dest, col);
    }
    //if not mergable, move current square to right above of destination
    else if (dest - 1 != row) {
        move(board, row, col, dest - 1, col);
    }
}

void move_left(square** board, int row, int col) {
    if (col == 1) return;
    
    //find the most closest leftward square
    int dest;
    for (dest = col - 1; 1 <= dest && board[row][dest].number == 0; dest--);
    
    //if there's no leftward squares, move current square to the leftmost position
    if (dest == 0) {
        move(board, row, col, row, 1);
    }
    //if mergable, merge them
    else if ((board[row][dest].number == board[row][col].number) && !board[row][dest].merged) {
        merge(board, row, col, row, dest);
    }
    //if not mergable, move current square to just right of destination
    else if (dest + 1 != col) {
        move(board, row, col, row, dest + 1);
    }
}

void move_right(square** board, int row, int col) {
    //function works with col lower than N
    if (col == N) return;
    
    //find the most closest rightward square
    int dest;
    for (dest = col + 1; dest <= N && board[row][dest].number == 0; dest++);
    
    //if there's no rightward squares, move current square to the rightmost position
    if (dest == N + 1) {
        move(board, row, col, row, N);
    }
    //if mergable, merge them
    else if ((board[row][dest].number == board[row][col].number) && !board[row][dest].merged) {
        merge(board, row, col, row, dest);
    }
    //if not mergable, move current square to just left of destination
    else if (dest - 1 != col) {
        move(board, row, col, row, dest - 1);
    }
}

void DFS_UP(square** board, int depth) {
    //Copy original board
    square** MovedBoard = new square*[N + 1]{};
    for (int i = 1; i <= N; i++) {
        MovedBoard[i] = new square[N + 1]{};
        for (int j = 1; j <= N; j++) {
            MovedBoard[i][j] = board[i][j];
            MovedBoard[i][j].merged = false;
        }
    }
    
    //move upper squares first 
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            if (MovedBoard[i][j].number) move_up(MovedBoard, i, j);
        }
    }
    
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            if (largest < MovedBoard[i][j].number) 
                largest = MovedBoard[i][j].number;
        }
    }
    
    DFS_call(MovedBoard, depth + 1);
}

void DFS_DOWN(square** board, int depth) {
    //Copy original board
    square** MovedBoard = new square*[N + 1]{};
    for (int i = 1; i <= N; i++) {
        MovedBoard[i] = new square[N + 1]{};
        for (int j = 1; j <= N; j++) {
            MovedBoard[i][j] = board[i][j];
            MovedBoard[i][j].merged = false;
        }
    }
    
    //move lower squares first 
    for (int i = N; 1 <= i; i--) {
        for (int j = 1; j <= N; j++) {
            if (MovedBoard[i][j].number) move_down(MovedBoard, i, j);
        }
    }
    
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            if (largest < MovedBoard[i][j].number) 
                largest = MovedBoard[i][j].number;
        }
    }
    
    DFS_call(MovedBoard, depth + 1);
}

void DFS_LEFT(square** board, int depth) {
    //Copy original board
    square** MovedBoard = new square*[N + 1]{};
    for (int i = 1; i <= N; i++) {
        MovedBoard[i] = new square[N + 1]{};
        for (int j = 1; j <= N; j++) {
            MovedBoard[i][j] = board[i][j];
            MovedBoard[i][j].merged = false;
        }
    }
    
    //move leftmost squares first 
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            if (MovedBoard[i][j].number) move_left(MovedBoard, i, j);
        }
    }
    
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            if (largest < MovedBoard[i][j].number) 
                largest = MovedBoard[i][j].number;
        }
    }
    
    DFS_call(MovedBoard, depth + 1);
}

void DFS_RIGHT(square** board, int depth) {
    //Copy original board
    square** MovedBoard = new square*[N + 1]{};
    for (int i = 1; i <= N; i++) {
        MovedBoard[i] = new square[N + 1]{};
        for (int j = 1; j <= N; j++) {
            MovedBoard[i][j] = board[i][j];
            MovedBoard[i][j].merged = false;
        }
    }
    
    //move rightmost squares first 
    for (int i = 1; i <= N; i++) {
        for (int j = N; 1 <= j; j--) {
            if (MovedBoard[i][j].number) move_right(MovedBoard, i, j);
        }
    }
    
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            if (largest < MovedBoard[i][j].number) 
                largest = MovedBoard[i][j].number;
        }
    }
    
    DFS_call(MovedBoard, depth + 1);
}

void DFS_call(square** board, int depth) {
    //termianate
    if (depth > 5) {
        for (int i = 1; i <= N; i++) delete[] board[i];
        delete[] board;
        return;
    }
    
    DFS_UP(board, depth);
    DFS_DOWN(board, depth);
    DFS_LEFT(board, depth);
    DFS_RIGHT(board, depth);
}
