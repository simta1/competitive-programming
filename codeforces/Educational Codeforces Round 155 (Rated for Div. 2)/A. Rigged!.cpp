#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	int TC;
	for (cin >> TC; TC--;) {
		int n;
		cin >> n;

		vector<pair<int, int>> v(n);
		for (auto &[s, e] : v) cin >> s >> e;
		int w = v[0].first;
		bool flag = 1;
		for (int i = 1; i < n; i++) if (v[i].first >= w && v[i].second >= v[0].second) flag = 0;
		if (flag) cout << w << "\n";
		else cout << "-1\n";
	}

	return 0;
}
