#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	int n, m;
	cin >> n >> m;

	vector<bool> seen(1 << n);
	vector<int> v(m);
	for (int i = 0; i < m; i++) {
		int k;
		for (cin >> k; k--;) {
			int x;
			cin >> x;
			v[i] |= 1 << x;
		}
		if (seen[v[i]]) {
			cout << "not possible";
			return 0;
		}
		seen[v[i]] = 1;
	}

	vector<ll> have(n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (v[j] >> i & 1) have[i] |= 1LL << j;
		}
	}

	vector dp(1 << n, vector<int>(m, -1));
	auto gdp = [&](auto &&gdp, int mask, int candi, int cnt) -> int {
		if (cnt <= 1) return 0;

		auto &res = dp[mask][candi];
		if (~res) return res;

		ll cand = 0;
		for (int j = 0; j < m; j++) {
			if ((v[j] & mask) == (v[candi] & mask)) cand |= 1LL << j;
		}

		res = 1e8;
		for (int i = 0; i < n; i++) if (~mask >> i & 1) {
			ll yes = cand & have[i];
			ll no = cand & ~have[i];
			if (!yes || !no) continue;

			int nmask = mask | 1 << i;
			int ncandi0 = __builtin_ctzll(no);
			int ncnt0 = __builtin_popcountll(no);
			int ncandi1 = __builtin_ctzll(yes);
			int ncnt1 = __builtin_popcountll(yes);
			res = min(res, cnt + gdp(gdp, nmask, ncandi0, ncnt0) + gdp(gdp, nmask, ncandi1, ncnt1));
		}
		return res;
	};

	cout << fixed << setprecision(12) << gdp(gdp, 0, 0, m) / double(m);

	return 0;
}
