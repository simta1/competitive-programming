#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    string v[7];
    for (auto &st : v) cin >> st;

    int d, h;
    cin >> d >> h;

    int ans = 0;
    for (int mask = 0; mask < 128; mask++) if (__builtin_popcount(mask) == d) {
        priority_queue<int> pq;
        for (int j = 0; j < 24; j++) {
            int cur = 0;
            for (int i = 0; i < 7; i++) if (mask >> i & 1) cur += (v[i][j] == '.');
            pq.push(cur);
        }
        int res = 0;
        for (int _ = h; _--;) {
            res += pq.top();
            pq.pop();
        }
        ans = max(ans, res);
    }
    cout << fixed << setprecision(12) << double(ans) / h / d;
    return 0;
}
