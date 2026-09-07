#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct DSU {
    vector<int> p;
    DSU(int n) : p(n) {
        iota(p.begin(), p.end(), 0);
    }
    int find(int a) {
        return a == p[a] ? a : p[a] = find(p[a]);
    }
    void merge(int a, int b) {
        p[find(a)] = find(b);
    }
};

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int TC;
    for (cin >> TC; TC--;) {
        int n;
        cin >> n;

        vector<int> a(n + 2), d(n + 2, 2e9);
        for (int i = 1; i <= n; i++) cin >> a[i];
        for (int i = 1; i <= n; i++) cin >> d[i];

        DSU dsu_l(n + 2), dsu_r(n + 2);
        auto die = [&](int idx) {
            int a = dsu_l.find(idx - 1), b = dsu_r.find(idx + 1);
            dsu_l.merge(idx, a);
            dsu_r.merge(idx, b);
        };

        vector<int> cand(n);
        iota(cand.begin(), cand.end(), 1);
        for (int r = 1; r <= n; r++) {
            if (r == 2) {
                // cout << "--";
                // for (auto &e : cand) cout << e << " "; cout << "\n";
            }

            vector<int> v;
            for (auto i : cand) if (i >= 1 && i <= n) {
                if (a[dsu_l.find(i - 1)] + a[dsu_r.find(i + 1)] > d[i]) v.push_back(i);
            }
            cout << v.size() << " ";

            cand.clear();
            for (auto i : v) die(i);
            for (auto i : v) {
                cand.push_back(dsu_l.find(i - 1));
                cand.push_back(dsu_r.find(i + 1));
            }

            // assert(is_sorted(cand.begin(), cand.end()));
            sort(cand.begin(), cand.end());
            cand.erase(unique(cand.begin(), cand.end()), cand.end());
            
        }
        cout << "\n";
    }

    return 0;
}
