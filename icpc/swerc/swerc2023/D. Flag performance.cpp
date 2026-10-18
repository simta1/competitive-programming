#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	int n, k, t;
	cin >> n >> k >> t;

	vector<int> v;
	vector<vector<int>> vs;
	map<vector<int>, int> mp;
	auto dfs = [&](auto &&dfs, int rem, int mn) {
		if (!rem) {
			vs.push_back(v);
			mp[v] = vs.size() - 1;
			return;
		}
		for (int i = mn; i <= rem; i++) {
			v.push_back(i);
			dfs(dfs, rem - i, i);
			v.pop_back();
		}
	};
	dfs(dfs, n, 1);

	constexpr ll MOD = 1e9 + 7;

	vector<vector<pair<int, int>>> adj(mp.size());
	for (int cur = 0; cur < mp.size(); cur++) {
		auto cv = vs[cur];
		for (int i = 0; i < cv.size(); i++) {
			for (int j = i + 1; j < cv.size(); j++) {
				auto nv = cv;
				nv.erase(find(nv.begin(), nv.end(), cv[i]));
				nv.erase(find(nv.begin(), nv.end(), cv[j]));
				nv.insert(lower_bound(nv.begin(), nv.end(), cv[i] + cv[j]), cv[i] + cv[j]);
				adj[cur].emplace_back(mp[nv], cv[i] * cv[j] % MOD);
			}
		}
		for (int i = 0; i < cv.size(); i++) {
			for (int x = 1; 2 * x <= cv[i]; x++) {
				auto nv = cv;
				nv.erase(find(nv.begin(), nv.end(), cv[i]));
				nv.insert(lower_bound(nv.begin(), nv.end(), x), x);
				nv.insert(lower_bound(nv.begin(), nv.end(), cv[i] - x), cv[i] - x);
				adj[cur].emplace_back(mp[nv], (2 * x == cv[i] ? x : cv[i]));
			}
		}
	}

	vector<ll> dp(mp.size());
	dp[0] = 1;
	
	while (k--) {
		vector<ll> ndp(mp.size());
		for (int cur = 0; cur < mp.size(); cur++) {
			for (auto [nxt, w] : adj[cur]) {
				ndp[cur] += dp[nxt] * w;
				ndp[cur] %= MOD;
			}
		}
		swap(dp, ndp);
	}

	while (t--) {
		vector<int> v(n);
		for (auto &e : v) cin >> e, --e;
		vector<bool> visited(n);
		vector<int> a;
		for (int i = 0; i < n; i++) if (!visited[i]) {
			int cur = i, cnt = 0;
			while (!visited[cur]) {
				visited[cur] = 1;
				cur = v[cur];
				++cnt;
			}
			a.push_back(cnt);
		}
		sort(a.begin(), a.end());
		cout << dp[mp[a]] << "\n";
	}

	return 0;
}
