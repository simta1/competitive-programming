#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	int TC;
	for (cin >> TC; TC--;) {
		int n;
		cin >> n;

		vector<int> v(2 * n);
		for (auto &e : v) cin >> e;

		sort(v.begin(), v.end());

		cout << v[n - 1] - v[0] + v[2 * n - 1] - v[n] << "\n";
		for (int i = 0; i < n; i++) {
			cout << v[i] << " " << v[i + n] << "\n";
		}
	}

	return 0;
}
