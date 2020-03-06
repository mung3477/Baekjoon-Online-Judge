#include <cstdio>
#include <queue>
using namespace std;

////////////////////////////////////////////////////

class point{
    public:
        point();
        point(int a, int b, int c);
        int x;
        int y;
        int cost;      
};

class cmp{
    public:
    bool operator()(point a, point b){
        return a.cost > b.cost;
    }
};

priority_queue< point, vector<point>, cmp > PQueue;
//////////////////////////////////////////////////

point::point(){
    x = 0;
    y = 0;
    cost = 0;
}

point::point(int a, int b, int c){
    x = a;
    y = b;
    cost = c;
}

/////////////////////////////////////////////////

int maze[101][101];
int visited[101][101];

int main(void)
{
    int N, M;
    scanf("%d %d", &M, &N);
    getchar();

    for(int i = 1; i <= N; i++){
        for(int j = 1; j <= M; j++){
            maze[i][j] = getchar() - '0';
        }
        getchar();
    }
    
    if(N == 1 && M == 1){
        printf("0");
        return 0;
    }

    PQueue.push(point(1, 1, 0));
    visited[1][1] = 1;

    int move_x[4] = {-1, +1, 0 , 0};
    int move_y[4] = {0, 0, -1, +1};

    while(PQueue.size()){
        point cur = PQueue.top();
        PQueue.pop();
        for(int i = 0; i < 4; i++){
            int nx = cur.x + move_x[i];
            int ny = cur.y + move_y[i];
            
            if(nx == N && ny == M){
                printf("%d", cur.cost);
                return 0;
            }

            if(nx < 1 || ny < 1 || nx > N || ny > M ||visited[nx][ny]) continue;

            visited[nx][ny] = 1;
            PQueue.push(point(nx, ny, cur.cost + maze[nx][ny]));
        }
    }

    return 0;
}