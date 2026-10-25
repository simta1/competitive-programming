#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	constexpr ll MOD = 998'244'353;

	constexpr int N = 2'000'005;
	static ll fac[N + 1] = {1};
	for (int i = 1; i <= N; i++) fac[i] = fac[i - 1] * i % MOD;

	int TC;
	for (cin >> TC; TC--;) {
		string st;
		cin >> st;

		int ans = 0;
		ll ans2 = 1;
		int n = st.size();
		for (int i = 0, j = 0; i < n; i = j) {
			while (j < n && st[i] == st[j]) ++j;
			ans += j - i - 1;
			ans2 = ans2 * (j - i) % MOD;
		}

		cout << ans << " " << ans2 * fac[ans] % MOD << "\n";
	}

	return 0;
}
