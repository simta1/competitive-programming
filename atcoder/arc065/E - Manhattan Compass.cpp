#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct DSU {
	vector<int> p;
	DSU(int n) : p(n) {
		iota(p.begin(), p.end(), 0);
	}
	int find(int a) {
		return a == p[a] ? a : p[a] = find(p[a]);
	}
	void merge(int a, int b) {
		p[find(a)] = find(b);
	}
};

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	int n, a, b;
	cin >> n >> a >> b;

	set<array<ll, 3>> sx, sy;
	vector<pair<ll, ll>> vx, vy;
	vector<pair<ll, ll>> v(n);
	for (int i = 0; i < n; i++) {
		ll x, y;
		cin >> x >> y;
		tie(x, y) = pair{x + y, x - y};
		sx.insert({x, y, i});
		sy.insert({y, x, i});
		v[i] = {x, y};
		vx.emplace_back(x, y);
		vy.emplace_back(y, x);
	}
	sort(vx.begin(), vx.end());
	sort(vy.begin(), vy.end());
	

	--a, --b;
	ll d = max(abs(v[a].first - v[b].first), abs(v[a].second - v[b].second));
	
	vector<bool> visited(n);
	queue<int> q;
	q.push(a);
	visited[a] = 1;

	auto osx = sx, osy = sy;
	while (!q.empty()) {
		auto cur = q.front();
		q.pop();
		auto [x, y] = v[cur];
		for (auto tx : {x - d, x + d}) {
			auto it = sx.lower_bound({tx, y - d, -1});
			while (it != sx.end()) {
				auto [nx, ny, nxt] = *it;
				if (nx == tx && ny <= y + d) {
					if (!visited[nxt]) {
						visited[nxt] = 1;
						q.push(nxt);
					}
					it = sx.erase(it);
				}
				else break;
			}
		}
		for (auto ty : {y - d, y + d}) {
			auto it = sy.lower_bound({ty, x - d, -1});
			while (it != sy.end()) {
				auto [ny, nx, nxt] = *it;
				if (ny == ty && nx <= x + d) {
					if (!visited[nxt]) {
						visited[nxt] = 1;
						q.push(nxt);
					}
					it = sy.erase(it);
				}
				else break;
			}
		}
	}

	ll ans = 0;
	constexpr int INF = 1e8;
	for (int i = 0; i < n; i++) if (visited[i]) {
		auto [x, y] = v[i];
		ans += upper_bound(vx.begin(), vx.end(), pair{x - d, y + d}) - lower_bound(vx.begin(), vx.end(), pair{x - d, y - d});
		ans += upper_bound(vx.begin(), vx.end(), pair{x + d, y + d}) - lower_bound(vx.begin(), vx.end(), pair{x + d, y - d});
		ans += upper_bound(vy.begin(), vy.end(), pair{y - d, x + d - 1}) - lower_bound(vy.begin(), vy.end(), pair{y - d, x - d + 1});
		ans += upper_bound(vy.begin(), vy.end(), pair{y + d, x + d - 1}) - lower_bound(vy.begin(), vy.end(), pair{y + d, x - d + 1});
	}
	cout << ans / 2;

	return 0;
}
