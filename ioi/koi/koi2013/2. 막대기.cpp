#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	int n, l;
	cin >> n >> l;

	vector<pair<int, int>> v(n);
	vector<int> as, bs;
	for (auto &[a, b] : v) {
		cin >> a >> b;
		as.push_back(a);
		bs.push_back(b);
	}

	sort(as.begin(), as.end());
	sort(bs.begin(), bs.end());
	sort(v.begin(), v.end());

	vector<ll> dp[2];
	dp[0].resize(as.size());
	dp[1].resize(bs.size());
	for (auto [a, b] : v) {
		ll d = l + abs(b - a);
		a = lower_bound(as.begin(), as.end(), a) - as.begin();
		b = lower_bound(bs.begin(), bs.end(), b) - bs.begin();
		ll x = dp[0][a] + d, y = dp[1][b] + d;
		dp[1][b] = max(dp[1][b], x);
		dp[0][a] = max(dp[0][a], y);
	}

	cout << max(
		*max_element(dp[0].begin(), dp[0].end()),
		*max_element(dp[1].begin(), dp[1].end())
	);

	return 0;
}
