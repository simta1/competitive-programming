#include <bits/stdc++.h>
using namespace std;
using ll = long long;

constexpr ll MOD = 1e9 + 7;
void add(ll &a, ll b) {
	a += b;
	if (a >= MOD) a -= MOD;
}

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	int n, m;
	cin >> n >> m;

	string st;
	cin >> st;

	vector<int> pfs(n + 1);
	for (int i = 1; i <= n; i++) pfs[i] = pfs[i - 1] + (st[i - 1] == '1');

	vector<int> right(n + 1);
	iota(right.begin(), right.end(), 0);

	while (m--) {
		int l, r;
		cin >> l >> r;
		right[l] = max(right[l], r);
	}
	for (int i = 1; i <= n; i++) right[i] = max(right[i - 1], right[i]);

	vector<int> v(n + 1);
	for (int i = 1; i <= n; i++) v[i] = pfs[right[i]] - pfs[right[i - 1]];

	vector dp(n + 1, vector<ll>(n + 1));
	dp[0][0] = 1;
	for (int i = 0; i < n; i++) {
		for (int cnt = 0; cnt <= n; cnt++) {
			if (!dp[i][cnt]) continue;
			int c1 = cnt + v[i + 1];
			int tot = right[i + 1] - i;
			int c0 = tot - c1;
			if (c0) add(dp[i + 1][cnt + v[i + 1]], dp[i][cnt]);
			if (c1) add(dp[i + 1][cnt - 1 + v[i + 1]], dp[i][cnt]);
		}
	}
	cout << dp[n][0];

	return 0;
}
