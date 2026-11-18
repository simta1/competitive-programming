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

	int n;
	cin >> n;

	string st;
	cin >> st;

	int k = st.size();

	vector<ll> dp(n + 1);
	dp[0] = 1;
	for (int i = 0; i < n; i++) {
		vector<ll> ndp(n + 1);
		for (int len = 0; len <= i; len++) {
			add(ndp[len + 1], dp[len]);
			add(ndp[len + 1], dp[len]);
			add(ndp[max(0, len - 1)], dp[len]);
		}
		swap(ndp, dp);
	}

	ll ans = dp[k];
	constexpr ll inv2 = MOD + 1 >> 1;
	while (k--) ans = ans * inv2 % MOD;
	cout << ans;

	return 0;
}
