#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	int n, k;
	cin >> n >> k;

	vector<string> v(n);
	for (int i = 0; i < k; i++) {
		string st;
		cin >> st;
		for (int j = 0; j < n; j++) v[j] += st[j];
	}

	map<string, vector<int>> mp;
	for (int i = n - 1; i >= 0; i--) mp[v[i].substr(1)].push_back(i);

	vector<int> ans(n);
	for (int i = 0; i < n; i++) {
		string pref = v[i].substr(0, k - 1);
		if (mp.count(pref) && !mp[pref].empty()) {
			ans[i] = mp[pref].back();
			mp[pref].pop_back();
		}
		else {
			cout << "NO";
			return 0;
		}
	}

	cout << "YES\n";
	for (auto e : ans) cout << e + 1 << " ";

	return 0;
}
