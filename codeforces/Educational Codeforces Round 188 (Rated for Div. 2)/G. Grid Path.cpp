#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n, m, mod;
    cin >> n >> m >> mod;

    auto f = [&](int i, bool x) {
        return i << 1 | x;
    };

    int N = 2 * m + 1;
    vector a(N, vector<ull>(N));
    for (int i = 0; i < m; i++) {
        for (int x = 0; x < 2; x++) {
            for (int l = (x ? 0 : i); l <= i; l++) {
                for (int r = i; r < m; r++) {
                    for (int i2 = l; i2 <= r; i2++) {
                        ++a[f(i, x)][f(i2, i2 == l)];
                    }
                    ++a[f(i, x)][2 * m];
                }
            }
        }
    }
    a[2 * m][2 * m] = 1;

    using mat = vector<vector<ull>>;
    auto op = [&](const mat &a, const mat &b) {
        mat res(N, vector<ull>(N));
        mat b2(N, vector<ull>(N));
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                b2[j][i] = b[i][j];
            }
        }

        constexpr int B = 16;
        for (int i = 0; i < N; i++) {
            for (int k = 0; k < N; k++) {
                ull sum = 0;
                for (int j1 = 0; j1 < N; j1 += B) {
                    int j2 = min(N - 1, j1 + B - 1);
                    for (int j = j1; j <= j2; j++) {
                        sum += a[i][j] * b2[k][j];
                    }
                    sum %= mod;
                }
                res[i][k] = sum;
            }
        }
        return res;
    };

    mat res(N, vector<ull>(N));
    for (int i = 0; i < res.size(); i++) res[i][i] = 1;
    for (; n; n >>= 1) {
        if (n & 1) res = op(res, a);
        a = op(a, a);
    }

    cout << res[f(0, 1)][2 * m];

    return 0;
}
