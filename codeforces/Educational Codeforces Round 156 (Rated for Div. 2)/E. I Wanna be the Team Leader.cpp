#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	int n, m;
	cin >> n >> m;

	vector<pair<int, int>> a(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i].first;
		a[i].second = i + 1;
	}
	sort(a.rbegin(), a.rend());

	vector<int> b(m);
	for (auto &e : b) cin >> e;

	vector nxt(m, vector<int>(n + 1));
	for (int i = 0; i < m; i++) {
		for (int l = 0; l <= n; l++) {
			int r = 1;
			if (l) r = nxt[i][l - 1];
			while (r <= n && ll(r - l) * a[r - 1].first < b[i]) ++r;
			nxt[i][l] = r;
		}
	}

	vector<int> dp(1 << m, n + 1);
	dp[0] = 0;
	vector<int> p(1 << m);
	for (int mask = 0; mask < (1 << m); mask++) {
		if (dp[mask] == n + 1) continue;
		for (int i = 0; i < m; i++) if (~mask >> i & 1) {
			int nmask = mask | 1 << i;
			int ndp = nxt[i][dp[mask]];
			if (dp[nmask] > ndp) {
				dp[nmask] = ndp;
				p[nmask] = mask;
			}
		}
	}

	if (dp[(1 << m) - 1] == n + 1) cout << "NO\n";
	else {
		cout <<"YES\n";

		vector<pair<int, int>> ans(m);
		int mask = (1 << m) - 1;
		while (mask) {
			int pmask = p[mask];
			int i = __builtin_ctz(mask ^ pmask);
			ans[i] = {dp[pmask] + 1, dp[mask]};
			mask = pmask;
		}
		for (int i = 0; i < m; i++) {
			auto [l, r] = ans[i];
			cout << r - l + 1 << " ";
			for (int i = l; i <= r; i++) cout << a[i - 1].second << " ";
			cout << "\n";
		}
	}

	return 0;
}
