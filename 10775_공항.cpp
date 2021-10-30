#include <iostream>
using std::cin;
using std::cout;

int* root;  //i보다 작거나 같은, 아직 사용되지 않은 가장 큰 수

int getRoot(int r) {
    if (root[r] == r) return r;
    else return root[r] = getRoot(root[r]);
}

void Union(int a, int b) {
    //이 문제의 경우 둘 다 root가 입력됨
    //둘 중 더 작은 수가 root가 됨
    if (a < b) root[b] = a;
    else root[a] = b;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    int G, P, docked = 0;
    cin >> G >> P;
    
    root = new int[G + 1]{};
    for (int i = 0; i <= G; i++) root[i] = i;
    
    for (P; P > 0; P--) {
        int gi;
        cin >> gi;
        
        //root가 0인 경우 도킹이 불가능하다는 의미
        if (!getRoot(gi)) {
            break;
        }
        else {
            Union(getRoot(gi), getRoot(getRoot(gi) - 1));
            docked++;
        }
    }
    
    cout << docked;
    
    return 0;
}
