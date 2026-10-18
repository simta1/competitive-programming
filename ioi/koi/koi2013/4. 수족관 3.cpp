#include <bits/stdc++.h>
using namespace std;
using ll = long long;

auto getCartesian(const vector<int> &v) { // min // 0-based
	int n = v.size();
	vector<pair<int, int>> chd(n, {-1, -1});
	vector<int> s;
	for (int i = 0; i < n; i++) {
		while (!s.empty() && v[s.back()] > v[i]) {
			chd[i].first = s.back();
			s.pop_back();
		}
		if (!s.empty()) chd[s.back()].second = i;
		s.push_back(i);
	}
	return pair{s[0], chd}; // root, chd
}

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	int n;
	cin >> n;

	vector<pair<int, int>> v(n);
	for (auto &[x, y] : v) cin >> x >> y;

	int k;
	cin >> k;

	vector<int> y, len;
	for (int i = 1; i + 1 < n - 1; i += 2) {
		auto [x1, y1] = v[i];
		auto [x2, y2] = v[i + 1];
		assert(y1 == y2);
		y.push_back(y1);
		len.push_back(x2 - x1);
	}

	n = y.size();
	auto [root, chd] = getCartesian(y);

	vector<int> width(n);
	auto mkt = [&](auto &&mkt, int cur) -> int {
		if (!~cur) return 0;
		auto [l, r] = chd[cur];
		return width[cur] = len[cur] + mkt(mkt, l) + mkt(mkt, r);
	};
	mkt(mkt, root);

	auto dfs = [&](auto &&dfs, int cur, int prvh) -> priority_queue<ll> {
		if (!~cur) return {};

		auto [l, r] = chd[cur];
		auto pq1 = dfs(dfs, l, y[cur]);
		auto pq2 = dfs(dfs, r, y[cur]);
		if (pq1.size() > pq2.size()) swap(pq1, pq2);

		auto &res = pq2;
		while (!pq1.empty()) {
			res.push(pq1.top());
			pq1.pop();
		}

		ll add = ll(y[cur] - prvh) * width[cur];
		if (res.empty()) res.push(add);
		else {
			ll x = res.top();
			res.pop();
			res.push(x + add);
		}
		return res;
	};
	auto pq = dfs(dfs, root, 0);

	ll ans = 0;
	while (!pq.empty() && k) {
		--k;
		ans += pq.top();
		pq.pop();
	}
	cout << ans;

	return 0;
}
