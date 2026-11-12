#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
	cin.tie(0) -> sync_with_stdio(0);
	constexpr ll MOD = 998'244'353;

	string st;
	cin >> st;

	int n = st.size();

	vector<ll> pref(n);
	auto left_fixed = [&](int l, int r) {
		for (int i = l; i <= r; i++) pref[i] = 0;

		pref[l] = st[l] - '0';
		ll cur = pref[l], mul = 1, sum = 0;
		for (int i = l + 1; i <= r; i++) {
			if (st[i] == '+') {
				mul = 1;
				sum = pref[i - 1];
				cur = 0;
				pref[i] = 0;
			}
			else if (st[i] == '*') {
				mul = mul * cur % MOD;
				cur = 0;
				pref[i] = 0;
			}
			else {
				int d = st[i] - '0';
				cur = (cur * 10 + d) % MOD;
				pref[i] = (sum + mul * cur) % MOD;
			}
		}

		ll res = 0;
		for (int i = l; i <= r; i++) res += pref[i];
		return res % MOD;
	};

	// for (int i = 0; i < n; i++) if (st[i] >= '0' && st[i] <= '9') {
	// 	cout << "\nl = " << i << "\n";
	// 	left_fixed(i, n - 1);
	// }

	vector<ll> suf(n);
	auto right_fixed = [&](int l, int r) {
		for (int i = l; i <= r; i++) suf[i] = 0;

		suf[r] = st[r] - '0';
		ll cur = suf[r], pw = 10, mul = 1, sum = 0;
		for (int i = r - 1; i >= l; i--) {
			if (st[i] == '+') {
				mul = 1;
				sum = suf[i + 1];
				cur = 0;
				pw = 1;
				suf[i] = 0;
			}
			else if (st[i] == '*') {
				mul = mul * cur % MOD;
				cur = 0;
				pw = 1;
				suf[i] = 0;
			}
			else {
				int d = st[i] - '0';
				cur = (cur + pw * d) % MOD;
				pw = pw * 10 % MOD;
				suf[i] = (cur * mul + sum) % MOD;
			}
			// cout << suf[i] << "::\n";
		}

		ll res = 0;
		for (int i = l; i <= r; i++) res += suf[i];
		return res % MOD;
	};

	// for (int i = n - 1; i >= 0; i--) if (st[i] >= '0' && st[i] <= '9') {
	// 	cout << "\nr = " << i << "\n";
	// 	right_fixed(0, i);
	// }

	vector<ll> dp(n);
	auto g = [&](int l, int r) {
		// ll res = 0;
		// for (int i = l; i <= r; i++) if (st[i] >= '0' && st[i] <= '9') res += left_fixed(i, r);
		// return res % MOD;

		for (int i = l; i <= r; i++) dp[i] = 0;

		ll prv = 0;
		ll sum = 0, len = 0, cur = 0;
		for (int i = l; i <= r; i++) {
			if (st[i] == '*') {
				prv = dp[i - 1];
				cur = sum = len = 0;
			}
			else {
				int d = st[i] - '0';
				++len;
				sum = (sum * 10 + len * d) % MOD;
				cur = (cur * 10 + d) % MOD;
				if (sum >= MOD) sum -= MOD;
				dp[i] = (sum + cur * prv) % MOD;
			}
			// cout << cur << " " << sum << " " << dp[i] << "::\n";
		}

		ll res = 0;
		for (int i = l; i <= r; i++) res += dp[i];
		return res % MOD;
	};

	// g(2, 5);
	// return 0;

	vector<int> pfs(st.size());
	for (int i = 0; i < n; i++) pfs[i] = st[i] >= '0' && st[i] <= '9';
	for (int i = 1; i < n; i++) pfs[i] += pfs[i - 1];
	auto count = [&](int l, int r) {
		return pfs[r] - (l ? pfs[l - 1] : 0);
	};

	// cout << g(2, 5) << "::\n";
	// cout << g(0, 0) << "::\n";
	// cout << right_fixed(0, 0) << " " << left_fixed(2, 5) << "::\n";

	auto f = [&](auto &&f, int l, int r) -> ll {
		int m = l + r >> 1;
		int plus = -1;
		for (int i = l; i <= r; i++) if (st[i] == '+') {
			if (!~plus || abs(m - plus) > abs(m - i)) plus = i;
		}
		// cout << l << " " << r << " " << plus << "::\n";

		ll res;
		if (!~plus) res = g(l, r);
		else res = (
			f(f, l, plus - 1)
			+ f(f, plus + 1, r)
			+ count(l, plus - 1) * left_fixed(plus + 1, r)
			+ count(plus + 1, r) * right_fixed(l, plus - 1)
		) % MOD;
		// cout << l << " " << r << " " << res << "::\n";
		return res;
	};

	cout << f(f, 0, n - 1);

	return 0;
}
