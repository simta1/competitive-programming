#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    vector<int> primes;
    constexpr int N = 1e5;
    static int lpf[N + 1], lpe[N + 1], tau[N + 1];
    for (int i = 2; i <= N; i++) {
        if (!lpf[i]) {
            lpf[i] = i;
            lpe[i] = 1;
            primes.push_back(i);
            tau[i] = 2;
        }
        for (auto p : primes) {
            if (i > N / p) break;
            lpf[i * p] = p;
            if (i % p == 0) {
                lpe[i * p] = lpe[i] + 1;
                tau[i * p] = tau[i] / (lpe[i] + 1) * (lpe[i] + 2);
                break;
            }
            else {
                lpe[i * p] = 1;
                tau[i * p] = tau[i] * tau[p];
            }
        }
    }

    for (int n = 1; ; n++) {
        int a = n;
        int b = n + 1;
        if (n & 1) b >>= 1;
        else a >>= 1;

        if (tau[a] * tau[b] >= 500) {
            cout << a * ll(b);
            return 0;
        }
    }

    return 0;
}
