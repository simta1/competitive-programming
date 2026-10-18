#include <bits/stdc++.h>
using namespace std;
using ll = long long;

bool f(const string &a, const string &b) {
	if (a.size() != b.size()) return false;
	int cnt = 0;
	for (int i = 0; i < a.size(); i++) {
		if (a[i] != b[i]) {
			if (++cnt > 1) return false;
		}
	}
	return true;
}

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	int n, m;
	cin >> n >> m;

	vector<string> v(n);
	for (auto &st : v) cin >> st;

	vector<int> ans(n);
	while (m--) {
		string st;
		cin >> st;

		auto it = find(v.begin(), v.end(), st);
		if (it != v.end()) ++ans[it - v.begin()];
		else {
			int idx = -1;
			bool flag = 1;
			for (int i = 0; i < n; i++) {
				if (f(v[i], st)) {
					if (~idx) flag = 0;
					else idx = i;
				}
			}
			if (flag && ~idx) ++ans[idx];
			// else cout << st << "\n";
		}
	}

	for (int i = 0; i < n; i++) cout << ans[i] << "\n";

	return 0;
}
