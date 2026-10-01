#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	int TC;
	for (cin >> TC; TC--;) {
		int n, a;
		cin >> n >> a;

		int c1 = 0, c2 = 0;
		while (n--) {
			int x;
			cin >> x;
			if (x < a) ++c1;
			if (x > a) ++c2;
		}

		if (c1 > c2) cout << a - 1 << "\n";
		else cout << a + 1 << "\n";
	}

	return 0;
}
