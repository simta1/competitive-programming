#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	ll n;
	cin >> n;

	auto check = [&](ll s, ll d, int len) {
		ll cur = 1;
		for (int i = 0; i < len; i++) {
			ll val = s + i * d;
			if (cur > n / val) return false;
			cur *= val;
		}
		return true;
	};

	ll ans = 0;
	for (int len = 3; len <= 19; len++) {
		ll plo = 1e9;
		for (int s = 1; ; s++) {
			int lo = 0, hi = plo;
			while (lo + 1 < hi) {
				int mid = lo + hi >> 1;
				if (check(s, mid, len)) lo = mid;
				else hi = mid;
			}
			// if (len == 3) cout << s << " " << lo << "::\n";
			if (lo) {
				ans += lo;
				plo = lo + 1;
			}
			else break;
		}
	}
	cout << ans;

	return 0;
}
