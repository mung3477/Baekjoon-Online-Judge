#include <iostream>
#include <string>
#include <queue>
#include <list>
#include <utility>
using std::cin;
using std::cout;
using std::string;
using std::queue;
using std::list;
using std::pair;
using std::make_pair;

int h, w;
bool* key; //a ~ z
list<pair<int, int>>* doors;    //A ~ Z
char** map; //[row][col], 0 ~ h + 1, 0 ~ w + 1
bool** visited;


bool able(int i, int j);
void expand(int i, int j, queue<pair<int, int>>& frontier);

int main()
{
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    int T;
    cin >> T;
    
    for (T; T > 0; T--) {
        key = new bool['z' - 'a' + 1]{};
        doors = new list<pair<int, int>>['Z' - 'A' + 1]{};
        
        string keys;
        int documents = 0, collected = 0;
        cin >> h >> w;
        
        map = new char*[h + 2];
        visited = new bool*[h + 2];
        for (int i = 0; i <= h + 1; i++) {
            map[i] = new char[w + 2]{};
            visited[i] = new bool[w + 2]{};
            
            int j = 0;
            //왼쪽 테두리
            map[i][j] = '.';
            
            for (j = 1; j <= w; j++) {
                //위 아래 테두리
                if (i == 0 || i == h + 1) {
                    map[i][j] = '.';
                }
                //원본 map
                else {
                    cin >> map[i][j];
                    if (map[i][j] == '$') documents++;
                    else if ('A' <= map[i][j] && map[i][j] <= 'Z') doors[map[i][j] - 'A'].emplace_back(i, j);
                }
            }
            
            //오른쪽 테두리
            map[i][j] = '.';
        }
        
        
        cin >> keys;
        //갖고 시작하는 열쇠
        if (keys != "0") {
            for (auto it = keys.begin(); it != keys.end(); it++) {
                int curKeyIndex = *it - 'a';
                key[curKeyIndex] = true;
                //문 다 열기
                for (auto jt = doors[curKeyIndex].begin(); jt != doors[curKeyIndex].end(); jt++) {
                    map[jt->first][jt->second] = '.';
                }
            }
        }
        
        //BFS
        queue<pair<int, int>> frontier;
        frontier.push(make_pair(0, 0));
        visited[0][0] = true;
        
        while (!frontier.empty() && documents != collected) {
            pair<int, int> cur = frontier.front();
            frontier.pop();
            
            char curPlace = map[cur.first][cur.second];
            
            //do appropriate job at current place
            //서류인 경우
            if (curPlace == '$') {
                collected++;
                map[cur.first][cur.second] = '.';   //서류 중복 획득 방지
            }
            //열쇠인 경우
            else if ('a' <= curPlace && curPlace <= 'z') {
                //없던 열쇠라면 문 열기
                if (!key[curPlace - 'a']) {
                    for (auto it = doors[curPlace - 'a'].begin(); it != doors[curPlace - 'a'].end(); it++) {
                        map[it->first][it->second] = '.';
                    }
                
                    //현 위치에서 재시작
                    while (!frontier.empty()) frontier.pop();
                    for (int i = 0; i <= h + 1; i++)
                        delete[] visited[i];
                    delete[] visited;
                    
                    visited = new bool*[h + 2];
                    for (int i = 0; i <= h + 1; i++)
                        visited[i] = new bool[w + 2]{};
                    
                    visited[cur.first][cur.second] = true;
                }
                
                map[cur.first][cur.second] = '.';   //열쇠 중복 획득 방지
            }
            
            expand(cur.first, cur.second, frontier);
        }
        
        cout << collected << "\n";
        
        for (int i = 0; i < h; i++)
            delete[] map[i], visited[i];
        delete[] map, key, doors, visited;
    }
   
    return 0;
}

//not visited yet, not a wall, not a door
bool able(int i, int j) {
    return !visited[i][j] && (map[i][j] != '*') && !('A' <= map[i][j] && map[i][j] <= 'Z');
}

void expand(int i, int j, queue<pair<int, int>>& frontier) {
    
    //up
    if (0 < i && able(i - 1, j)) {
        frontier.emplace(i - 1, j);
        visited[i - 1][j] = true;
    } 
    //down
    if (i < h + 1 && able(i + 1, j)) {
        frontier.emplace(i + 1, j);
        visited[i + 1][j] = true;
    }
    //left
    if (0 < j && able(i, j - 1)) {
        frontier.emplace(i, j - 1);
        visited[i][j - 1] = true;
    }
    //right
    if (j < w + 1 && able(i, j + 1)) {
        frontier.emplace(i, j + 1);
        visited[i][j + 1] = true;
    }
}
