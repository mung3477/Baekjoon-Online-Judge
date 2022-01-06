#include <iostream>
using std::cin;
using std::cout;

/** 
 * @var index - movie's index on leaf node of segment tree
 * @var watched - how many movie did he watched
*/
int *segTree, *index, N, M, watched;

int createSegTree(int cur, int left, int right);
int watch(int cur, int movieIndex, int left, int right);
void pop(int cur, int movieIndex, int left, int right);
void push(int cur, int where, int movie, int left, int right);

int main(void) {
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int T, movie;
    cin >> T;
    for (int i = 1; i <= T; i++) {
        cin >> N >> M;

        watched = 0;
        segTree = new int[4 * (M + N) + 1]{};
        index = new int[N + 1]{};

        createSegTree(1, 1, M + N);

        for (int i = 1; i <= M; i++) {
            cin >> movie;
            int movieIndex = index[movie];

            cout << watch(1, movieIndex, 1, M + N) << " ";
            pop(1, movieIndex, 1, M + N);
            push(1, M - watched, movie, 1, M + N);
            watched++;
        }

        cout << "\n";
        delete[] segTree, index;
    }

    return 0;
}

//node: 아래 서브 트리 영화 개수
int createSegTree(int cur, int left, int right) {
    //left번 영화가 담긴 leaf node
    if (left == right) {
        //original 칸
        if (M < left && left <= M + N) {
            segTree[cur] = 1;
            index[left - M] = left;
            return 1;
        }
        //빈 칸
        else return 0;
    }

    int mid = (left + right) / 2;
    
    return segTree[cur] = createSegTree(cur * 2, left, mid) + createSegTree(cur * 2 + 1, mid + 1, right);
}

/** 
 * segTree[where]에 있는 영화를 찾으러가면서 몇 개의 영화가 앞에 있는지 확인.
 * @param movieIndex - 찾고자하는 영화의 segTree leaf node 상에서의 위치
 * @param left - 현재 노드가 대표하는 리프 노드의 범위 시작값
 * @param right - 현재 노드가 대표하는 리프 노드의 범위 종료값
*/
int watch(int cur, int movieIndex, int left, int right) {
    int retVal;

    // target is smaller than boundary => 현재 노드 아래의 영화들이 target 영화 위에 쌓여있음. 
    if (right < movieIndex) retVal = segTree[cur];
    //target is bigger than boundary => 현재 노드 아래의 영화들이 target 영화보다 아래에 있음
    else if (movieIndex < left) retVal = 0;
    //target
    else if (left == right) retVal = 0;
    //target is in boundary
    else {
        int mid = (left + right) / 2;
        retVal = watch(cur * 2, movieIndex, left, mid) + watch(cur * 2 + 1, movieIndex, mid + 1, right);
    }
    
    return retVal;
}

//update : -1
void pop(int cur, int movieIndex, int left, int right) {
    if (left <= movieIndex && movieIndex <= right) {
        segTree[cur] -= 1;

        if (left == right) return;

        int mid = (left + right) / 2;
        pop(cur * 2, movieIndex, left, mid);
        pop(cur * 2 + 1, movieIndex, mid + 1, right);
        
    }
}
//update : +1
void push(int cur, int where, int movie, int left, int right) {
    if (left <= where && where <= right) {
        segTree[cur] += 1;

        if (left == right) {
            index[movie] = left;
            return;
        }

        int mid = (left + right) / 2;
        push(cur * 2, where, movie, left, mid);
        push(cur * 2 + 1, where, movie, mid + 1, right);
    }
}
