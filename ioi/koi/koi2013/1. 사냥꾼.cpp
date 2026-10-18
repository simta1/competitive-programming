#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	int n, m, l;
	cin >> n >> m >> l;

	vector<int> v(n);
	for (auto &e : v) cin >> e;
	sort(v.begin(), v.end());
	
	int ans = 0;
	while (m--) {
		int x, y;
		cin >> x >> y;

		int a = x - y, b = x + y;
		// b - l <= x <= a + l
		ans += upper_bound(v.begin(), v.end(), a + l) > lower_bound(v.begin(), v.end(), b - l);
	}
	cout << ans;

	return 0;
}
