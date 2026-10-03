#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    // constexpr int N = 50;
    // int g[N + 1];
    // g[0] = 0;
    // for (int i = 1; i <= N; i++) {
    //     bitset<N + 5> bs;
    //     for (int j = 0; j < i; j++) {
    //         if (__gcd(i, j) == 1) bs[g[j]] = 1;
    //     }
    //     g[i] = (~bs)._Find_first();
    // }
    // for (int i = 1; i <= N; i++) cout << i << " " << g[i] << "\n";

    constexpr int N = 1e7;
    vector<int> primes;
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

    static int g[N + 1];
    g[3] = 2;
    for (int i = 2; i < primes.size(); i++) {
        int curp = primes[i];
        int prvp = primes[i - 1];
        g[curp] = g[prvp] + 1;
    }

    g[1] = 1;
    for (int i = 3; i <= N; i++) if (lpf[i] != i) g[i] = g[lpf[i]];

    int TC;
    for (cin >> TC; TC--;) {
        int n;
        cin >> n;

        int sum = 0;
        while (n--) {
            int x;
            cin >> x;
            sum ^= g[x];
        }
        if (sum) cout << "Alice\n";
        else cout << "Bob\n";
    }

    return 0;
}
