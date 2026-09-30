#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    // n(x+y) = xy
    // (x-n)(y-n)=n^2

    vector<int> primes;
    constexpr int N = 1e7;
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

    for (int i = 1; ; i++) {
        int cur = i, tau = 1;
        while (cur > 1) {
            int p = lpf[cur];
            int e = 0;
            while (cur % p == 0) {
                cur /= p;
                ++e;
            }
            tau *= 2 * e + 1;
        }
        if ((tau + 1) / 2 > 1e3) {
            cout << i;
            return 0;
        }
    }

    return 0;
}
