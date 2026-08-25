#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n;
    cin >> n;

    vector<int> v(n + 1);
    for (int i = 1; i <= n; i++) cin >> v[i];

    vector<vector<int>> chd(n + 1);
    for (int i = 2; i <= n; i++) {
        int p;
        cin >> p;
        chd[p].push_back(i);
    }

    queue<int> q;
    q.push(1);
    vector<int> dep(n + 1);
    vector<ll> sum(n);
    while (!q.empty()) {
        auto cur = q.front();
        q.pop();
        for (auto nxt : chd[cur]) {
            dep[nxt] = dep[cur] + 1;
            sum[dep[nxt]] += v[nxt];
            q.push(nxt);
        }
    }

    for (int i = n - 1; i > 0; i--) {
        if (sum[i] == 0) continue;
        cout << "-+"[sum[i] > 0];
        return 0;
    }

    cout << "-0+"[1 + (v[1] > 0) - (v[1] < 0)];
    return 0;
}
