#include <iostream>
#define init 512
using std::cin;
using std::cout;

int original[10];
int minToggled = 101;

void copyBulbs(int* dest, int* src) {
    for (int i = 0; i <= 9; i++) dest[i] = src[i];
}

bool turnedOn(int row, int col, int* bulbs) {
    return (bulbs[row] & (init >> col)) != 0;
}

bool turnedOffAll(int* bulbs) {
    for (int i = 0; i <= 9; i++) if (bulbs[i] != 0) return false;
    return true;
}

void toggle(int row, int col, int* bulbs) {
    //upper
    if (0 < row) { bulbs[row - 1] = bulbs[row - 1] ^ (init >> col); }
    //left
    if (0 < col) { bulbs[row] = bulbs[row] ^ (init >> col - 1); }    
    //center
    bulbs[row] = bulbs[row] ^ (init >> col);
    //right
    if (col < 9) { bulbs[row] = bulbs[row] ^ (init >> col + 1); }
    //downward
    if (row < 9) { bulbs[row + 1] = bulbs[row + 1] ^ (init >> col); }
}

void tryTurnOffAll(int row, int col, int toggled, int* bulbs) {
    if (row == 10) { 
        if (turnedOffAll(bulbs) && minToggled > toggled) minToggled = toggled; 
    }
    else {
        //위 전구가 켜져있으면 이번 전구를 눌러서 위 전구를 끔
        if (turnedOn(row - 1, col, bulbs)) {
            toggle(row, col, bulbs);
            toggled++;
        }
        col == 9 ? tryTurnOffAll(row + 1, 0, toggled, bulbs) : tryTurnOffAll(row, col + 1, toggled, bulbs);
    }
}

void toggleFirstLine(int col, int toggled, int* bulbs) {
    if (col == 10) { 
        int newBulbs[10];
        copyBulbs(newBulbs, bulbs);
        tryTurnOffAll(1, 0, toggled, newBulbs); 
    }
    else {
        //안 누르고 한 번
        toggleFirstLine(col + 1, toggled, bulbs);
        
        //누르고 한 번
        toggle(0, col, bulbs);
        toggleFirstLine(col + 1, toggled + 1, bulbs);
        toggle(0, col, bulbs);
    }
}

int main()
{
    char given;
    for (int i = 0; i <= 9; i++) {
        int bulbLine = 0;
        for (int j = 0; j <= 9; j++) {
            cin >> given;
            if (given == 'O') {
                bulbLine = bulbLine | (init >> j);
            }
        }
        original[i] = bulbLine;
    }
    
    toggleFirstLine(0, 0, original);
    
    cout << (minToggled == 101 ? -1 : minToggled);
    
    return 0;
}
