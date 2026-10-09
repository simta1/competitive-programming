#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    constexpr int N = 1e7;
    static int lpf[N + 1];
    vector<int> ps;
    for (int i = 2; i <= N; i++) {
        if (!lpf[i]) {
            lpf[i] = i;
            ps.push_back(i);
        }
        for (auto p : ps) {
            if (i > N / p) break;
            lpf[i * p] = p;
            if (i % p == 0) break;
        }
    }

    int k;
    cin >> k;

    int tau = 1;
    int x = abs(k);
    while (x > 1) {
        int p = lpf[x];
        int e = 0;
        while (x % p == 0) {
            ++e;
            x /= p;
        }
        tau *= 2 * e + 1;
    }

    ll cnt = tau + 1 >> 1;
    cout << cnt * 2 << " " << cnt * 2 * 2 * k;

    return 0;
}
