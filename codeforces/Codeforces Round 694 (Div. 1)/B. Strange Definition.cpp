#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	vector<int> primes;
	constexpr int N = 1e6;
	static int lpf[N + 1];
	for (int i = 2; i <= N; i++) {
		if (!lpf[i]) {
			lpf[i] = i;
			primes.push_back(i);
		}
		for (auto p : primes) {
			if (i > N / p) break;
			lpf[i * p] = p;
			if (i % p == 0) break;
		}
	}

	auto f = [&](int n) {
		int res = 1;
		while (n > 1) {
			int p = lpf[n];
			bool cnt = 0;
			while (n % p == 0) {
				n /= p;
				cnt ^= 1;
			}
			if (cnt) res *= p;
		}
		return res;
	};

	int TC;
	for (cin >> TC; TC--;) {
		int n;
		cin >> n;

		vector<int> v(n);
		for (auto &e : v) {
			cin >> e;
			e = f(e);
		}
		sort(v.begin(), v.end());

		// for (auto &e : v) cout << e << " "; cout << "\n";
		
		int mx[2]{};
		int sum = 0;
		for (int i = 0, j = 0; i < n; i = j) {
			while (j < n && v[i] == v[j]) ++j;
			int cnt = j - i;
			mx[cnt & 1] = max(mx[cnt & 1], cnt);
			if (v[i] == 1 || cnt >= 2 && ~cnt & 1) sum += cnt;
		}

		int ans0 = max(mx[0], mx[1]);
		int ans1 = max(mx[1], sum);

		int q;
		for (cin >> q; q--;) {
			ll w;
			cin >> w;
			if (w == 0) cout << ans0 << "\n";
			else cout << ans1 << "\n";
		}
	}

	return 0;
}
