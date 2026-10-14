#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	string a, b;
	cin >> a >> b;

	constexpr int INF = 1e7;

	reverse(a.begin(), a.end());
	int m = a.size();
	auto gdp = [&](const string &st) {
		int n = st.size();
		vector dp(m + 1, vector<int>(n + 1, INF));
		for (int i = 0; i <= m; i++) dp[i][0] = i;
		for (int j = 0; j <= n; j++) dp[0][j] = j;
		for (int i = 1; i <= m; i++) {
			for (int j = 1; j <= n; j++) {
				dp[i][j] = min({
					dp[i][j - 1] + 1,
					dp[i - 1][j] + 1,
					dp[i - 1][j - 1] + (a[i - 1] != st[j - 1])
				});
			}
		}
		return dp;
	};

	int n = b.size();

	vector<int> dp(n + 1, INF);
	dp[0] = 0;
	for (int i = 1; i <= n; i++) {
		int len = min(i, 2 * m);
		auto st = b.substr(i - len + 1 - 1, len);
		reverse(st.begin(), st.end());
		auto dp2 = gdp(st);
		int mn = INF;
		for (int j = i; j >= i - len + 1; j--) {
			// dp[i] = dp2(j, i) + min(dp[j-1:i-1])
			mn = min(mn, dp[j - 1]);
			if (dp2[m][i - j + 1] > m) continue;
			dp[i] = min(dp[i], dp2[m][i - j + 1] + mn);
		}
	}

	cout << dp[n];

	return 0;
}
