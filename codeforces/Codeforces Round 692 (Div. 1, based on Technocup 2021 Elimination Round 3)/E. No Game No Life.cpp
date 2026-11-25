#include <bits/stdc++.h>
using namespace std;
using ll = long long;

constexpr ll MOD = 998'244'353;
void sub(ll &a, ll b) {
	a -= b;
	if (a < 0) a += MOD;
}

ll binpow(ll a, ll n) {
	ll res = 1;
	for (; n; n >>= 1) {
		if (n & 1) res = res * a % MOD;
		a = a * a % MOD;
	}
	return res;
}

ll modInv(ll a) {
	return binpow(a, MOD - 2);
};

void eliminate(int n, vector<vector<ll>> &a) {
	for (int i = 0; i < n; i++) {
		int p = i;
		while (p < n && !a[p][i]) ++p;
		swap(a[i], a[p]);
		ll mul = modInv(a[i][i]);
		for (auto &e : a[i]) e = e * mul % MOD;
		for (int i2 = 0; i2 < n; i2++) if (i2 != i) {
			mul = a[i2][i];
			for (int j = i; j < n + 1; j++) {
				a[i2][j] -= a[i][j] * mul;
				a[i2][j] %= MOD;
			}
		}
	}
}

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	int n, m;
	cin >> n >> m;

	vector<vector<int>> rdj(n + 1), adj(n + 1);
	vector<int> deg(n + 1);
	while (m--) {
	    int u, v;
	    cin >> u >> v;
		adj[u].push_back(v);
	    rdj[v].push_back(u);
		++deg[u];
	}

	queue<int> q;
	vector<int> g(n + 1);
	for (int i = 1; i <= n; i++) if (!deg[i]) {
		q.push(i);
	}
	while (!q.empty()) {
		auto cur = q.front();
		q.pop();
		for (auto nxt : rdj[cur]) if (--deg[nxt] == 0) {
			vector<bool> cnt(adj[nxt].size() + 1);
			for (auto x : adj[nxt]) if (g[x] < cnt.size()) cnt[g[x]] = 1;
			int mex = 0;
			while (cnt[mex]) ++mex;
			g[nxt] = mex;
			q.push(nxt);
		}
	}

	int mx = *max_element(g.begin(), g.end());
	int sz = 1;
	while (sz <= mx) sz <<= 1;
	vector<int> cnt(sz + 1);
	for (int i = 1; i <= n; i++) ++cnt[g[i]];

	vector a(sz, vector<ll>(sz + 1));
	a[0][sz] = 1;
	for (int i = 0; i < sz; i++) {
		a[i][i] = n + 1;
		for (int j = 0; j < sz; j++) {
			a[i][i ^ j] -= cnt[j];
			// sub(a[i][i ^ j], cnt[j]);
		}
	}
	eliminate(sz, a);
	ll ans = 1 - a[0][sz];
	ans %= MOD;
	if (ans < 0) ans += MOD;
	cout << ans;

	return 0;
}
