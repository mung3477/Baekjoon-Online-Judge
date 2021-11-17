#include <iostream>
#include <algorithm>
#include <queue>
#include <utility>
#include <set>
using std::cin;
using std::cout;
using std::fill;
using std::queue;
using std::pair;    //row, size
using std::make_pair;
using std::move;
using std::set;

pair<short, short> initPair;

struct shark {
    short row;
    short col;
    short speed;
    char direction;
    short size;
    
    shark(short row, short col, short speed, char direction, short size): row(row), col(col), speed(speed), direction(direction), size(size) {};
    
    void show() {
        cout << "==SHARK==\n" << "row: " << row <<"\ncol: " << col <<"\nsize: " << size <<"\n";
    }
};

short R, C, M, caughtSharkSize;
int total;
pair<short, short>* closest;
queue<shark> sharks;
set<int> caughtSharkSizes;
int** occupied;

void catchShark(int col);
void moveSharks();
void moveShark(shark* jaws);

void showClosest() {
    cout << "sharks left : " << sharks.size() << "\n";
    for (int i = 1; i <= C; i++) {
        cout << closest[i].first << " ";
    }    
    cout << "\n";
}

int main()
{
    cin >> R >> C >> M;
    
    initPair = make_pair(R + 1, 0);
    closest = new pair<short, short>[C + 1]{};
    fill(closest, &closest[C + 1], initPair);
    occupied = new int*[R + 1];
    for (int i = 1; i <= R; i++) {
        occupied[i] = new int[C + 1]{};       
    }
    
    //fill sharks information
    for (int i = 0; i < M; i++) {
        short row;
        short col;
        short speed;
        char direction;
        short size;
        
        cin >> row >> col >> speed >> direction >> size;
        sharks.emplace(row, col, speed, direction, size);
        
        if (closest[col].first > row) 
            closest[col] = make_pair(row, size);
    }
    
    //showClosest();
    
    for (int i = 1; i <= C; i++) {
        catchShark(i);
        fill(closest, &closest[C + 1], initPair);
        for (int i = 1; i <= R; i++) {
            for (int j = 1; j <= C; j++) {
                occupied[i][j] = 0;
            }
        }
        moveSharks();
        
        //showClosest();
    }

    cout << total;
    return 0;
}

//catch closest shark
void catchShark(int col) {
    caughtSharkSizes.insert(closest[col].second);
    total += closest[col].second;
}

//move all sharks
void moveSharks() {
    queue<shark> movedSharks;
    while (!sharks.empty()) {
        shark* cur = &sharks.front();
        
        //skip moving caught Shark
        if (caughtSharkSizes.find(cur->size) == caughtSharkSizes.end()) {
            moveShark(cur);
                
            int row = cur->row, col = cur->col;
            //cur->show();
            //there's already anther shark
            if (occupied[row][col]) {
                //current shark is bigger
                if (occupied[row][col] < cur->size) {
                    caughtSharkSizes.insert(occupied[row][col]);
                    movedSharks.push(move(*cur));
                    occupied[row][col] = cur->size;
                    
                    //update closest array
                    if (closest[cur->col].first >= cur->row) 
                        closest[cur->col] = make_pair(cur->row, cur->size);
                }
                //current shark is smaller
                else {
                    caughtSharkSizes.insert(cur->size);
                }
            }
            //vacant
            else {
                movedSharks.push(move(*cur));
                occupied[cur->row][cur->col] = cur->size;
                
                //update closest array
                if (closest[cur->col].first >= cur->row) 
                    closest[cur->col] = make_pair(cur->row, cur->size);
            }
        }
        
        sharks.pop();
    }
    movedSharks.swap(sharks);
}

void moveShark(shark* cur) {
    int movedDistance;
    
    //up down
    if (cur->direction <= '2') {
        movedDistance = cur->speed % (2 * R - 2);    
        
        for (int i = 1; i <= movedDistance; i++) {
            //reverse direction
            if ((cur->row == 1) && (cur->direction == '1')) {
                cur->direction = '2';
            }
            else if ((cur->row == R) && (cur->direction == '2')) {
                cur->direction = '1';
            }
            
            //up
            if (cur->direction == '1') {
                (cur->row)--;
            }
            //down
            else {
                (cur->row)++;
            }
        }
    }
    //left right
    else {
        movedDistance = cur->speed  % (2 * C - 2);
        for (int i = 1; i <= movedDistance; i++) {
            //reverse direction
            if ((cur->col == 1) && (cur->direction == '4')) {
                cur->direction = '3';
            }
            else if ((cur->col == C) && (cur->direction == '3')) {
                cur->direction = '4';
            }
            
            //right
            if (cur->direction == '3') {
                (cur->col)++;
            }
            //left
            else {
                (cur->col)--;
            }
        }
    }
}
