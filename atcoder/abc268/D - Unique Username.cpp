#include <algorithm>
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n, m;
    cin >> n >> m;

    int len = 0;
    vector<string> v(n);
    for (auto &st : v) {
        cin >> st;
        len += st.size();
    }

    unordered_set<string> s;
    while (m--) {
        string st;
        cin >> st;
        s.insert(st);
    }

    int rem = 16 - len - (n - 1);
    auto f = [&](auto &&f, int idx, int cnt, const string &st) -> void {
        if (idx == n) {
            if (st.size() >= 3 && !s.count(st)) {
                cout << st;
                exit(0);
            }
            return;
        }

        if (idx > 0 && cnt < rem) f(f, idx, cnt + 1, st + "_");
        if (idx + 1 < n)  f(f, idx + 1, cnt, st + v[idx] + "_");
        else f(f, idx + 1, cnt, st + v[idx]);
    };

    sort(v.begin(), v.end());
    do {
        f(f, 0, 0, "");
    } while (next_permutation(v.begin(), v.end()));
    cout << -1;

    return 0;
}
