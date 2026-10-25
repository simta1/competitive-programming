#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	constexpr ll MOD = 998'244'353;
	constexpr ll P = 998'244'353;
	constexpr int N = 3e5 + 5;
	static ll inv[N + 1] = {1, 1};
	for (int i = 2; i <= N; ++i) inv[i] = inv[P % i] * (P - P / i) % P;

	int n, m;
	cin >> n >> m;
	
	string st;
	cin >> st;

	ll ans = 1;
	for (int i = 0; i < n - 1; i++) {
		if (i && st[i] == '?') ans = ans * i % MOD;
	}

	cout << (st[0] == '?' ? 0 : ans) << "\n";

	while (m--) {
		int i;
		char ch;
		cin >> i >> ch;
		--i;

		if (i && st[i] == '?') ans = ans * inv[i] % MOD;
		st[i] = ch;
		if (i && st[i] == '?') ans = ans * i % MOD;
		cout << (st[0] == '?' ? 0 : ans) << "\n";
	}

	return 0;
}
