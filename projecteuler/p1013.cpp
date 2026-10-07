#include <bits/stdc++.h>
using namespace std;
using ll = long long;

pair<ll, ll> f(ll p, int e) {
    ll pw = 1, sum = 1;
    for (int i = 0; i < e; i++) {
        pw *= p;
        sum += pw;
    }
    return {pw, sum};
}

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    constexpr int N = 1e4;
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

    ll ans = 0;
    for (auto p : {2, 3}) {
        auto [pw, sum] = f(p, 24);
        if (sum % 25 == 0) ans += pw;
    }

    constexpr ll MX = 1e15;
    for (int i = 0; i < primes.size(); i++) {
        for (int j = i + 1; j < primes.size(); j++) {
            ll p = primes[i];
            ll q = primes[j];
            auto [pw, sum] = f(p, 4);
            auto [pw2, sum2] = f(q, 4);
            if (pw > MX / pw2) continue;

            int cnt = 0;
            while (sum % 5 == 0) sum /= 5, ++cnt;
            while (sum2 % 5 == 0) sum2 /= 5, ++cnt;
            if (cnt >= 2) ans += pw * pw2;
        }
    }

    cout << ans << "\n";

    return 0;
}
