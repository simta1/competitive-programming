#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int TC;
    for (cin >> TC; TC--;) {
        int n;
        cin >> n;

        vector<int> v(n);
        for (auto &e : v) cin >> e;

        auto comp = v;
        sort(comp.begin(), comp.end());
        comp.erase(unique(comp.begin(), comp.end()), comp.end());
        for (auto &e : v) e = lower_bound(comp.begin(), comp.end(), e) - comp.begin();

        auto check = [&]() {
            vector<bool> used(comp.size());
            for (int i = 0, j = 1; i < v.size(); i = j) {
                while (j < v.size() && v[i] == v[j]) ++j;
                if (used[v[i]]) return false;
                used[v[i]] = true;
            }
            return true;
        };

        vector<vector<pair<int, int> > > poss(comp.size());
        for (int i = 0, j = 1; i < n; i = j) {
            while (j < n && v[i] == v[j]) ++j;
            poss[v[i]].emplace_back(i, j - 1);
        }

        if ([&]() {
            vector<int> candi;
            for (auto &pos : poss) {
                if (pos.size() >= 4) return false;
                if (pos.size() >= 2) {
                    auto [l1, r1] = pos[0];
                    auto [l2, r2] = pos[1];
                    if (l1) candi.push_back(l1 - 1);
                    candi.push_back(l1);
                    candi.push_back(r1);
                    if (r1 + 1 < n) candi.push_back(r1 + 1);
                    if (l2) candi.push_back(l2 - 1);
                    candi.push_back(l2);
                    candi.push_back(r2);
                    if (r2 + 1 < n) candi.push_back(r2 + 1);
                    if (pos.size() >= 3) {
                        auto [l3, r3] = pos[2];
                        if (l3) candi.push_back(l3 - 1);
                        candi.push_back(l3);
                        candi.push_back(r3);
                        if (r3 + 1 < n) candi.push_back(r3 + 1);
                    }
                    break;
                }
            }

            if (candi.empty()) return true;
            assert(candi.size() <= 12);

            for (int i = 0; i < candi.size(); i++) {
                for (int j = i + 1; j < candi.size(); j++) {
                    swap(v[candi[i]], v[candi[j]]);
                    if (check()) return true;
                    swap(v[candi[j]], v[candi[i]]);
                }
            }
            return false;
        }()) cout << "YES\n";
        else cout << "NO\n";
    }

    return 0;
}
