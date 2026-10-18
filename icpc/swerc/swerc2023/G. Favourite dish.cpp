#include <bits/stdc++.h>
using namespace std;
using ll = long long;

template <typename T>
struct Point {
	T x, y;
	int idx = -1;
	Point() = default;
	Point(T x, T y) : x(x), y(y) {}
	template <typename U> Point(const Point<U> &other) : x(static_cast<T>(other.x)), y(static_cast<T>(other.y)), idx(other.idx) {}
	bool operator<(const Point &o) const { return tie(x, y) < tie(o.x, o.y); }
	bool operator<=(const Point &o) const { return tie(x, y) <= tie(o.x, o.y); }
	bool operator==(const Point &o) const { return tie(x, y) == tie(o.x, o.y); }
	Point operator-(const Point &o) const { return {x - o.x, y - o.y}; }
	friend T cross(const Point &a, const Point &b) {
		return a.x * b.y - a.y * b.x;
	}
	friend int ccw(const Point &p1, const Point &p2, const Point &p3) {
		T cp = cross(p2 - p1, p3 - p1);
		return (cp > 0) - (cp < 0);
	}
	friend bool isBetween(const Point &a, const Point &b, const Point &c) {
		return min(a.x, c.x) <= b.x && b.x <= max(a.x, c.x) && min(a.y, c.y) <= b.y && b.y <= max(a.y, c.y);
	}
};

using P = Point<ll>;
vector<P> upperHull(vector<P> &p) {
	sort(p.begin(), p.end());
	int i = p.size() - 2;
	while (i >= 0 && p[i].x == p.back().x) --i;
	reverse(p.begin() + i + 1, p.end());
	vector<P> h;
	for (auto x : p) {
		while (h.size() >= 2) {
			auto a = h[h.size() - 2], b = h.back();
			int dir = ccw(a, b, x);
			if (dir > 0 || dir == 0 && b.idx > min(a.idx, x.idx)) h.pop_back();
			else break;
		}
		h.push_back(x);
	}
	return h;
}

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	int n, q;
	cin >> n >> q;

	vector<P> ps(n);
	for (int i = 0; i < n; i++) {
		cin >> ps[i].x >> ps[i].y;
		ps[i].idx = i + 1;
	}

	auto u = upperHull(ps);

	while (q--) {
		ll x, y;
		cin >> x >> y;

		auto f = [&](int i) {
			return pair{x * u[i].x + y * u[i].y, -u[i].idx};
		};

		int lo = 0, hi = u.size() - 1;
		while (lo + 2 < hi) {
			int p = (2 * lo + hi) / 3;
			int q = (lo + 2 * hi) / 3;
			if (f(p) < f(q)) lo = p;
			else hi = q;
		}

		auto ans = f(lo);
		for (int i = lo + 1; i <= hi; i++) ans = max(ans, f(i));
		cout << -ans.second << "\n";
	}

	return 0;
}
