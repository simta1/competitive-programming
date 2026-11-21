#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	int n, idx;
	cin >> n >> idx;

	vector<int> v(n);
	for (auto &e : v) cin >> e;

	int l = 0, r = n - 1;
	while (l <= n && v[l]) ++l;
	while (r >= 0 && v[r]) --r;

	int ans = 0;
	if (l <= idx - 1) {
		for (int i = l; i <= idx - 1; i++) {
			ans += v[i];
		}
		ans += idx - l;
	}

	if (idx <= r) {
		for (int i = r; i >= idx; i--) {
			ans += v[i];
		}
		ans += r - idx + 1;
	}

	cout << ans;

	return 0;
}
