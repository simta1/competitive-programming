#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct vi {
	pair<int, int> v[11];
	int sz = 0;
};

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	int n, q;
	cin >> n >> q;

	vector v(n + 1, vector<int>(n + 1));
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> v[i][j];
		}
	}

	auto op = [&](const vi &a, bool shift, const vi &b) {
		static vector<int> visited(n * n + 1);
		static int t = 0;

		++t;
		int i = 0, j = 0;
		vi res;
		while (i < a.sz || j < b.sz) {
			pair<int, int> p;
			if (j == b.sz || (i < a.sz && a.v[i].first + shift <= b.v[j].first)) {
				p = a.v[i++];
				p.first += shift;
			}
			else p = b.v[j++];
			if (visited[p.second] != t) {
				visited[p.second] = t;
				res.v[res.sz++] = p;
				if (res.sz >= q + 1) break;
			}
		}
		return res;
	};

	vector dists(n + 1, vector<vi>(n + 1));
	vector<vi> col(n + 1);
	for (int i = 1; i <= n; i++) {
		vi row;
		for (int j = 1; j <= n; j++) {
			vi cur;
			cur.v[cur.sz++] = {0, v[i][j]};
			row = op(row, 1, cur);
			col[j] = op(col[j], 1, cur);
			dists[i][j] = op(op(dists[i - 1][j - 1], 1, col[j]), 0, row);
		}
	}

	vector<int> ans(n + 1);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			vi &ds = dists[i][j];

			int mx = min({
				i,
				j,
				int(ds.sz < q + 1 ? 1e8 : ds.v[q].first)
			});
			++ans[mx];
		}
	}
	for (int i = n - 1; i >= 1; i--) ans[i] += ans[i + 1];
	for (int i = 1; i <= n; i++) cout << ans[i] << "\n";

	return 0;
}
