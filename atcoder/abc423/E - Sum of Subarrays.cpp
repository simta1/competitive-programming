#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using hh = __int128_t;

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	constexpr bool debug = 0;

	int n, q;
	if constexpr (debug) {
		n = 20, q = 100;
	}
	else cin >> n >> q;

	vector<int> v(n + 1);
	if constexpr (debug) {
		for (int i = 1; i <= n; i++) v[i] = rand() % 100 + 1;
	}
	else {
		for (int i = 1; i <= n; i++) cin >> v[i];
	}

	vector<hh> pfs(n + 1);
	for (int i = 1; i <= n; i++) pfs[i] = v[i] + pfs[i - 1];

	auto ppfs = pfs;
	for (int i = 1; i <= n; i++) ppfs[i] += ppfs[i - 1];

	vector<hh> pfs_pfsii(n + 1);
	for (int i = 1; i <= n; i++) {
		pfs_pfsii[i] = pfs[i] * i;
		pfs_pfsii[i] += pfs_pfsii[i - 1];
	}
	auto pfs_ppfs = ppfs;
	for (int i = 1; i <= n; i++) {
		pfs_ppfs[i] += pfs_ppfs[i - 1];
	}

	auto naive = [&](int L, int R) {
		ll res = 0;
		for (int l = L; l <= R; l++) {
			for (int r = l; r <= R; r++) {
				res += pfs[r] - pfs[l - 1];
			}
		}
		return res;
	};

	auto test = [&](int L, int R) {
		ll res = 0;
		// for (int i = L; i <= R; i++) {
		// 	res += pfs[i] * i + (-L + 1) * pfs[i] - ppfs[i - 1] + (L >= 2 ? ppfs[L - 2] : 0);
		// }

		// return pfs_pfsii[R] - pfs_pfsii[L - 1]
		// 	+ (-L + 1) * (ppfs[R] - ppfs[L - 1])
		// 	- (pfs_ppfs[R - 1] - (L >= 2 ? pfs_ppfs[L - 2] : 0))
		// 	+ (L >= 2 ? pfs_ppfs[L - 2] : 0) * (R - L + 1);


		res = pfs_pfsii[R] - pfs_pfsii[L - 1];
		res += (-L + 1) * (ppfs[R] - ppfs[L - 1]);
		res -= pfs_ppfs[R - 1] - (L >= 2 ? pfs_ppfs[L - 2] : 0);
		for (int i = L; i <= R; i++) {
			// res += - ppfs[i - 1] + (L >= 2 ? ppfs[L - 2] : 0);
			res += (L >= 2 ? ppfs[L - 2] : 0);
		}

		return res;
	};


	while (q--) {
		int L, R;
		if constexpr (debug) {
			L = rand() % n + 1;
			R = rand() % (n - L + 1) + L;
		}
		else cin >> L >> R;

		if (L == R) {
			if constexpr (!debug) cout << v[L] << "\n";
			continue;
		}

		ll ans = pfs_pfsii[R] - pfs_pfsii[L - 1]
			+ (-L + 1) * (ppfs[R] - ppfs[L - 1])
			- (pfs_ppfs[R - 1] - (L >= 2 ? pfs_ppfs[L - 2] : 0))
			+ (L >= 2 ? ppfs[L - 2] : 0) * (R - L + 1);

		if constexpr (debug) {
			assert(test(L, R) == naive(L, R));
			if (ans != naive(L, R)) {
				cout << L << " " << R << "::\n";
				for (auto &e : v) cout << e << " "; cout << "\n";
				cout << ans << " " << naive(L, R) << "::\n";
				return 0;
			}
		}
		else cout << ll(ans) << "\n";
	}

	return 0;
}
