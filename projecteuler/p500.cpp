#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    constexpr int N = 1e7;
    static int lpf[N + 1];
    vector<int> primes;
    for (int i = 2; i <= N; i++) {
        if (!lpf[i]) {
            lpf[i] = i;
            primes.push_back(i);
        }
        for (auto p : primes) {
            if (p > N / i) break;
            lpf[i * p] = p;
            if (i % p == 0) break;
        }
    }

    constexpr ll MOD = 500'500'507;
    int n = 500'500;
    assert(primes.size() >= n);

    priority_queue<int, vector<int>, greater<int>> pq;
    for (auto p : primes) pq.push(p);
    int mx = primes.back();

    ll ans = 1;
    while (n--) {
        auto x = pq.top();
        pq.pop();
        ans = ans * x % MOD;
        if (x <= mx / x) pq.push(x * x);
    }

    cout << ans;

    return 0;
}
