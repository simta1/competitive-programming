#include <bits/stdc++.h>
using namespace std;
using ll = long long;

template <typename T, T mod>
class Stirling2 {
private:
    vector<vector<T> > dp;

public:
    Stirling2(int maxN, int maxK) : dp(maxN + 1, vector<T>(maxK + 1, -1)) {}
    Stirling2(int maxN) : Stirling2(maxN, maxN) {}

    T operator()(int n, int k) {
        if (k < 0 || n < 0) return 0;
        if (!n) return !k;
        
        T &res = dp[n][k];
        if (~res) return res;

        return res = ((*this)(n - 1, k - 1) + k * (*this)(n - 1, k) % mod) % mod;
    }

    T bell(int n) {
        T res = 0;
        for (int k = 1; k <= n; k++) res = (res + (*this)(n, k)) % mod;
        return res;
    }
};

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	constexpr ll MOD = 998'244'353;

	constexpr int N = 5e3;
	static ll dp[N + 1] = {0, 0, 1, 1, 1};
	for (int i = 5; i <= N; i++) {
		dp[i] = dp[i - 2] + dp[i - 3];
		if (dp[i] >= MOD) dp[i] -= MOD;
	}

	Stirling2<ll, MOD> st2(N);
	static ll bell[N + 1];
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= i; j++) bell[i] += st2(i, j);
		bell[i] %= MOD;
	}

	int TC;
	for (cin >> TC; TC--;) {
		int n;
		cin >> n;

		string st;
		cin >> st;

		int ans = n;
		ll ans2 = 1;
		int cnt[2]{};
		for (int i = 0, j = 0; i < n; i = j) {
			while (j < n && (i + j & 1) == (st[i] != st[j])) ++j;
			int len = j - i;
			if (len >= 2) {
				ans += len;
				ans2 = ans2 * dp[len] % MOD;
			}
			else ++cnt[st[i] - '0'];
		}

		// cout << ans2 << "::\n";
		if (cnt[0]) ans2 = ans2 * bell[cnt[0]] % MOD;
		if (cnt[1]) ans2 = ans2 * bell[cnt[1]] % MOD;

		cout << ans << " " << ans2 << "\n";
	}

	return 0;
}
