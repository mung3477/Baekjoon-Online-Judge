#include <stdio.h>
#include <vector>

#define MAX(a,b)(a>b?a:b)

using namespace std;

vector<int> adj[100001];
int dist[100001], d;
bool visited[100001];

int dfs(int cur) {
	visited[cur] = true;

	int depth = 0;

	for (int next : adj[cur]) {
		if (!visited[next]) {
			int tmp = dfs(next);

			if (tmp > d)
				dist[cur]++;

			depth = MAX(depth, tmp);
		}
	}

	if (depth > d)
		for (int next : adj[cur])
			dist[cur] += dist[next];

	return depth + 1;
}

int main() {
	int n, s;
	scanf("%d %d %d", &n, &s, &d);

	for (int i = 0; i < n - 1; i++) {
		int x, y;
		scanf("%d %d", &x, &y);

		adj[x].push_back(y);
		adj[y].push_back(x);
	}

	dfs(s);

	printf("%d", dist[s] * 2);

	return 0;
}