#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	int n, k, t;
	cin >> n >> k >> t;

	vector<int> v(n);
	for (auto &e : v) cin >> e;
	v.push_back(t);

	int last = 0;
	int ans = 0;
	sort(v.begin(), v.end());
	for (auto s : v) {
		if (s > t) break;
		if (last < s) {
			// cout << last << " " << s << "\n";
			ans += (s - last + k - 1) / k;
		}
		last = max(last, s + k);
	}
	cout << ans;

	return 0;
}
