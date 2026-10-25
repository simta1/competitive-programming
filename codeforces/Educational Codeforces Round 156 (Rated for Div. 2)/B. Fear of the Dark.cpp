#include <bits/stdc++.h>
using namespace std;
using ll = long long;

using ld = double;
ld dist(int x1, int y1, int x2, int y2) {
	int dx = x2 - x1;
	int dy = y2 - y1;
	return sqrt(dx * dx + dy * dy);
}

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	cout << fixed << setprecision(12);

	int TC;
	for (cin >> TC; TC--;) {
		int px, py, ax, ay, bx, by;
		cin >> px >> py >> ax >> ay >> bx >> by;
		ld ans1 = max(dist(ax, ay, 0, 0), dist(ax, ay, px, py));
		ld ans2 = max(dist(bx, by, 0, 0), dist(bx, by, px, py));
		ld ans3 = max({dist(ax, ay, 0, 0), dist(bx, by, px, py), dist(ax, ay, bx, by) / 2});
		ld ans4 = max({dist(bx, by, 0, 0), dist(ax, ay, px, py), dist(ax, ay, bx, by) / 2});
		cout << min({ans1, ans2, ans3, ans4}) << "\n";
	}

	return 0;
}
