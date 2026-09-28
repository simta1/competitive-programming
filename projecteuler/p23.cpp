#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    vector<int> primes;
    constexpr int N = 28121;
    static int lpf[N + 1], lpsum[N + 1], sum[N + 1];
    for (int i = 2; i <= N; i++) {
        if (!lpf[i]) {
            lpf[i] = i;
            lpsum[i] = i + 1;
            primes.push_back(i);
            sum[i] = i + 1;
        }
        for (auto p : primes) {
            if (i > N / p) break;
            lpf[i * p] = p;
            if (i % p == 0) {
                lpsum[i * p] = lpsum[i] * p + 1;
                sum[i * p] = sum[i] / lpsum[i] * lpsum[i * p];
                break;
            }
            else {
                lpsum[i * p] = p + 1;
                sum[i * p] = sum[i] * sum[p];
            }
        }
    }

    bitset<N + 2> bs, cur;
    for (int i = 1; i <= N; i++) bs[i] = sum[i] > 2 * i;

    for (int i = 1; i <= N; i++) if (sum[i] > 2 * i) cur |= bs << i;

    ll ans = 0;
    for (int i = 1; i <= N; i++) {
        if (!cur[i]) ans += i;
    }
    cout << ans;

    return 0;
}
