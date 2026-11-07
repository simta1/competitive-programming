#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	int TC;
	for (cin >> TC; TC--;) {
		int l, r;
		cin >> l >> r;

		int n = r - l + 1;
		if (l > 0 || r < 0) cout << n - 1 << "\n";
		else cout << max(0, abs(l + r) - 1) << "\n";
	}

	return 0;
}
