#include <bits/stdc++.h>
using namespace std;
using ll = long long;

constexpr int INF = 1e8;
int f(int a, int b) {
    if (abs(a - b) <= 1) return a + b;
    return INF;
}

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int TC;
    for (cin >> TC; TC--;) {
        int n;
        string st;
        cin >> n >> st;

        int cnt[2]{};
        for (int i = 0, j = 1; i < n; i = j) {
            while (j < n && st[i] == st[j]) ++j;
            int len = j - i;
            cnt[st[i] - '0'] += len - 1;
        }

        int ans = f(cnt[0], cnt[1]);
        if (st[0] == '0' || st.back() == '0') ans = min(ans, f(cnt[0] + 1, cnt[1]));
        if (st[0] == '0' && st.back() == '0') ans = min(ans, f(cnt[0] + 2, cnt[1]));
        if (st[0] == '1' || st.back() == '1') ans = min(ans, f(cnt[0], cnt[1] + 1));
        if (st[0] == '1' && st.back() == '1') ans = min(ans, f(cnt[0], cnt[1] + 2));
        cout << (ans == INF ? -1 : ans) << "\n";
    }

    return 0;
}
