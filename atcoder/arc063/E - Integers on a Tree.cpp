#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	int n;
	cin >> n;

	vector<vector<int>> adj(n + 1);
	for (int i = 1; i < n; i++) {
	    int u, v;
	    cin >> u >> v;
	    adj[u].push_back(v);
	    adj[v].push_back(u);
	}

	int k;
	cin >> k;

	using pii = pair<int, int>;
	priority_queue<pii, vector<pii>, greater<pii>> pq;
	vector<int> ans(n + 1, -1);
	while (k--) {
		int v, p;
		cin >> v >> p;
		ans[v] = p;
		pq.emplace(ans[v], v);
	}

	while (!pq.empty()) {
		auto [dist, cur] = pq.top();
		pq.pop();
		for (auto nxt : adj[cur]) {
			if (!~ans[nxt]) {
				ans[nxt] = ans[cur] + 1;
				pq.emplace(ans[nxt], nxt);
			}
			else {
				if (abs(ans[nxt] - ans[cur]) != 1) {
					cout << "No";
					return 0;
				}
			}
		}
	}

	cout << "Yes\n";
	for (int i = 1; i <= n; i++) cout << ans[i] << "\n";

	return 0;
}
