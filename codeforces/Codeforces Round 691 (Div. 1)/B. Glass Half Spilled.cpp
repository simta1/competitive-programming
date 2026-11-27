#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	int n;
	cin >> n;

	vector<pair<int, int>> v(n);
	int asum = 0, bsum = 0;
	for (auto &[a, b] : v) {
		cin >> a >> b;
		a *= 2, b *= 2;
		asum += a;
		bsum += b;
	}

	constexpr int INF = 1e8;
	vector dp(n + 1, vector<int>(asum + 1, -INF));
	dp[0][0] = 0;
	for (int i = 0; i < n; i++) {
		auto ndp = dp;
		auto [a, b] = v[i];
		for (int cnt = 0; cnt <= i; cnt++) {
			for (int sa = 0; sa <= asum; sa++) {
				if (dp[cnt][sa] == -INF) continue;
				ndp[cnt + 1][sa + a] = max(ndp[cnt + 1][sa + a], dp[cnt][sa] + b);
			}
		}
		swap(dp, ndp);
	}

	// for (int cnt = 1; cnt <= n; cnt++) {

	// }

	for (int k = 1; k <= n; k++) {
		for (int i = asum - 1; i >= 0; i--) dp[k][i] = max(dp[k][i], dp[k][i + 1]);
		auto check = [&](int x) {
			return dp[k][x] + bsum >= 2 * x;
		};

		int lo = 0, hi = asum + 1;
		while (lo + 1 < hi) {
			int mid = lo + hi >> 1;
			if (check(mid)) lo = mid;
			else hi = mid;
		}
		cout << lo * 0.5 << " ";
	}


	return 0;
}
