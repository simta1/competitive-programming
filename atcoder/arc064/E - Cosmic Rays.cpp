#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	int xs, ys, xt, yt;
	cin >> xs >> ys >> xt >> yt;

	int n;
	cin >> n;

	vector<array<ll, 3>> v(n);
	for (auto &[x, y, r] : v) cin >> x >> y >> r;
	
	v.push_back({xs, ys, 0});
	v.push_back({xt, yt, 0});
	int s = n, t = n + 1;
	n += 2;

	using ld = double;
	vector dist(n, vector<ld>(n));
	for (int i = 0; i < n; i++) {
		for (int j = i; j < n; j++) {
			ll dx = v[i][0] - v[j][0];
			ll dy = v[i][1] - v[j][1];
			dist[i][j] = dist[j][i] = max<ld>(0, sqrt(dx * dx + dy * dy) - v[i][2] - v[j][2]);
		}
	}

	for (int m = 0; m < n; m++) {
		for (int s = 0; s < n; s++) {
			for (int e = 0; e < n; e++) {
				dist[s][e] = min(dist[s][e], dist[s][m] + dist[m][e]);
			}
		}
	}
	cout << fixed << setprecision(12) << dist[s][t];

	return 0;
}
