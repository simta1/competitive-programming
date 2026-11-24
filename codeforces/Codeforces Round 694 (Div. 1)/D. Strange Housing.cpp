#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	int TC;
	for (cin >> TC; TC--;) {
		int n, m;
		cin >> n >> m;

		vector<vector<int>> adj(n + 1);
		while (m--) {
		    int u, v;
		    cin >> u >> v;
		    adj[u].push_back(v);
		    adj[v].push_back(u);
		}

		vector<int> ans(n + 1, -1);
		queue<int> q;
		auto f = [&](int u) {
			ans[u] = 1;
			for (auto v : adj[u]) {
				if (~ans[v]) {
					assert(ans[v] == 0);
					continue;
				}
				q.push(v);
				ans[v] = 0;
			}
		};

		f(1);
		while (!q.empty()) {
			auto cur = q.front();
			q.pop();
			for (auto nxt : adj[cur]) if (!~ans[nxt]) f(nxt);
		}

		bool flag = 1;
		for (int i = 1; i <= n; i++) {
			if (!~ans[i]) flag = 0;
		}
		if (flag) {
			cout << "YES\n";
			cout << count(ans.begin(), ans.end(), 1) << "\n";
			for (int i = 1; i <= n; i++) if (ans[i]) cout << i << " ";
		}
		else cout << "NO\n";
	}

	return 0;
}
