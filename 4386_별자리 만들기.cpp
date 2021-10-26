#include <iostream>
#include <queue>
#include <vector>
#include <cmath>
using std::cin;
using std::cout;
using std::priority_queue;
using std::vector;
using std::pow;
using std::sqrt;

struct star {
    double x;
    double y;
    
    star(): x(0), y(0){};
    star(double x, double y): x(x), y(y) {};
};

struct edge {
    int A;
    int B;
    double cost;
    
    edge(): A(0), B(0), cost(0){};
    edge(int A, int B, double cost): A(A), B(B), cost(cost){};
};

struct compEdge {
    bool operator()(const edge& E1, const edge& E2) {
        return E1.cost > E2.cost;
    }  
};

int* rank;
int* root;
vector<star> stars;
priority_queue<edge, vector<edge>, compEdge> edgePQ;

int getRoot(int A);
void Union(int A, int B);
double distanceBtw(int i, int j);

int main()
{
    int N;
    cin >> N;
    
    rank = new int[N]{};
    root = new int[N]{};
    
    for (int i = 0; i < N; i++) {
       rank[i] = 1;
       root[i] = i;
       
       double x, y;
       cin >> x >> y;
       stars.emplace_back(x, y);
    }
    
    //put all edges in PQ
    for (int i = 0; i < N - 1; i++) {
        for (int j = i + 1; j < N; j++) {
            edgePQ.emplace(i, j, distanceBtw(i, j));
        }
    }
    
    //kruskal
    int used = 0;
    double MSTCost = 0;
    while (!edgePQ.empty() && used < N - 1) {
        edge cur = edgePQ.top();
        edgePQ.pop();
        
        if (getRoot(cur.A) != getRoot(cur.B)) {
            Union(cur.A, cur.B);
            used++;
            MSTCost += cur.cost;
        }
    }
    
    cout << std::fixed;
    cout.precision(2);
    cout << MSTCost;
    
    return 0;
}

int getRoot(int A) {
    if (root[A] == A) return A;
    else return root[A] = getRoot(root[A]);
}

void Union(int A, int B) {
    A = getRoot(A); 
    B = getRoot(B);
    
    if (A == B) return;
    else if (rank[A] < rank[B]) {
        root[A] = B;
    }
    else {
        root[B] = A;
        if (rank[A] == rank[B]) rank[A]++;
    }
}

double distanceBtw(int i, int j) {
    return sqrt(pow((stars.at(i).x - stars.at(j).x), 2) + pow((stars.at(i).y - stars.at(j).y), 2));
}
