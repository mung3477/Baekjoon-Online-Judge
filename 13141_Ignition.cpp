#include <iostream>
#include <vector>
#include <utility>
#include <math.h>
using std::cin;
using std::cout;
using std::vector;
using std::abs;

struct edge {
    int u;
    int v;
    int length;

    edge(int u, int v, int length): u(u), v(v), length(length) {};
};

int N, **distance, *igniteTime;
vector<edge> Edges;

template <typename T> 
T min(T a, T b) {
    if (a < b) return a;
    else return b;
}

template <typename T>
T max(T a, T b) {
    if (a > b) return a;
    else return b;
}

int main(void) {
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cout << std::fixed;
    cout.precision(1);
    

    int M, S, E, L;
    double ans = 20000001.0;
    cin >> N >> M;

    igniteTime = new int[N + 1]{};
    distance = new int*[N + 1]{};
    for (int i = 0; i <= N; i++) {
        distance[i] = new int[N + 1]{};
        for (int j = 0; j <= N; j++) distance[i][j] = (i == j) ? 0 : -1;
    }

    

    for (int i = 1; i <= M; i++) {
        cin >> S >> E >> L;
        Edges.emplace_back(S, E, L);
        distance[S][E] = distance[S][E] == -1 ? L : min<int>(distance[S][E], L);
        distance[E][S] = distance[E][S] == -1 ? L : min<int>(distance[E][S], L);
    }

    // Floyd-Warshall
    for (int k = 1; k <= N; k++) {
        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= N; j++) {
                if (distance[i][k] != -1 && distance[k][j] != -1) {
                    int newDist = distance[i][k] + distance[k][j];
                    distance[i][j] = distance[i][j] == -1 ? newDist : min<int>(distance[i][j], newDist);
                }
            }
        }
    }
    
    for (int s = 1; s <= N; s++) {
        for (int i = 1; i <= N; i++) igniteTime[i] = distance[s][i];
        
        double burnDownTime, totalBurnDownTime = 0.0;
        for (const edge& E : Edges) {
            int timeDiff = abs(igniteTime[E.u] - igniteTime[E.v]), edgeIgniteTime = min<int>(igniteTime[E.u], igniteTime[E.v]);
            if (E.length < timeDiff) burnDownTime = edgeIgniteTime + E.length;
            else burnDownTime = edgeIgniteTime + timeDiff + (E.length - timeDiff) / 2.0;

            totalBurnDownTime = max<double>(totalBurnDownTime, burnDownTime);
        }

        ans = min<double>(ans, totalBurnDownTime);
    }

    cout << ans;

    for (int i = 0; i <= N; i++) delete[] distance[i];
    delete[] igniteTime, distance;
    return 0;
}
