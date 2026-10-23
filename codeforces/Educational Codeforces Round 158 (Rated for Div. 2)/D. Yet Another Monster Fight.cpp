#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	int n;
	cin >> n;

	vector<int> v(n);
	for (auto &e : v) cin >> e;

	auto check = [&](int x) {
		int mx = n, mn = -1;
		for (int i = 0; i < n; i++) {
			if (x < v[i]) return false;
			int l = i, r = n - i - 1;
			bool a = v[i] <= x - l;
			bool b = v[i] <= x - r;
			if (a && b) continue;
			else if (a) mx = min(mx, i); 
			else if (b) mn = max(mn, i);
			else mx = min(mx, i), mn = max(mn, i);
		}
		return mn <= mx;
	};

	int mx = *max_element(v.begin(), v.end());
	int lo = 0, hi = n + mx;
	while (lo + 1 < hi) {
		int mid = lo + hi >> 1;
		if (check(mid)) hi = mid;
		else lo = mid;
	}
	cout << hi;

	return 0;
}
