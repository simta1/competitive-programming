#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Point {
	ll x, y;
	Point operator-(const Point &o) const {
		return {x - o.x, y - o.y};
	}
};
ll cross(Point a, Point b) {
	return a.x * b.y - a.y * b.x;
}
int ccw(Point a, Point b, Point c) {
	ll cp = cross(b - a, c - a);
	return (cp > 0) - (cp < 0);
}

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	int n;
	cin >> n;

	vector<ll> a(n), b(n);
	for (auto &e : a) cin >> e;
	for (auto &e : b) cin >> e;

	int s = 0, e = n - 1;
	int m = s + e >> 1;
	
	vector<Point> hl, hr;
	for (int i = 0; i <= m; i++) {
		Point p = {i, b[i]};
		while (hl.size() >= 2 && ccw(hl[hl.size() - 2], hl.back(), p) >= 0) hl.pop_back();
		hl.push_back(p);
	}
	for (int i = m + 1; i <= e; i++) {
		Point p = {i, a[i]};
		while (hr.size() >= 2 && ccw(hr[hr.size() - 2], hr.back(), p) >= 0) hr.pop_back();
		hr.push_back(p);
	}

	using ld = double;
	ld mx = ld(n - 1) / 2;
	auto f = [&](Point a, Point b) {
		return ld(a.y - b.y) / (a.x - b.x) * (mx - a.x) + a.y;
	};
	auto tangent = [&](Point a, vector<Point> &h) {
		int lo = 0, hi = h.size() - 1;
		while (lo + 2 < hi) {
			int p = (2 * lo + hi) / 3;
			int q = (lo + 2 * hi) / 3;
			if (f(a, h[p]) > f(a, h[q])) hi = q;
			else lo = p;
		}
		ld res = 0;
		for (int i = lo; i <= hi; i++) res = max(res, f(a, h[i]));
		return res;
	};

	vector<ld> pref(n), suf(n);
	for (int i = 0; i <= m; i++) pref[i] = tangent({i, b[i]}, hr);
	for (int i = 1; i <= m; i++) pref[i] = max(pref[i], pref[i - 1]);
	for (int i = m; i >= 0; i--) suf[i] = tangent({i, a[i]}, hr);
	for (int i = m - 1; i >= 0; i--) suf[i] = max(suf[i], suf[i + 1]);

	cout << fixed << setprecision(12);
	for (int i = 0; i <= m; i++) {
		ld ans = pref[i];
		if (i + 1 <= m) ans = max(ans, suf[i + 1]);
		cout << 2 * ans << " ";
	}

	for (int i = m + 1; i <= e; i++) pref[i] = tangent({i, b[i]}, hl);
	for (int i = m + 2; i <= e; i++) pref[i] = max(pref[i], pref[i - 1]);
	for (int i = e; i >= m + 1; i--) suf[i] = tangent({i, a[i]}, hl);
	for (int i = e - 1; i >= m + 1; i--) suf[i] = max(suf[i], suf[i + 1]);

	for (int i = m + 1; i <= e; i++) {
		ld ans = pref[i];
		if (i + 1 <= e) ans = max(ans, suf[i + 1]);
		cout << 2 * ans << " ";
	}

	return 0;
}
