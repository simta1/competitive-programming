#include <bits/stdc++.h>
using namespace std;
using ll = long long;

constexpr int INF = 2e9;

bool check(const vector<array<int, 4>> &v) {
    int n = v.size();

    vector<int> lens;
    vector<array<int, 3>> hor_add, hor_rm, ver;
    for (int i = 0; i < n; i++) {
        auto [x1, y1, x2, y2] = v[i];
        if (x1 != x2) {
            hor_add.push_back({x1, y1, i});
            hor_rm.push_back({x2, y1, i});
            lens.push_back(x2 - x1);
        }
        else {
            ver.push_back({x1, y1, y2});
            lens.push_back(y2 - y1);
        }
    }

    sort(lens.begin(), lens.end());
    
    int cnt = 0; // 교차점개수
    sort(hor_add.rbegin(), hor_add.rend());
    sort(hor_rm.rbegin(), hor_rm.rend());
    sort(ver.begin(), ver.end());
    set<pair<int, int>> ys;
    for (auto [ver_x, y1, y2] : ver) {
        while (!hor_add.empty() && hor_add.back()[0] <= ver_x) {
            auto [_, y, idx] = hor_add.back();
            hor_add.pop_back();
            ys.emplace(y, idx);
        }
        while (!hor_rm.empty() && hor_rm.back()[0] < ver_x) {
            auto [_, y, idx] = hor_rm.back();
            hor_rm.pop_back();
            ys.erase({y, idx});
        }

        vector<pair<int, int>> cross;
        for (auto it = ys.lower_bound({y1, -INF}); it != ys.end() && it->first <= y2; it++) {
            if (++cnt >= 2 * n) return true;
            int hor_idx = it->second;
            auto [hor_x1, hor_y1, hor_x2, hor_y2] = v[hor_idx];
            cross.emplace_back(hor_x2, hor_y2);
        }

        sort(cross.rbegin(), cross.rend());
        set<pair<int, int>> s;
        for (auto [hor_x, hor_y] : cross) {
            auto it = s.emplace(hor_y, hor_x).first; // 현재 ver_x를 포함하는 수평선들만 보는 중이고, 수평선끼리는 교점이 없으므로 hor_y가 겹치는 경우 없음

            auto check_U = [&](int ver_x2, int hy1, int hy2) {
                auto begin = lower_bound(ver.begin(), ver.end(), array{ver_x2, -INF, -INF});
                auto end = upper_bound(ver.begin(), ver.end(), array{ver_x2, INF, INF});
                auto tmp = upper_bound(begin, end, array{ver_x2, hy1, INF});
                int y1 = hy1;
                int len1 = -1;
                if (tmp != begin) {
                    --tmp;
                    auto [_, ty1, ty2] = *tmp;
                    if (ty2 >= hy1) {
                        len1 = ty2 - ty1;
                        y1 = max(y1, ty2);
                    }
                }
                tmp = upper_bound(begin, end, array{ver_x2, hy2, INF});
                int y2 = hy2;
                int len2 = -1;
                if (tmp != begin) {
                    --tmp;
                    auto [_, ty1, ty2] = *tmp;
                    if (ty2 >= hy2) {
                        len2 = ty2 - ty1;
                        y2 = min(y2, ty1);
                    }
                }
                int need = max(y2 - y1, 0);
                if (need == 0) return true;
                int cnt = lens.end() - lower_bound(lens.begin(), lens.end(), need);
                if (cnt >= 4 + (len1 >= need) + (len2 >= need)) return true;
                need = hy2 - y1;
                cnt = lens.end() - lower_bound(lens.begin(), lens.end(), need);
                if (cnt >= 4 + (len1 >= need)) return true;
                need = y2 - hy1;
                cnt = lens.end() - lower_bound(lens.begin(), lens.end(), need);
                if (cnt >= 4 + (len2 >= need)) return true;
                return false;
            };

            if (it != s.begin()) {
                auto [hor_y2, hor_x2] = *prev(it);
                int len = hor_y - hor_y2;
                if (hor_x - ver_x >= len) {
                    if (check_U(ver_x + len, hor_y2, hor_y)) return true;
                }
            }
            if (next(it) != s.end()) {
                auto [hor_y2, hor_x2] = *next(it);
                int len = hor_y2 - hor_y;
                if (hor_x - ver_x >= len) {
                    if (check_U(ver_x + len, hor_y, hor_y2)) return true;
                }
            }
        }
    }

    return false;
}

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int TC;
    for (cin >> TC; TC--;) {
        int n;
        cin >> n;

        vector<array<int, 4>> v(n);
        for (auto &[x1, y1, x2, y2] : v) cin >> x1 >> y1 >> x2 >> y2;

        bool ans = check(v);
        for (int i = 0; i < 3; i++) {
            for (auto &[x1, y1, x2, y2] : v) {
                tie(x1, y1, x2, y2) = tuple{-y1, x1, -y2, x2};
                if (x1 > x2) swap(x1, x2);
                if (y1 > y2) swap(y1, y2);
            }
            ans |= check(v);
        }

        if (ans) cout << "yes\n";
        else cout << "no\n";
    }

    return 0;
}
