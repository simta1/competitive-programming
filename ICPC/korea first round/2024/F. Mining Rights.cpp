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
bool checkIntersect(const Point<T> &p1, const Point<T> &p2, const Point<T> &p3, const Point<T> &p4) {
    int a = ccw(p1, p2, p3) * ccw(p1, p2, p4);
    int b = ccw(p3, p4, p1) * ccw(p3, p4, p2);

    if (a > 0 || b > 0) return false;
    if (a < 0 || b < 0) return true;
    return min(p1, p2) <= max(p3, p4) && min(p3, p4) <= max(p1, p2);
}

using ld = double;
using P = Point<ld>;
const ld PI = acos(-1);
P f() {
    int i;
    cin >> i;
    ld theta = ld(i) / 3600 * 2 * PI;
    return {1000 * cos(theta), 1000 * sin(theta)};
}

P g() {
    int i, len;
    cin >> i >> len;
    ld theta = ld(i) / 3600 * 2 * PI;
    return {len * cos(theta), len * sin(theta)};
}

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n;
    cin >> n;

    vector<pair<P, P>> v(n);
    for (auto &[a, b] : v) a = f(), b = f();
    P p1 = g(), p2 = g();

    bool ans = 1;
    for (auto [a, b] : v) ans ^= checkIntersect(p1, p2, a, b);

    if (ans) cout << "YES\n";
    else cout << "NO\n";

    return 0;
}
