#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	int TC;
	for (cin >> TC; TC--;) {
		ll n;
		cin >> n;

		string st = to_string(n);
		sort(st.begin(), st.end());

		int ans = 0;
		for (int i = 2; i <= 9; i++) if (n % i == 0) {
			ll d = n / i;
			string cur = to_string(d);
			sort(cur.begin(), cur.end());
			ans += st == cur;
		}
		cout << ans << "\n";
	}

	return 0;
}
