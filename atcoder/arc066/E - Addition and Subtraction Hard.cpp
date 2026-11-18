#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	int n;
	cin >> n;

	vector<int> v(n);
	cin >> v[0];
	for (int i = 1; i < n; i++) {
		char ch;
		cin >> ch;
		cin >> v[i];
		if (ch == '-') v[i] *= -1;
	}

	constexpr ll INF = 1e18;
	vector<array<ll, 3>> dp(n + 1, {-INF, -INF, -INF});
	dp[0][0] = 0;
	for (int i = 0; i < n; i++) {
		for (int cnt = 0; cnt < 3; cnt++) {
			if (dp[i][cnt] == -INF) continue;

			if (v[i] > 0) {
				for (int ncnt = 0; ncnt <= cnt; ncnt++) {
					int val = ncnt & 1 ? -v[i] : v[i];
					dp[i + 1][ncnt] = max(dp[i + 1][ncnt], dp[i][cnt] + val);
				}
			}
			else {
				for (int ncnt = 1; ncnt <= min(2, cnt + 1); ncnt++) {
					int val = ncnt & 1 ? v[i] : -v[i];
					dp[i + 1][ncnt] = max(dp[i + 1][ncnt], dp[i][cnt] + val);
				}
			}
		}
	}
	cout << *max_element(dp[n].begin(), dp[n].end());

	return 0;
}
