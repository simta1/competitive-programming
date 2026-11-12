#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	int n, m;
	cin >> n >> m;

	vector<int> v(m);
	for (auto &e : v) cin >> e;

	vector<ll> imos(n + 1);
	for (int i = 1; i < m; i++) {
		auto [a, b] = minmax(v[i - 1], v[i]);
		int d = b - a;
		imos[a] += n - d;
		imos[b] -= n - d;
		if (1 <= a - 1) {
			imos[1] += d;
			imos[a] -= d;
		}
		imos[b] += d;
	}

	for (int i = 1; i <= n; i++) imos[i] += imos[i - 1];

	cout << *min_element(imos.begin() + 1, imos.end());


	return 0;
}
