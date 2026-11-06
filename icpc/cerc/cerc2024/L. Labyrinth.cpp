#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	int n, q;
	cin >> n >> q;

	constexpr array<pair<int, int>, 4> dpos = {{
		{-1, 0}, {0, 1}, {1, 0}, {0, -1}
	}};

	vector<string> v(n);
	for (auto &st : v) cin >> st;

	auto f = [&](int i, int j, int d) {
		return n * i + j << 2 | d;
	};
	auto inRange = [&](int i, int j) {
		return i >= 0 && i < n && j >= 0 && j < n;
	};

	int N = 4 * n * n;
	vector<int> adj(N + 1, -1);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (v[i][j] == '#') continue;
			for (int cd = 0; cd < 4; cd++) {
				for (int k = 1; k <= 10; k += 3) {
					int nd = cd + k & 3;
					auto [di, dj] = dpos[nd];
					int ni = i + di, nj = j + dj;
					if (!inRange(ni, nj)) {
						adj[f(i, j, cd)] = N;
						break;
					}
					else if (v[ni][nj] == '.') {
						adj[f(i, j, cd)] = f(ni, nj, nd);
						break;
					}
				}
			}
		}
	}

	vector<int> state(N + 1), dp(N + 1);
	auto dfs = [&](auto &&dfs, int cur) -> void {
		state[cur] = 1;
		int nxt = adj[cur];
		if (~nxt) {
			if (!state[nxt]) {
				dfs(dfs, nxt);
				dp[cur] = !~dp[nxt] ? -1 : dp[nxt] + 1;
			}
			else if (state[nxt] == 1) dp[cur] = -1;
			else dp[cur] = !~dp[nxt] ? -1 : dp[nxt] + 1;
		}
		else dp[cur] = cur == N ? 0 : -1;
		state[cur] = 2;
	};
	for (int i = 0; i < N; i++) if (!state[i]) dfs(dfs, i);

	while (q--) {
		int r, c;
		char ch;
		cin >> r >> c >> ch;
		int dir = string("URDL").find(ch);
		cout << dp[f(r - 1, c - 1, dir)] << "\n";
	}
	return 0;
}
