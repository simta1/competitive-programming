#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	int TC;
	for (cin >> TC; TC--;) {
		int n, m;
		cin >> n >> m;

		vector<array<int, 3>> a;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				int x;
				cin >> x;
				a.push_back({i, j, x - 1});
			}
		}

		int dim[3] = {0, 1, 2};
		int di = 0, dj = 0, dv = 0;

		string st;
		cin >> st;
		for (auto ch : st) {
			if (ch == 'L') --dj;
			else if (ch == 'R') ++dj;
			else if (ch == 'U') --di;
			else if (ch == 'D') ++di;
			else if (ch == 'I') {
				swap(dj, dv);
				swap(dim[1], dim[2]);
			}
			else {
				swap(di, dv);
				swap(dim[0], dim[2]);
			}
		}

		auto f = [&](int x) {
			x %= n;
			return x < 0 ? x + n : x;
		};

		vector ans(n, vector<int>(n));
		for (auto e : a) {
			int i = e[dim[0]];
			int j = e[dim[1]];
			int v = e[dim[2]];
			ans[f(i + di)][f(j + dj)] = f(v + dv);
		}

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) cout << ans[i][j] + 1 << " ";
			cout << "\n";
		}
	}

	return 0;
}
