#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	int n;
	cin >> n;

	vector<int> v(n);
	for (auto &e : v) cin >> e;

	int l;
	cin >> l;

	int lg = __lg(n);
	vector f(n, vector<int>(lg + 1));
	for (int i = 0, j = 0; i < n; i++) {
		while (j + 1 < n && v[j + 1] <= v[i] + l) ++j;
		f[i][0] = j;
	}
	for (int i = n - 1; i >= 0; i--) {
		for (int j = 1; j <= lg; j++) f[i][j] = f[f[i][j - 1]][j - 1];
	}

	int q;
	for (cin >> q; q--;) {
		int a, b;
		cin >> a >> b;
		if (a > b) swap(a, b);
		--a, --b;

		int ans = 0;
		for (int i = lg; i >= 0; i--) {
			if (f[a][i] < b) {
				ans += 1 << i;
				a = f[a][i];
			}
		}
		cout << ans + 1 << "\n";
	}

	return 0;
}
