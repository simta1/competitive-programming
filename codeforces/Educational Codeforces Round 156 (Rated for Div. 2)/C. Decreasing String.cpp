#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	int TC;
	for (cin >> TC; TC--;) {
		string st;
		cin >> st;

		ll x;
		cin >> x;

		int len = st.size();
		int cnt = 0;
		while (x > len) {
			x -= len;
			++cnt;
			--len;
		}
		// cout << cnt << " " << x << "::\n";

		string ans;
		for (int i = 0; i < st.size(); i++) {
			while (cnt && !ans.empty() && ans.back() > st[i]) {
				ans.pop_back();
				--cnt;
			}
			ans += st[i];
		}
		cout << ans[x - 1];
	}

	return 0;
}
