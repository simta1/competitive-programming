#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	int TC;
	for (cin >> TC; TC--;) {
		int n;
		cin >> n;

		vector<vector<int>> adj(n + 1);
		for (int i = 1; i < n; i++) {
		    int u, v;
		    cin >> u >> v;
		    adj[u].push_back(v);
		    adj[v].push_back(u);
		}

		if (~n & 1) {
			cout << n + 1 << "\n";
			continue;
		}

		auto check = [&](int k, int root) {
			vector<int> top(n + 1);
			auto mkt = [&](auto &&mkt, int cur, int par) -> void {
				for (auto nxt : adj[cur]) if (nxt != par) {
					if (cur == root) top[nxt] = nxt;
					else top[nxt] = top[cur];
					mkt(mkt, nxt, cur);
				}
			};
			mkt(mkt, root, -1);

			for (int i = 1; i <= n; i++) {
				if (k - i >= 1 && k - i <= n && k - i != i && top[i] != top[k - i]) return true;
			}
			return false;
		};

		vector<pair<int, int>> candi = {
			{n + 1, n + 1 >> 1},
			{n, n},
			{n + 2, 1}
		};

		bool flag = 0;
		for (auto [k, root] : candi) {
			if (check(k, root)) {
				cout << k << "\n";
				flag = 1;
				break;
			}
		}
		if (!flag) cout << n << "\n";
	}

	return 0;
}
