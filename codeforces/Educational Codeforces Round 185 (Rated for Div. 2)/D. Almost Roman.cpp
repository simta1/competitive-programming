#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	int TC;
	for (cin >> TC; TC--;) {
		int n, q;
		string st;
		cin >> n >> q >> st;

		int sum = 0, empty = 0;
		for (int i = 0; i < n; i++) {
			if (st[i] == 'X') sum += 10;
			else if (st[i] == 'V') sum += 5;
			else sum += (i + 1 < n && st[i + 1] != 'I' && st[i + 1] != '?') ? -1 : 1;

			empty += st[i] == '?';
		}

		int inc = 0, same = 0;
		for (int i = 0, j; i < n; i = j) {
			if (st[i] != '?') j = i + 1;
			else {
				j = i + 1;
				while (j < n && st[j] == '?') ++j;
				if (j < n && st[j] != 'I') ++j;

				int len = j - i;
				if (i && st[i - 1] == 'I') ++len;

				inc += len / 2 - (st[j - 1] != '?');
				same += len & 1;
			}
		}

		while (q--) {
			int cx, cv, ci;
			cin >> cx >> cv >> ci;

			int numi = min(empty, ci), numv = 0, numx = 0;
			if (ci < empty) numv = min(empty - ci, cv);
			if (ci + cv < empty) numx = empty - ci - cv;

			int ans = sum;
			ans += numv * 4 + numx * 9;

			int num = numv + numx;
			ans -= min(num, inc) * 2;
			if (inc + same < num) ans += (num - inc - same) * 2;
			cout << ans << "\n";
		}
	}

	return 0;
}
