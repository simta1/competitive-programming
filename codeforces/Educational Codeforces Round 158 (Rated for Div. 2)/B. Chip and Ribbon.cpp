#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	int TC;
	for (cin >> TC; TC--;) {
		int n;
		cin >> n;

		vector<int> v(n + 1);
		for (int i = 1; i <= n; i++) cin >> v[i];

		ll ans = 0;
		for (int i = 1; i <= n; i++) ans += max(0, v[i] - v[i - 1]);
		cout << ans - 1 << "\n";
	}

	return 0;
}
