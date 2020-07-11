#include <cstdio>
#include <algorithm>
using namespace std;

#define MOD 1000000000

struct Edge{
    int u, v, w;
    Edge() : Edge(-1, -1, 0){};
    Edge(int a, int b, int c): u(a), v(b), w(c){};
    bool operator <(const Edge& o) { return w > o.w; }
};



//유니온 파인드 배열. 1부터 사용
int uf[100001];

//루트 찾기
int find(int a){
    if(uf[a] < 0) return a;
    uf[a] = find(uf[a]);
    return uf[a];
}

//a 쪽으로 합치기
bool merge(int a, int b){
    a = find(a);
    b = find(b);
    if(a == b) return false;
    uf[a] += uf[b];
    uf[b] = a;
    return true;
}


int main(void)
{
    int N, M;
    scanf("%d %d", &N, &M);

    Edge edges[100000];
    int index = 0;
    long long sum = 0;
    for(int i = 1; i <= M; i++){
        int v1, v2, cost;
        scanf(" %d %d %d", &v1, &v2, &cost);
        edges[index++] = Edge(v1, v2, cost);
        sum += cost;
    }

    sort(edges, edges + M);
    fill(uf, uf + N + 1, -1);

    long long prevCost = 0, ans = 0;
    int cnt = 0;
    //간선 다 쓸 때까지
    for(int i = 0; i < M; i++){
        long long u = edges[i].u, v = edges[i].v, n1 = uf[find(u)], n2 = uf[find(v)];
        if(merge(u, v)){
            ans += ((sum - prevCost) * ((-n1 * -n2) % MOD)) % MOD;
            ans %= MOD;
            cnt++;
            if(cnt == N - 1) break;
        }
        prevCost += edges[i].w;
    }

    printf("%lld", ans);
    return 0;
}