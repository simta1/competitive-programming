#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	string st;
	cin >> st;

	ll x, y;
	cin >> x >> y;

	int cnt[2]{};
	int n = st.size();
	vector<ll> right0;
	for (int i = n - 1; i >= 0; i--) {
		auto ch = st[i];
		if (ch == '?') {
			right0.push_back(cnt[0]);
		}
		else ++cnt[ch - '0'];
	}
	reverse(right0.begin(), right0.end());

	ll I = 0;
	cnt[0] = cnt[1] = 0;
	vector<ll> left1;
	for (auto ch : st) {
		if (ch == '?') {
			left1.push_back(cnt[1]);
		}
		else {
			++cnt[ch - '0'];
			if (ch == '0') I += cnt[1];
		}
	}

	ll ans = 9e18;
	if (y >= x) {
		for (int i = 1; i < left1.size(); i++) left1[i] += left1[i - 1];
		for (int i = right0.size() - 2; i >= 0; i--) right0[i] += right0[i + 1];
		for (int c0 = 0; c0 <= left1.size(); c0++) {
			ll c1 = left1.size() - c0;
			ll curI = I + (c0 ? left1[c0 - 1] : 0) + (c1 ? right0[right0.size() - c1]: 0);
			ll t0 = c0 + cnt[0];
			ll t1 = c1 + cnt[1];
			ans = min(ans, curI * (y - x) + t0 * t1 * x);
		}
	}
	else {
		for (int i = left1.size() - 2; i >= 0; i--) left1[i] += left1[i + 1];
		// cout << right0[0] << "::\n";
		for (int i = 1; i < right0.size(); i++) right0[i] += right0[i - 1];
		for (int c0 = 0; c0 <= left1.size(); c0++) {
			ll c1 = left1.size() - c0;
			ll curI = I + c0 * c1 + (c0 ? left1[left1.size() - c0] : 0) + (c1 ? right0[c1 - 1] : 0);
			ll t0 = c0 + cnt[0];
			ll t1 = c1 + cnt[1];
			// if (c0 == 1) cout << c0 << " " << c1 << " " << t0 << " " << t1 << " " << curI << "::\n";
			ans = min(ans, curI * (y - x) + t0 * t1 * x);
		}
	}

	cout << ans;

	return 0;
}
