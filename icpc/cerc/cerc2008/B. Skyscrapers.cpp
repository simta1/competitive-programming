#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	int TC;
	for (cin >> TC; TC--;) {
		int n, q;
		cin >> n >> q;

		vector<pair<int, int>> v(n);
		for (int i = 0; i < n; i++) {
			int h;
			cin >> h;
			v[i] = {h, i};
		}

		vector<int> qs(q);
		for (auto &t : qs) cin >> t;

		sort(v.begin(), v.end());
		
		vector<int> ans(q);
		vector<bool> active(n);
		int cnt = 0;
		for (int i = q - 1; i >= 0; i--) {
			while (!v.empty() && v.back().first > qs[i]) {
				int idx = v.back().second;
				v.pop_back();
				// cout << idx << "::\n";
				active[idx] = 1;
				++cnt;
				if (idx && active[idx - 1]) --cnt;
				if (idx + 1 < n && active[idx + 1]) --cnt;
			}
			ans[i] = cnt;
		}
		
		for (auto &e : ans) cout << e << " ";
		cout << "\n";
	}

	return 0;
}
