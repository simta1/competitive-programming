#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int A, B, C, D, E, F, G, H;
    cin >> A >> B >> C >> D >> E >> F >> G >> H;

    int ans = 0;

    int v[16]{};
    bool used[14]{};
    auto dfs = [&](auto &&dfs, int cur) {
        if (cur == 3) {
            int d = v[3] = E - v[0] - v[1] - v[2];
            if (d < 1 || d > 13 || used[d]) return;
            int h = v[7] = D - d;
            if (h < 1 || h > 13 || used[h] || d == h) return;
            used[d] = used[h] = 1;
            dfs(dfs, 4);
            used[d] = used[h] = 0;
        }
        else if (cur == 6) {
            int g = v[6] = F - v[4] - v[5] - v[7];
            if (g < 1 || g > 13 || used[g]) return;
            int k = v[10] = C - v[2] - g;
            if (k < 1 || k > 13 || used[k]) return;
            used[g] = used[k] = 1;
            dfs(dfs, 8);
            used[g] = used[k] = 0;
        }
        else if (cur == 9) {
            int j = v[9] = G - v[8] - v[10];
            if (j < 1 || j > 13 || used[j]) return;
            int l = v[12] = A - v[0] - v[4] - v[8];
            if (l < 1 || l > 13 || used[l]) return;
            int m = v[13] = B - v[1] - v[5] - v[9];
            if (m < 1 || m > 13 || used[m]) return;
            ans += (j != l && l != m && j != m && H == l + m);
        }
        else {
            for (int i = 1; i <= 13; i++) if (!used[i]) {
                used[i] = 1;
                v[cur] = i;
                dfs(dfs, cur + 1);
                used[i] = 0;
            }
        }
    };
    dfs(dfs, 0);
    cout << ans;

    return 0;
}
