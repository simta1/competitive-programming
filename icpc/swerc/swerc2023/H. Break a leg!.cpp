#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using hh = __int128;

struct P {
	ll x, y;
	P operator-(const P &o) const { return {x - o.x, y - o.y}; }
};
ll cross(P a, P b) {
	return a.x * b.y - a.y * b.x;
}
int ccw(P a, P b, P c) {
	ll cp = cross(b - a, c - a);
	return (cp > 0) - (cp < 0);
}

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	int n;
	cin >> n;

	vector<P> ps(n);
	for (auto &[x, y] : ps) cin >> x >> y;

	hh A = 0, gx = 0, gy = 0;
	for (int i = 0, j = n - 1; i < n; j = i++) {
		ll cp = cross(ps[i], ps[j]);
		A += cp;
		gx += (ps[i].x + ps[j].x) * cp;
		gy += (ps[i].y + ps[j].y) * cp;
	}
	A *= 3; // <= 24e12
	if (A < 0) A *= -1, gx *= -1, gy *= -1;

	auto f = [&](P p) {
		hh x = p.x * A - gx;
		hh y = p.y * A - gy;
		return pair{x, y};
	};

	vector<P> tmp;
	for (auto &p : ps) {
		auto [x, y] = f(p);
		if (x || y) tmp.push_back(p);
	}
	swap(tmp, ps);
	n = ps.size();

	auto cross2 = [&](P a, P b) { // cross(a - g, b - g)
		return A * (cross(a, b)) - (a.x - b.x) * gy + (a.y - b.y) * gx;
	};
	auto half = [&](P p) {
		auto [x, y] = f(p);
		return y < 0 || (y == 0 && x < 0);
	};
	auto cmp = [&](const P &a, const P &b) {
		bool ah = half(a), bh = half(b);
		if (ah != bh) return ah < bh;
		return cross2(a, b) > 0;
	};
	sort(ps.begin(), ps.end(), cmp);

	vector<pair<P, int>> v;
	for (int i = 0, j = 0; i < n; i = j) {
		while (j < n && half(ps[i]) == half(ps[j]) && cross2(ps[i], ps[j]) == 0) ++j;
		v.emplace_back(ps[i], j - i);
	}

	ll s1 = 0, s2 = 0, s3 = 0;
	for (auto [dir, cnt] : v) {
		s3 += s2 * cnt;
		s2 += s1 * cnt;
		s1 += cnt;
	}
	ll ans = s3;

	ll sum = 0, sqsum = 0;
	for (int i = 0, j = 1; i < v.size(); i++) {
		j = max(j, i + 1);
		while (j < i + v.size() && cross2(v[i].first, v[j % v.size()].first) >= 0) {
			ll cnt = v[j % v.size()].second;
			sum += cnt;
			sqsum += cnt * cnt;
			++j;
		}
		ans -= (sum * sum - sqsum) / 2 * v[i].second;
		if (i + 1 < j) {
			ll cnt = v[(i + 1) % v.size()].second;
			sum -= cnt;
			sqsum -= cnt * cnt;
		}
	}
	cout << ans;

	return 0;
}
