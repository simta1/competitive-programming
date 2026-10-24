#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	int TC;
	for (cin >> TC; TC--;) {
		int x, y, k;
		cin >> x >> y >> k;
		if (x < y) cout << y + max(0, y - x - k) << "\n";
		else cout << x << "\n";
	}

	return 0;
}
