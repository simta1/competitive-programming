#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	while (1) {
		int n;
		cin >> n;
		if (!n) break;

		vector<array<int, 3>> xs(n), ys(n);
		for (int i = 0; i < n; i++) {
			int x, y;
			cin >> x >> y;
			xs[i] = {x, y, i};
			ys[i] = {y, x, i};
		}
		sort(xs.begin(), xs.end());
		sort(ys.begin(), ys.end());

		vector<array<int, 4>> adj(n, {-1, -1, -1, -1});
		for (int i = 0, j = 0; i < n; i = j) {
			while (j < n && ys[i][0] == ys[j][0]) ++j;
			for (int k = i; k < j; k += 2) {
				int l = ys[k][2];
				int r = ys[k + 1][2];
				adj[l][0] = r;
				adj[r][2] = l;
			}
		}
		for (int i = 0, j = 0; i < n; i = j) {
			while (j < n && xs[i][0] == xs[j][0]) ++j;
			for (int k = i; k < j; k += 2) {
				int d = xs[k][2];
				int u = xs[k + 1][2];
				adj[u][1] = d;
				adj[d][3] = u;
			}
		}

		int cur = 0;
		int d = 0;
		while (!~adj[cur][d]) ++d;

		string ans;
		int cnt = 0;
		string eswn = "ESWN";
		while (ans.size() < n) {
			ans += eswn[d];
			cur = adj[cur][d];
			if (~adj[cur][d + 3 & 3]) {
				d = d + 3 & 3;
				--cnt;
			}
			else {
				d = d + 1 & 3;
				++cnt;
			}
		}
		if (cnt < 0) {
			reverse(ans.begin(), ans.end());
			for (auto &ch : ans) ch = eswn[eswn.find(ch) + 2 & 3];
		}
		cout << ans << "\n";
	}

	return 0;
}
