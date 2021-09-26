#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using std::cin;
using std::cout;
using std::vector;
using std::queue;
using std::remove_if;

struct point {
    int row;
    int col;
    point(): row(0), col(0) {};
    point(int row, int col): row(row), col(col) {};
};

struct Comp {
    bool operator()(point& a, point& b) {
        return a.row > b.row || (a.row == b.row && a.col > b.col);
    }
} comp;

struct update {
    point target;
    int diff;
    update(): target(), diff(0) {};
    update(int row, int col, int diff): target(row, col), diff(diff) {};
};

int R, C, T, upCleaner, downCleaner;
int** room;
vector<point> dusts;
queue<update> updateInfos;

//fill updateInfos(diffuse to surroundings) and subtract amount of diffused dust from current amount.
void diffuseToSurroundings(point& dust) {
    int row = dust.row, col = dust.col, diffused = 0, amount = (int)((double)room[row][col] / 5);
    
    //up
    if (1 < row && room[row - 1][col] != -1) {
        updateInfos.emplace(row - 1, col, amount);
        diffused += amount;
    }
    //down
    if (row < R && room[row + 1][col] != -1) {
        updateInfos.emplace(row + 1, col, amount);
        diffused += amount;
    }
    //left
    if (1 < col && room[row][col - 1] != -1) {
        updateInfos.emplace(row, col - 1, amount);
        diffused += amount;
    }
    //right
    if (col < C && room[row][col + 1] != -1) {
        updateInfos.emplace(row, col + 1, amount);
        diffused += amount;
    }
    
    room[row][col] -= diffused;
}

//update all diffusions
void updateDustMap() {
    while (!updateInfos.empty()) {
        update cur = updateInfos.front();
        updateInfos.pop();
        
        if (!room[cur.target.row][cur.target.col]) {
            dusts.emplace_back(cur.target.row, cur.target.col);
        }
        room[cur.target.row][cur.target.col] += cur.diff;
    }
}

void diffuseDust() {
    for (auto dust : dusts) {
        diffuseToSurroundings(dust);
    }
    updateDustMap();
}

bool inFrontOfAirConditioner(point& dust) {
    return (dust.row == upCleaner || dust.row == downCleaner) && dust.col == 2;
}

//move dusts in reverse order of air flow direction
void airConditionerWorks() {
    //upper air
    //downward flow
    room[upCleaner - 1][1] = 0;
    for (int i = upCleaner - 2; 1 <= i; i--) {
        room[i + 1][1] = room[i][1];
    }
    //left flow
    for (int j = 2; j <= C; j++) {
        room[1][j - 1] = room[1][j];
    }
    //upward flow
    for (int i = 2; i <= upCleaner; i++) {
        room[i - 1][C] = room[i][C];
    }
    //right flow
    for (int j = C - 1; 2 <= j; j--) {
        room[upCleaner][j + 1] = room[upCleaner][j];
    }
    room[upCleaner][2] = 0;
    
    //lower air 
    //upward flow
    room[downCleaner + 1][1] = 0;
    for (int i = downCleaner + 2; i <= R; i++) {
        room[i - 1][1] = room[i][1];
    }
    //left flow
    for (int j = 2; j <= C; j++) {
        room[R][j - 1] = room[R][j];
    }
    //downward flow
    for (int i = R - 1; downCleaner <= i; i--) {
        room[i + 1][C] = room[i][C];
    }
    //right flow
    for (int j = C - 1; 2 <= j; j--) {
        room[downCleaner][j + 1] = room[downCleaner][j];
    }
    room[downCleaner][2] = 0;
}

void showMap() {
    for (int i = 1; i <= R; i++) {
        for (int j = 1; j <= C; j++) {
            cout << room[i][j] << " ";
        }
        cout << "\n";
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    int totalDust = 0;
    
    cin >> R >> C >> T;
    
    //construct
    room = new int*[R + 1];
    for (int i = 1; i <= R; i++) {
        room[i] = new int[C + 1]{};
    }
    
    //fill the room
    for (int i = 1; i <= R; i++) {
        for (int j = 1; j <= C; j++) {
            cin >> room[i][j];
            if (0 < room[i][j]) dusts.emplace_back(i, j);
        }
    }
    
    //find the air conditioner
    for (int i = 1; i <= R; i++) {
        if (room[i][1] == -1) {
            upCleaner = i;
            downCleaner = i + 1;
            break;
        }
    }
    
    //time goes on...
    for (int t = 1; t <= T; t++) {
        diffuseDust();
        airConditionerWorks();
        
        dusts.clear();
        for (int i = 1; i <= R; i++) {
            for (int j = 1; j <= C; j++) {
                if (room[i][j] > 0) dusts.emplace_back(i, j);
            }
        }
    }
    
    for (int i = 1; i <= R; i++) {
        for (int j = 1; j <= C; j++) {
            if (0 < room[i][j]) totalDust += room[i][j];
        }
    }
    
    cout << totalDust;
    
    return 0;
}
