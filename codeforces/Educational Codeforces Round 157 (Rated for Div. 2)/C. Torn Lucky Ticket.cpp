#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	int n;
	cin >> n;

	static int cnt[6][46]{};

	vector<string> v(n);
	for (auto &st : v) {
		cin >> st;

		int sum = 0;
		for (auto ch : st) sum += ch - '0';
		++cnt[st.size()][sum];
	}

	ll ans = 0;
	for (int len = 1; len <= 5; len++) {
		for (int sum = len; sum <= 9 * len; sum++) {
			ll c = cnt[len][sum];
			ans += c * c;
		}
	}

	for (auto st : v) {
		if (st.size() == 3) {
			int a = st[0] - '0', b = st[1] - '0', c = st[2] - '0';
			ans += cnt[1][b + c - a] + cnt[1][a + b - c];
		}
		else if (st.size() == 4) {
			int a = st[0] - '0', b = st[1] - '0', c = st[2] - '0', d = st[3] - '0';
			ans += cnt[2][b + c + d - a] + cnt[2][a + b + c - d];
		}
		else if (st.size() == 5) {
			int a = st[0] - '0', b = st[1] - '0', c = st[2] - '0', d = st[3] - '0', e = st[4] - '0';
			ans += cnt[1][c + d + e - a - b] + cnt[1][a + b + c - d - e];
			ans += cnt[3][b + c + d + e - a] + cnt[3][a + b + c + d - e];
		}
	}
	cout << ans;

	return 0;
}
