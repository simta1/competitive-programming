#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	int n, m;
	cin >> n >> m;

	vector a(n, vector<int>(m));
	for (auto &r : a) for (auto &e : r) cin >> e;

	map<vector<int>, vector<int>> mp;
	for (int i = n - 1; i >= 0; i--) mp[a[i]].push_back(i);

	vector b(n, vector<int>(m));
	for (auto &r : b) for (auto &e : r) cin >> e;

	vector<int> idx(n);
	for (int i = 0; i < n; i++) {
		if (!mp.count(b[i]) || mp[b[i]].empty()) {
			cout << "-1\n";
			return 0;
		}
		idx[i] = mp[b[i]].back();
		mp[b[i]].pop_back();
	}

	vector<int> desc(m);
	for (int i = 0; i + 1 < n; i++) {
		for (int j = 0; j < m; j++) {
			desc[j] += b[i][j] > b[i + 1][j];
		}
	}

	vector<bool> rm(n - 1);
	auto remove = [&](int i) {
		rm[i] = 1;
		for (int j = 0; j < m; j++) {
			if (b[i][j] > b[i + 1][j]) --desc[j];
		}
	};

	vector<int> ans;
	vector<bool> selected(m);
	auto f = [&](int j) {
		ans.push_back(j + 1);
		selected[j] = 1;
		for (int i = 0; i + 1 < n; i++) if (!rm[i]) {
			if (b[i][j] < b[i + 1][j]) remove(i);
		}

	};

	while (1) {
		bool flag = 0;
		for (int j = 0; j < m; j++) if (!selected[j]) {
			if (!desc[j]) {
				flag = 1;
				f(j);
			}
		}
		if (!flag) break;
	}

	for (int i = 0; i + 1 < n; i++) if (!rm[i]) {
		if (idx[i] > idx[i + 1]) {
			cout << -1;
			return 0;
		}
	}

	cout << ans.size() << "\n";
	for (int i = ans.size() - 1; i >= 0; i--) cout << ans[i] << " ";

	return 0;
}
