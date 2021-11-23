#include <iostream>
using std::cin;
using std::cout;

int* root;
int* rank;

int getRoot(int A) {
    if (root[A] == A) return A;
    else return root[A] = getRoot(root[A]);
}

void Union(int A, int B) {
    if (A != B) {
        if (rank[A] < rank[B]) {
            root[A] = B;
        }
        else {
            root[B] = A;
            if (rank[A] == rank[B]) rank[A]++;
        }
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    int N, M;
    cin >> N >> M;
    
    root = new int[N];
    rank = new int[N];
    
    for (int i = 0; i < N; i++) {
        root[i] = i;
        rank[i] = 1;
    }
    
    int end = 0;
    
    for (int i = 1; i <= M; i++) {
        int a, b;
        cin >> a >> b;
        
        a = getRoot(a);
        b = getRoot(b);
        if (a == b && !end) end = i; 
        else Union(a, b);
    }
    
    cout << end;

    return 0;
}
