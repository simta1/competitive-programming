#include <bits/stdc++.h>
#define int ll
using namespace std;
using ll = long long;

main() {
	cin.tie(0) -> sync_with_stdio(0);

	int n, k;
	cin >> n >> k;

	vector<array<int, 3>> v(n);
	for (auto &[a, b, c] : v) cin >> a >> b >> c;

	set<array<int, 3>> evt; // {t, i, start}
	for (int i = 0; i < n; i++) evt.insert({v[i][0], i, 1});

	vector<int> ans(n);
	int cur = 0;
	queue<int> q;
	while (!evt.empty()) {
		auto [t, idx, add] = *evt.begin();
		evt.erase(evt.begin());
		if (add > 0) {
			q.push(idx);
		}
		else {
			cur -= v[idx][2];
		}
		while (!q.empty() && cur + v[q.front()][2] <= k) {
			int i = q.front();
			auto [a, b, c] = v[i];
			q.pop();

			cur += c;
			ans[i] = t;
			evt.insert({t + b, i, -1});
		}
	}

	for (int i = 0; i < n; i++) cout << ans[i] << "\n";

	return 0;
}
