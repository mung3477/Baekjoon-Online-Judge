#include <iostream>
using std::cin;
using std::cout;

int* rank;
int* root;
int* wishOf;
//bool* hasTeam;
int* hasTeam;

int getRoot(int i);
void Union(int a, int b);
void CycleTraverse(int a, int b, int start);

int main()
{
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    int T;
    cin >> T;
    
    for (T; T > 0; T--) {
        int N, answer = 0;
        cin >> N;
        
        rank = new int[N + 1]{};
        root = new int[N + 1]{};
        wishOf = new int[N + 1]{};
        //hasTeam = new bool[N]{};
        hasTeam = new int[N + 1]{};
        
        for (int i = 1; i <= N; i++) {
            rank[i] = 1;
            root[i] = i;
            cin >> wishOf[i];
        }
        
        for (int i = 1; i <= N; i++) {
            //If this edge makes cycle
            if (getRoot(i) == getRoot(wishOf[i])) {
                //Mark as "team matched"
                CycleTraverse(i, wishOf[i], i);
            }
            else {
                Union(i, wishOf[i]);
            }
        }
        

        for (int i = 1; i <= N; i++) {
            if (!hasTeam[i]) answer++;
        }
        
        cout << answer << "\n";
        
        delete[] rank, root, hasTeam;
    }
    return 0;
}

int getRoot(int i) {
    if (i == root[i]) return i;
    else return root[i] = getRoot(root[i]);
}

void Union(int a, int b) {
    a = getRoot(a);
    b = getRoot(b);
    
    if (a != b) {
        if (rank[a] < rank[b]) root[a] = b;
        else {
            root[b] = a;
            if (rank[a] == rank[b]) rank[a]++;
        }
    }
}

void CycleTraverse(int a, int b, int start) {
    hasTeam[a] = hasTeam[b] = b;
    if (b != start) CycleTraverse(b, wishOf[b], start);
}
