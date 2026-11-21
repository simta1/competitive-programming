#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
	cin.tie(0) -> sync_with_stdio(0);
	constexpr ll MOD = 998'244'353;
	auto binpow = [&](ll a, ll n) {
		ll res = 1;
		for (; n; n >>= 1) {
			if (n & 1) res = res * a % MOD;
			a = a * a % MOD;
		}
		return res;
	};
	auto modInv = [&](ll a) { return binpow(a, MOD - 2); };
	constexpr int N = 105;
	static ll fac[N + 1] = {1}, ifac[N + 1]{};
	for (int i = 1; i <= N; i++) fac[i] = fac[i - 1] * i % MOD;
	ifac[N] = modInv(fac[N]);
	for (int i = N - 1; i >= 0; i--) ifac[i] = ifac[i + 1] * (i + 1) % MOD;

	int n, k;
	cin >> n >> k;

	vector<vector<int>> adj(n + 1);
	for (int i = 1; i < n; i++) {
	    int u, v;
	    cin >> u >> v;
	    adj[u].push_back(v);
	    adj[v].push_back(u);
	}

	vector<vector<vector<ll>>> dp(n + 1);
	vector<int> sz(n + 1, 1);
	auto dfs = [&](auto &&dfs, int cur, int par) -> void {
		dp[cur] = vector(2, vector<ll>(n));
		dp[cur][1][0] = 1;
		for (auto nxt : adj[cur]) if (nxt != par) {
			dfs(dfs, nxt, cur);
			vector ndp(sz[cur] + sz[nxt] + 1, vector<ll>(n));
			for (int a = 1; a <= sz[cur]; a++) {
				for (int b = 0; a + b <= sz[cur]; b++) {
					if (dp[cur][a][b]) ndp[a][b + 1] = dp[cur][a][b];
				}
			}
			for (int a = 1; a <= sz[cur]; a++) {
				for (int b = 0; a + b <= sz[cur]; b++) {
					for (int x = 1; x <= sz[nxt]; x++) {
						for (int y = 0; x + y <= sz[nxt]; y++) {
							ndp[a + x][b + y] += dp[cur][a][b] * dp[nxt][x][y];
							ndp[a + x][b + y] %= MOD;
						}
					}
				}
			}
			swap(dp[cur], ndp);
			sz[cur] += sz[nxt];
		}
	};
	dfs(dfs, 1, -1);

	ll ans = 0;
	for (int i = 1; i <= n; i++) {
		for (int a = k + 1; a <= sz[i]; a++) {
			for (int b = 0; a + b <= sz[i]; b++) {
				int bb = b + (i != 1);
				ans += fac[a] * fac[bb] % MOD * ifac[a + bb] % MOD * dp[i][a][b];
				ans %= MOD;
			}
		}
	}
	cout << ans;

	return 0;
}
