#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	constexpr int N = 1e6;
	constexpr int MX = 3 * N + 7;
	static bool notp[MX + 1] = {1, 1};
	for (int i = 2; i <= MX; i++) if (!notp[i] && i <= MX / i) {
		for (int j = i * i; j <= 3 * N + 7; j += i) notp[j] = 1;
	}

	static int ans[N + 1]{};
	for (int i = 1; i <= N; i++) ans[i] = ans[i - 1] + !notp[3 * i + 7];

	int TC;
	for (cin >> TC; TC--;) {
		int n;
		cin >> n;
		cout << ans[n] << "\n";
	}

	return 0;
}
