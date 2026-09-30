#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    vector<int> primes;
    constexpr int N = 1e8 + 1;
    static int lpf[N + 1];
    for (int i = 2; i <= N; i++) {
        if (!lpf[i]) {
            lpf[i] = i;
            primes.push_back(i);
        }
        for (auto p : primes) {
            if (i > N / p) break;
            lpf[i * p] = p;
            if (i % p == 0) break;
        }
    }

    ll ans = 1;
    for (auto p : primes) if (p % 4 == 3) {
        int n = p - 1;
        bool flag = 1;
        for (int d = 2; d <= n / d; d++) if (n % d == 0) {
            int x = d + n / d;
            if (lpf[x] != x) {
                flag = 0;
                break;
            }
        }
        if (flag) ans += n;
    }
    cout << ans;

    return 0;
}
