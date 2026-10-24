#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	int n;
	cin >> n;

	vector<int> v(n);
	for (int i = 1; i < n; i++) {
		cin >> v[i];
		v[i] ^= v[i - 1];
	}
	// for (auto e : v) cout << e << " ";

	int x = 0;
	for (int i = 30; i >= 0; i--) {
		int cnt[2]{};
		for (auto e : v) ++cnt[e >> i & 1];
		// cout << cnt[0] << " " << cnt[1] << "::\n";
		if (cnt[0] < cnt[1]) x |= 1 << i;
	}
	for (auto e : v) cout << (e ^ x) << " ";

	return 0;
}
