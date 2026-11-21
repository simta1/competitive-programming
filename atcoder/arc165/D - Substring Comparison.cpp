#include <bits/stdc++.h>
using namespace std;
using ll = long long;

auto getSCC(int n, const vector<vector<int>> &adj) { // adj: 0-based // O(V+E)
	vector<int> dfsn(n), sccn(n, -1);
	vector<int> s(n);
	int top = 0, dfsi = 0, scci = 0;
	auto dfs = [&](auto &&dfs, int cur) -> int {
		int low = dfsn[cur] = ++dfsi;
		s[top++] = cur;
		for (auto nxt : adj[cur]) if (!~sccn[nxt]) low = min(low, dfsn[nxt] ? dfsn[nxt] : dfs(dfs, nxt));
		if (low == dfsn[cur]) {
			do { sccn[s[--top]] = scci; } while (s[top] != cur);
			++scci;
		}
		return low;
	};
	for (int i = 0; i < n; i++) if (!dfsn[i]) dfs(dfs, i);
	for (int i = 0; i < n; i++) sccn[i] = scci - 1 - sccn[i];
	return pair{scci, sccn}; // 0-based // scci = scc 개수
}

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	int n, m;
	cin >> n >> m;

	vector<array<int, 4>> v(m);
	for (auto &[a, b, c, d] : v) {
		cin >> a >> b >> c >> d;
		--a, --b, --c, --d;
	}

	vector<int> p(n);
	iota(p.begin(), p.end(), 0);

	if ([&]() {
		int tot = n;
		while (1) {
			vector<vector<int>> adj(tot);
			for (auto &[a, b, c, d] : v) {
				while (a <= b && c <=d && p[a] == p[c]) ++a, ++c;
				if (c > d) return false;
				if (a <= b) adj[p[a]].push_back(p[c]);
			}
			auto [cnt, sccn] = getSCC(tot, adj);
			if (tot == cnt) return true;
			for (int i = 0; i < n; i++) p[i] = sccn[p[i]];
			tot = cnt;
		}
		return true;
	}()) cout << "Yes\n";
	else cout << "No\n";

	return 0;
}
