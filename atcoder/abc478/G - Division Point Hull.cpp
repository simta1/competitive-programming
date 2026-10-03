#include <bits/stdc++.h>
using namespace std;
using ll = long long;

template <typename T>
struct Point {
    T x, y;
    Point() = default;
    Point(T x, T y) : x(x), y(y) {}
    template <typename U> Point(const Point<U> &other) : x(static_cast<T>(other.x)), y(static_cast<T>(other.y)) {}
    bool operator<(const Point &other) const { return tie(x, y) < tie(other.x, other.y); }
    bool operator<=(const Point &other) const { return tie(x, y) <= tie(other.x, other.y); }
    bool operator==(const Point &other) const { return tie(x, y) == tie(other.x, other.y); }
    Point operator-(const Point &other) const { return {x - other.x, y - other.y}; }
    Point operator+(const Point &other) const { return {x + other.x, y + other.y}; }
};
template <typename T>
T crossProduct(const Point<T> &p1, const Point<T> &p2) {
    return (p1.x * p2.y - p2.x * p1.y);
}
template <typename T>
int ccw(const Point<T> &p1, const Point<T> &p2, const Point<T> &p3) { // -1 : 시계, 0 : 일직선, 1 : 반시계
    T cp = crossProduct(p2 - p1, p3 - p1);
    return (cp > 0) - (cp < 0);
}

template <typename T>
vector<Point<T>> getConvexHull(vector<Point<T>> ps) { // O(NlogN)
    sort(ps.begin(), ps.end());
    ps.erase(unique(ps.begin(), ps.end()), ps.end());
    if (ps.empty()) return {};
    sort(ps.begin() + 1, ps.end(), [&](const Point<T> &a, const Point<T> &b) {
        int dir = ccw(ps[0], a, b);
        return dir ? dir > 0 : a < b;
    });
    vector<Point<T>> h;
    for (auto &p : ps) {
        while (h.size() >= 2 && ccw(h[h.size() - 2], h[h.size() - 1], p) <= 0) h.pop_back();
        h.push_back(p);
    }
    return h; // 반시계 방향 정렬된 상태
}

template <typename T>
bool checkQuadrant(const Point<T> &p) {
	return p.y < 0 || (p.y == 0 && p.x < 0); // PI <= atan2(p) < 2 * PI
};

using poly = vector<Point<ll>>;
poly minkowski(const poly &h1, const poly &h2) {
    assert(!h1.empty() && !h2.empty());
    int mn1 = min_element(h1.begin(), h1.end(), [&](const auto &a, const auto &b) {
        return tie(a.y, a.x) < tie(b.y, b.x);
    }) - h1.begin();
    int mn2 = min_element(h2.begin(), h2.end(), [&](const auto &a, const auto &b) {
        return tie(a.y, a.x) < tie(b.y, b.x);
    }) - h2.begin();
    vector<Point<ll>> d1, d2;
    for (int i = 0; i < h1.size(); i++) {
        int idx1 = (mn1 + i) % h1.size();
        int idx2 = (mn1 + i + 1) % h1.size();
        if (h1[idx2] == h1[idx1]) continue;
        d1.push_back(h1[idx2] - h1[idx1]);
    }
    for (int i = 0; i < h2.size(); i++) {
        int idx1 = (mn2 + i) % h2.size();
        int idx2 = (mn2 + i + 1) % h2.size();
        if (h2[idx2] == h2[idx1]) continue;
        d2.push_back(h2[idx2] - h2[idx1]);
    }

    poly res = {h1[mn1] + h2[mn2]};
    merge(d1.begin(), d1.end(), d2.begin(), d2.end(), back_inserter(res), [&](const Point<ll> &a, const Point<ll> &b) {
        bool aq = checkQuadrant(a), bq = checkQuadrant(b);
        return aq != bq ? aq < bq : crossProduct(a, b) > 0;
    });
    for (int i = 1; i < res.size(); i++) res[i] = res[i] + res[i - 1];
    if (res.size() > 1) res.pop_back();
    return res;
}

template <typename T>
T getPolygonAreaDouble(const vector<Point<T>> &polygon) {
    if (polygon.size() <= 2) return 0;
    T res = 0;
    for (int i = 0, j = polygon.size() - 1; i < polygon.size(); j = i++) res += crossProduct(polygon[j], polygon[i]);
    return abs(res);
}

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n;
    cin >> n;

    int p, q;
    cin >> p >> q;

    vector<Point<ll>> v(n);
    for (auto &[x, y] : v) cin >> x >> y;

    auto f = [&](auto &&f, int s, int e) -> vector<Point<ll>> {
        if (s == e) return {};

        int m = s + e >> 1;
        vector<Point<ll>> a, b;
        for (int i = s; i <= m; i++) a.push_back(v[i]);
        for (int i = m + 1; i <= e; i++) b.push_back(v[i]);

        auto h1 = getConvexHull(a);
        auto h2 = getConvexHull(b);
        for (auto &[x, y] : h1) x *= q, y *= q;
        for (auto &[x, y] : h2) x *= p, y *= p;
        auto points = minkowski(h1, h2);
        for (auto p : f(f, s, m)) points.push_back(p);
        for (auto p : f(f, m + 1, e)) points.push_back(p);
        return getConvexHull(points);
    };

    auto a = getPolygonAreaDouble(f(f, 0, n - 1));
    ll b = 2 * (p + q) * (p + q);
    ll g = __gcd(a, b);
    cout << a / g << " " << b / g;

    return 0;
}
