#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	int n;
	cin >> n;

	vector<int> v(n);
	for (auto &e : v) cin >> e;

	if (n > 5000) {
		n = 5000;
		v.resize(n);
	}

	vector<pair<int, int>> pos(5e6 + 1, {-1, -1});
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			int sum = v[i] + v[j];
			if (~pos[sum].first) {
				auto [a, b] = pos[sum];
				if (a == i || a == j || b == i || b == j) continue;
				cout << "YES\n";
				cout << a + 1 << " " << b + 1 << " " << i + 1 << " " << j + 1 << "\n";
				return 0;
			}
			else pos[sum] = {i, j};
		}
	}

	cout << "NO\n";

	return 0;
}
