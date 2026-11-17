#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	int TC;
	for (cin >> TC; TC--;) {
		int n, m, q;
		cin >> n >> m >> q;

		int B = sqrt(m) / 5;

		vector<vector<int>> adj(n);
		while (m--) {
			int u, v;
			cin >> u >> v;
			--u, --v;
			adj[u].push_back(v);
			adj[v].push_back(u);
		}

		for (int i = 0; i < n; i++) sort(adj[i].begin(), adj[i].end());

		int ans = n;
		vector<int> p(n);
		vector<int> deg(n);
		vector<vector<int>> has(n);
		for (int i = 0; i < n; i++) {
			p[i] = i;
			has[i] = {i};
			deg[i] = adj[i].size();
		}

		auto find = [&](int a) {
			while (a != p[a]) a = p[a] = p[p[a]];
			return a;
		};
		auto init = [&](int a) {
			p[a] = a;
			has[a] = {a};
			deg[a] = adj[a].size();
		};

		while (q--) {
			int u, v;
			cin >> u >> v;
			--u, --v;
			if (find(u) != find(v)) {
				int a = find(u);
				int b = find(v);
				if (deg[a] > deg[b]) swap(a, b);

				if ([&]() {
					if (deg[a] == 0) return false;
					if (has[a].size() <= B && has[b].size() <= B) {
						for (auto e1 : has[a]) {
							for (auto e2 : has[b]) {
								if (binary_search(adj[e2].begin(), adj[e2].end(), e1)) return true;
							}
						}
						return false;
					}
					else {
						for (auto e1 : has[a]) {
							for (auto e2 : adj[e1]) {
								if (find(e2) == b) return true;
							}
						}
						return false;
					}
				}()) {
					vector<int> is;
					for (auto i : has[a]) is.push_back(i);
					for (auto i : has[b]) is.push_back(i);
					ans += has[a].size() - 1;
					ans += has[b].size() - 1;
					for (auto i : is) init(i);
				}
				else {
					p[a] = b;
					deg[b] += deg[a];
					if (has[a].size() > has[b].size()) swap(has[a], has[b]);
					for (auto e : has[a]) has[b].push_back(e);
					--ans;
				}
			}
			cout << ans << "\n";
		}
	}

	return 0;
}
