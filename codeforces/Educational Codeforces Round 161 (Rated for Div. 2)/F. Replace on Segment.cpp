#include <bits/stdc++.h>
using namespace std;
using ll = long long;

vector<vector<vector<int>>> dp, dp2;
vector<vector<int>> rpos, lpos;
vector<int> v, nxt, prv;
int n, x;

int f(int l, int r, int c);
int g(int l, int r, int c);

int f(int l, int r, int c) {
    if (v[l] == c) l = nxt[l];
    if (v[r] == c) r = prv[r];
    if (l > r) return 0;

    int &res = dp[l][r][c];
    if (~res) return res;
    res = g(l, r, c) + 1;
    for (int m = l; m < r; m++) res = min(res, f(l, m, c) + f(m + 1, r, c));
    return res;
}

int g(int l, int r, int c) {
    if (v[l] != c) l = rpos[l][c];
    if (v[r] != c) r = lpos[r][c];
    if (l > r) return 0;

    int &res = dp2[l][r][c];
    if (~res) return res;

    res = 1e9;
    for (int d = 0; d < x; d++) if (d != c) res = min(res, f(l, r, d));
    for (int m = l; m < r; m++) res = min(res, g(l, m, c) + g(m + 1, r, c));
    return res;
}

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int TC;
    for (cin >> TC; TC--;) {
        cin >> n >> x;

        v = vector<int>(n);
        for (auto &e : v) cin >> e, --e;

        rpos = vector(n, vector<int>(x, n));
        for (int i = n - 2; i >= 0; i--) {
            rpos[i] = rpos[i + 1];
            rpos[i][v[i + 1]] = i + 1;
        }
        lpos = vector(n, vector<int>(x, -1));
        for (int i = 1; i < n; i++) {
            lpos[i] = lpos[i - 1];
            lpos[i][v[i - 1]] = i - 1;
        }
        nxt = vector<int>(n, n);
        for (int i = n - 2; i >= 0; i--) {
            if (v[i] != v[i + 1]) nxt[i] = i + 1;
            else nxt[i] = nxt[i + 1];
        }
        prv = vector<int>(n, -1);
        for (int i = 1; i < n; i++) {
            if (v[i] != v[i - 1]) prv[i] = i - 1;
            else prv[i] = prv[i - 1];
        }

        dp = vector(n, vector(n, vector<int>(x, -1)));
        dp2 = vector(n, vector(n, vector<int>(x, -1)));
        for (int i = 0; i < n; i++) {
            for (int c = 0; c < x; c++) {
                dp[i][i][c] = v[i] != c;
                dp2[i][i][c] = v[i] == c;
            }
        }

        int ans = n;
        for (int c = 0; c < x; c++) ans = min(ans, f(0, n - 1, c));
        cout << ans << "\n";
    }

    return 0;
}
