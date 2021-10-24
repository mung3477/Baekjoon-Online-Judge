#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cmath>
#include <utility>
using std::cin;
using std::cout;
using std::vector;
using std::priority_queue;
using std::sort;
using std::abs;
using std::pair;
using std::make_pair;

struct planet {
    int x;
    int y;
    int z;
    int origIndex;
    
    planet(): x(0), y(0), z(0), origIndex(0){};
    planet(int x, int y, int z, int i): x(x), y(y), z(z), origIndex(i){};
};
struct planetEdge {
    int indexA;
    int indexB;
    int dist;
    
    planetEdge(): indexA(-1), indexB(-1), dist(-1) {};
    planetEdge(int indexA, int indexB, int dist): indexA(indexA), indexB(indexB), dist(dist) {};
};

//x, y, z 오름차순 정렬
struct compPlanet {
    char criteria;
    compPlanet(const char& compParam='x'): criteria(compParam) {};
    
    bool operator()(planet& A, planet& B) {
        if (criteria == 'x') return A.x < B.x;
        else if (criteria == 'y') return A.y < B.y;
        else return A.z < B.z;
    }
};

//dist 오름차순 정렬
struct compDist {
    bool operator()(planetEdge& E1, planetEdge& E2) {
        return E1.dist > E2.dist;
    }
};

vector<planet> original;
vector<planet> xSorted;
vector<planet> ySorted;
vector<planet> zSorted;
priority_queue<planetEdge, vector<planetEdge>, compDist> distPQ;  
int* rank;
int* root;
int N;

int getRoot(int a);
void Union(int a, int b);

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    int used = 0;
    long long answer = 0;

    cin >> N;
    rank = new int[N];
    root = new int[N];

    for (int i = 0; i <= N - 1; i++) {
        root[i] = i;
        rank[i] = 1;
        
        int x, y, z;
        cin >> x >> y >> z;
        original.emplace_back(x, y, z, i);
    }
    zSorted = ySorted = xSorted = original;

    sort(xSorted.begin(), xSorted.end(), compPlanet('x'));
    sort(ySorted.begin(), ySorted.end(), compPlanet('y'));
    sort(zSorted.begin(), zSorted.end(), compPlanet('z'));
    
    //fill the PQ
    for (int i = 0; i < N - 1; i++) {
        distPQ.emplace(xSorted.at(i).origIndex, xSorted.at(i + 1).origIndex, abs(xSorted.at(i).x - xSorted.at(i + 1).x));
        distPQ.emplace(ySorted.at(i).origIndex, ySorted.at(i + 1).origIndex, abs(ySorted.at(i).y - ySorted.at(i + 1).y));
        distPQ.emplace(zSorted.at(i).origIndex, zSorted.at(i + 1).origIndex, abs(zSorted.at(i).z - zSorted.at(i + 1).z));
    }
    
    //kruskal's algorithm
    while (!distPQ.empty() && used < N - 1) {
        planetEdge cur = distPQ.top();
        planet A = original.at(cur.indexA);
        planet B = original.at(cur.indexB);
        distPQ.pop();
        
        //if this edge doesn't make a cycle, use that edge
        if (getRoot(A.origIndex) != getRoot(B.origIndex)) {
            Union(A.origIndex, B.origIndex);
            used++;
            answer += cur.dist;
        }
    }
    
    cout << answer;
    
    return 0;
}

int getRoot(int a) {
    if (root[a] == a) return a;
    else return root[a] = getRoot(root[a]);
}

void Union(int a, int b) {
    a = getRoot(a); 
    b = getRoot(b);
    
    if (a != b) {
        if (rank[a] < rank[b]) 
            root[a] = b;
        else {
            root[b] = a;
            if (rank[a] == rank[b]) rank[a]++;
        }
    }
}


