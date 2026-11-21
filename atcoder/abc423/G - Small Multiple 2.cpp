#include <bits/stdc++.h>
using namespace std;
using ll = long long;

tuple<ll, ll, ll> egcd(ll a, ll b) { // ax + by = gcd(a, b)
	if (b == 0) return {1, 0, a};
	auto [x, y, g] = egcd(b, a % b);
	return {y, x - (a / b) * y, g};
} // x<=b/g, y<=a/g
ll modInv(ll a, ll b) {
	auto [x, y, g] = egcd(a, b);
	return g != 1 ? -1 : (x + b) % b;
} // modInv(n, MOD)

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	int TC;
	for (cin >> TC; TC--;) {
		ll mod;
		string st;
		cin >> mod >> st;

		vector<ll> pw(st.size() + 10, 1);
		for (int i = 1; i < pw.size(); i++) pw[i] = pw[i - 1] * 10 % mod;

		ll s = 0;
		for (auto ch : st) s = (s * 10 + (ch - '0')) % mod;

		vector<pair<ll, ll>> mn(10, {LLONG_MAX, LLONG_MAX});

		vector<ll> g(5), inv(5);
		for (int len = 0; len < 5; len++) {
			ll a = pw[st.size() + len];
			g[len] = __gcd(a, mod);
			inv[len] = modInv(a / g[len], mod / g[len]);
		}

		for (int r = 0; r < 1e4; r++) {
			int cnt_r = 0;
			for (int i = r; i; i /= 10) ++cnt_r;
			for (int len = cnt_r; len <= 4; len++) {
				ll b = -(s * pw[len] + r) % mod;
				if (b < 0) b += mod;
				ll a = pw[st.size() + len];
				// ax === b
				if (b % g[len]) continue;
				b /= g[len], a /= g[len];
				ll l = inv[len] * b % (mod / g[len]);
				mn[len] = min(mn[len], {l, r});
			}
		}

		for (int l = 0; l < 1e4; l++) {
			int cnt_l = 0;
			for (int i = l; i; i /= 10) ++cnt_l;
			for (int len = 0; len <= 9 - cnt_l; len++) {
				ll r = -(l * pw[st.size() + len] + s * pw[len]) % mod;
				if (r < 0) r += mod;
				int cnt_r = 0;
				for (int i = r; i; i /= 10) ++cnt_r;
				if (cnt_r <= len) mn[len] = min(mn[len], {l, r});
			}
		}

		string ans = st + string(9, '9');
		for (int len = 0; len < 10; len++) {
			auto [l, r] = mn[len];
			if (l == LLONG_MAX) continue;
			string a = l ? to_string(l) : "";
			string cur;
			string b = len ? to_string(r) : "";
			cur = a + st + string(len - b.size(), '0') + b;
			if (ans.size() > cur.size() || ans.size() == cur.size() && ans > cur) ans = cur;
		};
		cout << ans << "\n";
	}

	return 0;
}
