#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	int TC;
	for (cin >> TC; TC--;) {
		int n;
		cin >> n;

		vector<ll> a(n), b(n);
		for (auto &e : a) cin >> e;
		for (auto &e : b) cin >> e;
		ll mn = *min_element(a.begin(), a.end());
		ll mn2 = *min_element(b.begin(), b.end());
		cout << min(mn * n + accumulate(b.begin(), b.end(), 0LL), mn2 * n + accumulate(a.begin(), a.end(), 0LL)) << "\n";
	}

	return 0;
}
