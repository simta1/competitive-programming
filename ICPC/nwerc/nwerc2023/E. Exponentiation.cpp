#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n, q;
    cin >> n >> q;

    vector<vector<int>> chd(1);
    vector<int> state(n), rank = {0};
    vector<int> sorted = {0};
    while (q--) {
        char op;
        int i, j;
        cin >> op >> i >> j;
        --i, --j;
        if (op == '!') {
            int a = state[i], b = state[j];
            vector<int> cur = chd[a];
            auto it = lower_bound(cur.begin(), cur.end(), b, [&](int a, int b) {
                return rank[a] > rank[b];
            });
            cur.insert(it, b);
            chd.push_back(cur);
            state[i] = chd.size() - 1;

            auto cmp = [&](int a, int b) {
                const auto &ca = chd[a];
                const auto &cb = chd[b];
                int i = 0, j = 0;
                while (i < ca.size() || j < cb.size()) {
                    if (i < ca.size() && j < cb.size()) {
                        if (rank[ca[i]] < rank[cb[i]]) return true;
                        if (rank[ca[i]] > rank[cb[i]]) return false;
                    }
                    else if (i < ca.size()) return false;
                    else if (j < cb.size()) return true;
                    ++i, ++j;
                }
                return false;
            };
            auto jt = lower_bound(sorted.begin(), sorted.end(), state[i], cmp);
            sorted.insert(jt, state[i]);
            rank.emplace_back();
            rank[sorted[0]] = 0;
            for (int i = 1; i < sorted.size(); i++) rank[sorted[i]] = rank[sorted[i - 1]] + cmp(sorted[i - 1], sorted[i]);
        }
        else {
            int ra = rank[state[i]], rb = rank[state[j]];
            cout << ">=<"[(ra < rb) - (ra > rb) + 1] << "\n";
        }
    }

    return 0;
}
