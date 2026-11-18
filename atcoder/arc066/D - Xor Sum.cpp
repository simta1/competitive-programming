#include <bits/stdc++.h>
using namespace std;
using ll = long long;

constexpr ll MOD = 1e9 + 7;
void add(ll &a, ll b) {
	a += b;
	if (a >= MOD) a -= MOD;
}

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	ll n;
	cin >> n;

	static ll dp[61][2][2][3]{}; // dp[i][x][carry][cmp]
	dp[0][0][0][1] = 1;
	for (int i = 0; i < 60; i++) {
		for (int x = 0; x < 2; x++) {
			for (int carry = 0; carry < 2; carry++) {
				for (int cmp = 0; cmp < 3; cmp++) {
					if (!dp[i][x][carry][cmp]) continue;
					for (int d = 0; d < 3; d++) {
						int a = d >> 1 & 1;
						int nx = d & 1;
						int sum = a + x + carry;
						int ncarry = sum >= 2;
						int digit = sum & 1;
						int ncmp = cmp;
						if (digit < (n >> i & 1)) ncmp = 0;
						else if (digit > (n >> i & 1)) ncmp = 2;
						add(dp[i + 1][nx][ncarry][ncmp], dp[i][x][carry][cmp]);
					}
				}
			}
		}
	}

	cout << (dp[60][0][0][0] + dp[60][0][0][1]) % MOD;

	return 0;
}
