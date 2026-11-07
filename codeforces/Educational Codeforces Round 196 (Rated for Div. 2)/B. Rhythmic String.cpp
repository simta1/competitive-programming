#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	int TC;
	for (cin >> TC; TC--;) {
		int n;
		cin >> n;

		// constexpr ll MX = 1'000'000'000'000'000'000;
		// bool inf = 0;
		// ll lcm = 1;
		// vector<ll> v(n);
		// for (auto &e : v) {
		// 	cin >> e;
		// 	ll g = __gcd(lcm, e);
		// 	ll x = e / g;
		// 	if (!inf && lcm <= MX / x) lcm *= x;
		// 	else inf = 1;
		// }
		// if (inf) lcm = MX + 1;

		// sort(v.begin(), v.end());
		// auto it = upper_bound(v.begin(), v.end(), lcm);
		// int idx = it - v.begin();
		// int mx = 0;
		// // for (auto &e : v) cout << e << " "; cout << "\n";
		// // cout << idx << "::\n";
		// for (int i = 0, j = 0; i < idx; i = j) {
		// 	while (j < idx && v[i] == v[j]) ++j;
		// 	mx = max(mx, j - i);
		// }
		// // cout << idx << " " << mx << "\n";
		// cout << idx - mx << "\n";


		vector<int> v(n);
		for (auto &e : v) cin >> e;

		int mx = 0;
		for (auto e : v) {
			int cnt = 0;
			for (auto e2 : v) if (e2 % e == 0) ++cnt;
			mx = max(mx, cnt);
		}
		cout << n - mx << "\n";

		// int ans = n - 1;
		// sort(v.begin(), v.end());
		// for (int i = 0, j = 0; i < n; i = j) {
		// 	while (j < n && v[i] == v[j]) ++j;
			
		// 	ans = min(ans, cur);
		// }
		// cout << ans << "\n";
	}

	return 0;
}
