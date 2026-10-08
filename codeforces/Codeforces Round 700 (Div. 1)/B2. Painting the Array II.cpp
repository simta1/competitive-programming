#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n;
    cin >> n;

    vector<int> v(n);
    for (auto &e : v) cin >> e;

    vector<int> last(n + 1, n), npos(n + 1);
    for (int i = n - 1; i >= 0; i--) {
        npos[i] = last[v[i]];
        last[v[i]] = i;
    }

    int ans = 0;
    int a = 0, b = 0;
    vector<int> nxt(n + 1, n);
    for (int i = 0; i < n; i++) {
        if (a != v[i] && b != v[i]) {
            if (nxt[a] > nxt[b]) a = v[i];
            else b = v[i];
            ++ans;
        }
        nxt[v[i]] = npos[i];
    }

    cout << ans;

    return 0;
}
