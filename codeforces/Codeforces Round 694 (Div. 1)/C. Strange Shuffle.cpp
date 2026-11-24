#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int qry(int i) {
	cout << "? " << i << endl;
	int res;
	cin >> res;
	return res;
}

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	// int n = 19, k = 12;
	// int p = 10;
	// vector<int> v(n, k);
	// for (int _ = 50; _--;) {
	// 	for (auto e : v) cout << setw(2) << e << " ";
	// 	cout << "\n";

	// 	vector<int> nxt(n);
	// 	for (int i = 0; i < n; i++) if (i != p) {
	// 		nxt[(i - 1 + n) % n] += v[i] >> 1;
	// 		nxt[(i + 1) % n] += v[i] + 1 >> 1;
	// 	}
	// 	nxt[(p + 1) % n] += v[p];
	// 	swap(nxt, v);
	// }

	int n, k;
	cin >> n >> k;

	for (int _ = 330; _--;) qry(1);

	int step = min(300, n / 4);
	for (int i = 1; i <= n; i += step) {
		int x = qry(i);
		if (x != k) {
			int dir = x > k ? -1 : 1;
			int lo = 0, hi = n / 2;
			while (lo + 1 < hi) {
				int mid = lo + hi >> 1;
				int idx = (i + mid * dir + n - 1) % n + 1;
				int y = qry(idx);
				if (y == k || (x > k) != (y > k)) hi = mid;
				else lo = mid;
			}
			cout << "! " << (i + hi * dir + n - 1) % n + 1 << endl;
			return 0;
		}
	}

	return 0;
}
