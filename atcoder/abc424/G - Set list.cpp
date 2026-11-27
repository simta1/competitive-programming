#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	int n, m;
	cin >> n >> m;

	vector<int> a(n);
	for (auto &e : a) cin >> e;
	sort(a.begin(), a.end());

	auto pfs = a;
	for (int i = 1; i < n; i++) pfs[i] += pfs[i - 1];

	vector<int> f(m + 1);
	int lb = 0, sum = 0;
	for (int i = 0; i <= m; i++) {
		while (lb < n && a[lb] < i) sum += a[lb++];
		f[i] = sum + (n - lb) * i;
	}

	vector<pair<int, int>> v(m);
	int bsum = 0;
	for (auto &[b, c] : v) {
		cin >> b >> c;
		bsum += b;
	}

	vector dp(m + 1, vector<ll>(bsum + 1, -1));
	dp[0][0] = 0;

	sort(v.rbegin(), v.rend());
	for (auto [b, c] : v) {
		for (int cnt = m - 1; cnt >= 0; cnt--) {
			for (int bs = 0; bs <= bsum; bs++) {
				if (!~dp[cnt][bs]) continue;
				if (bs + b <= f[cnt + 1]) dp[cnt + 1][bs + b] = max(dp[cnt + 1][bs + b], dp[cnt][bs] + c);
			}
		}
	}
	
	ll ans = 0;
	for (int cnt = 0; cnt <= m; cnt++) {
		for (int bs = 0; bs <= bsum; bs++) {
			ans = max(ans, dp[cnt][bs]);
		}
	}
	cout << ans;

	return 0;
}
