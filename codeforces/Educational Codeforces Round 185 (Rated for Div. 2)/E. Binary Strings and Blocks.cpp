#include <bits/stdc++.h>
using namespace std;
using ll = long long;

constexpr ll MOD = 998'244'353;
void add(ll &a, ll b) {
	a += b;
	if (a >= MOD) a -= MOD;
}

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	vector<ll> pow2(3e5 + 1, 1);
	for (int i = 1; i < pow2.size(); i++) pow2[i] = pow2[i - 1] * 2 % MOD;

	int TC;
	for (cin >> TC; TC--;) {
		int n, m;
		cin >> n >> m;

		vector<int> v(n, -1);
		while (m--) {
			int l, r;
			cin >> l >> r;
			--l, --r;
			v[r] = max(v[r], l);
		}

		for (int i = 1; i < n; i++) v[i] = max(v[i], v[i - 1]);

		vector<ll> dp(n), pfs(n);
		dp[0] = pfs[0] = 2;
		for (int i = 1; i < n; i++) {
			if (v[i] == -1) dp[i] = pow2[i + 1];
			else {
				assert(v[i] < i);
				dp[i] = pfs[i - 1] - (v[i] ? pfs[v[i] - 1] : 0);
				if (dp[i] < 0) dp[i] += MOD;
			}

			pfs[i] = pfs[i - 1] + dp[i];
			if (pfs[i] >= MOD) pfs[i] -= MOD;
		}

		cout << dp[n - 1] << "\n";
	}

	return 0;
}
