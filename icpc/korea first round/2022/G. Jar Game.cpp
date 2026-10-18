#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    static int dp[60][100][100][100];
    memset(dp, -1, sizeof(dp));
    auto gdp = [&](auto &&gdp, int k, int a, int b, int c) -> int {
        if (!a && !b && !c) return 0;

        auto &res = dp[k][a][b][c];
        if (~res) return res;

        vector<int> candi;
        if (a) {
            int nval = gdp(gdp, k + 1, max(0, a - k), b, c);
            int add = k & 1 ? min(a, k) : 0;
            candi.push_back(nval + add);
        }
        if (b) {
            int nval = gdp(gdp, k + 1, a, max(0, b - k), c);
            int add = k & 1 ? min(b, k) : 0;
            candi.push_back(nval + add);
        }
        if (c) {
            int nval = gdp(gdp, k + 1, a, b, max(0, c - k));
            int add = k & 1 ? min(c, k) : 0;
            candi.push_back(nval + add);
        }
        return res = k & 1 ? *max_element(candi.begin(), candi.end()) : *min_element(candi.begin(), candi.end());
    };

    int a, b, c;
    cin >> a >> b >> c;

    int f = gdp(gdp, 1, a, b, c);
    int s = a + b + c - f;
    // cout << f << " " << s << "\n";
    if (f > s) cout << "F";
    else if (f < s) cout << "S";
    else cout << "D";

    return 0;
}
