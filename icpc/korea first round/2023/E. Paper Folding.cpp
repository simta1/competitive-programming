#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = double;

template <typename T>
struct Point {
    T x, y;
    Point() = default;
    Point(T x, T y) : x(x), y(y) {}
    template <typename U> Point(const Point<U> &other) : x(static_cast<T>(other.x)), y(static_cast<T>(other.y)) {}
    bool operator<(const Point &other) const { return tie(x, y) < tie(other.x, other.y); }
    bool operator<=(const Point &other) const { return tie(x, y) <= tie(other.x, other.y); }
    bool operator==(const Point &other) const { return tie(x, y) == tie(other.x, other.y); }
    Point operator-(const Point &other) const { return {x-other.x, y-other.y}; }
    Point operator+(const Point &p) const { return {x+p.x, y+p.y}; }
    Point operator*(T k) const { return {x*k, y*k}; }
    Point operator/(T k) const { return {x/k, y/k}; }
    friend T dot(Point a, Point b) { return a.x*b.x+a.y*b.y; }
    friend T cross(Point a, Point b) { return a.x*b.y-a.y*b.x; }
    friend int ccw(Point a, Point b, Point c) {
        T v = cross(b-a,c-a);
        return (v>0)-(v<0);
    }
};
Point<ld> footPL(const Point<ld> &p, const Point<ld> &p1, const Point<ld> &p2) {
    auto d = p2 - p1;
    return p1 + d * (dot(p - p1, d) / dot(d, d));
}
Point<ld> reflectPL(const Point<ld> &p, const Point<ld> &p1, const Point<ld> &p2) {
    return footPL(p, p1, p2) * 2 - p;
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

vector<Point<ld>> clipHalfPlane(const vector<Point<ld>> &poly, Point<ld> a, Point<ld> b) { // a->b의 왼쪽만 남김
    vector<Point<ld>> res;
    for (int i = 0, j = poly.size() - 1; i < poly.size(); j = i++) {
        auto p = poly[j], q = poly[i];
        ld s = cross(b - a, p - a), t = cross(b - a, q - a);
        if (s >= 0) res.push_back(p);
        if ((s < 0 && t > 0) || (s > 0 && t < 0)) res.push_back(p + (q - p) * (s / (s - t)));
    }
    return res;
}
vector<Point<ld>> convexIntersection(vector<Point<ld>> a, const vector<Point<ld>> &b) { // O(M(N+M))
    // b는 반시계여야 됨
    if (b.empty()) return {};
    for (int i = 0, j = b.size() - 1; i < b.size(); j = i++) a = clipHalfPlane(a, b[j], b[i]);
    return a;
}

template <typename T>
T polygonArea2(const vector<Point<T>> &polygon) {
    if (polygon.size() <= 2) return 0;
    T res = 0;
    for (int i = 0, j = polygon.size() - 1; i < polygon.size(); j = i++) res += cross(polygon[j], polygon[i]);
    return abs(res);
}

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int w, h;
    cin >> w >> h;

    Point<int> p1, p2;
    cin >> p1.x >> p1.y >> p2.x >> p2.y;

    vector<Point<int>> rect = {{0, 0}, {w, 0}, {w, h}, {0, h}};
    vector<Point<ld>> a = {p1, p2}, b = {p1, p2};
    for (auto p : rect) {
        int dir = ccw(p1, p2, p);
        if (dir > 0) a.push_back(reflectPL(p, p1, p2));
        else if (dir < 0) b.push_back(p);
    }
    auto h1 = getConvexHull(a);
    auto h2 = getConvexHull(b);

    int ans = w * h - polygonArea2(convexIntersection(h1, h2)) / 2;
    cout << ans;

    return 0;
}
