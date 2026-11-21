#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	int n;
	cin >> n;

	vector<int> v(n);
	for (auto &e : v) cin >> e;

	int a = 0, b = n;
	while (a < n && !v[a]) ++a;
	while (b > 0 && !v[b - 1]) --b;

	// cout << a << " " << b << "::\n";
	if (a < b) cout << b - a - 1;
	else cout << 0;

	return 0;
}
