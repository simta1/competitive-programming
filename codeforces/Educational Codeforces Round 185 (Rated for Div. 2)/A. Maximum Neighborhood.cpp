#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
	cin.tie(0) -> sync_with_stdio(0);
    constexpr array<pair<int, int>, 4> dpos = {{
        {-1, 0}, {0, -1}, {1, 0}, {0, 1}
    }};

	int TC;
	for (cin >> TC; TC--;) {
		int n;
		cin >> n;

		auto f = [&](int i, int j) {
			return n * i + j + 1;
		};

		int ans = 0;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				int cur = f(i, j);
				for (auto [di, dj] : dpos) {
					int ni = i + di;
					int nj = j + dj;
					if (ni >= 0 && ni < n && nj >= 0 && nj < n) cur += f(ni, nj);
				}
				ans = max(ans, cur);
			}
		}

		cout << ans << "\n";
	}

	return 0;
}
