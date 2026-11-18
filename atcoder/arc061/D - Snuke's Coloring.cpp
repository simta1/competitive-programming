#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	int n, m, k;
	cin >> n >> m >> k;

	map<pair<int, int>, int> mp;
	while (k--) {
		int a, b;
		cin >> a >> b;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				int r = a - i;
				int c = b - j;
				if (r > 0 && c > 0 && r <= n - 2 && c <= m - 2) ++mp[{r, c}];
			}
		}
	}

	static ll ans[10];
	ans[0] = ll(n - 2) * (m - 2) - mp.size();
	for (auto [pos, cnt] : mp) ++ans[cnt];

	for (int i = 0; i < 10; i++) cout << ans[i] << "\n";

	return 0;
}
