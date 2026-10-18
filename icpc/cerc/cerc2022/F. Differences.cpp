#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n, m, k;
    cin >> n >> m >> k;

    vector<string> v(n);
    for (auto &st : v) cin >> st;

    mt19937 rng;
    vector<unsigned int> w(n);
    for (auto &e : w) e = rng();
    ull tot = accumulate(w.begin(), w.end(), 0ULL);

    vector<array<ull, 4>> sum(m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) sum[j][v[i][j] - 'A'] += w[i];
    }

    for (int i = 0; i < n; i++) {
        ull cur = 0;
        for (int j = 0; j < m; j++) cur += tot - sum[j][v[i][j] - 'A'];
        if (cur == (tot - w[i]) * k) {
            cout << i + 1;
            return 0;
        }
    }
    // P(false positive) <= n / 2^32

    return 0;
}
