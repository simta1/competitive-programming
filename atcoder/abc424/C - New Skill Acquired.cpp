#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	int n;
	cin >> n;

	vector<vector<int>> adj(n + 1);
	for (int i = 1; i <= n; i++) {
		int a, b;
		cin >> a >> b;
		adj[a].push_back(i);
		adj[b].push_back(i);
	}

	vector<bool> visited(n + 1);
	queue<int> q;
	q.push(0);
	visited[0] = 1;
	int ans = 0;
	while (!q.empty()) {
		auto cur = q.front();
		q.pop();
		for (auto nxt : adj[cur]) if (!visited[nxt]) {
			++ans;
			visited[nxt] = 1;
			q.push(nxt);
		}
	}

	cout << ans;

	return 0;
}
