#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n, r;
    cin >> n >> r;

    int h = ceil(sqrt(3) * r);
    int w = 2 * r;

    vector<pair<int, int>> v(n);
    for (auto &[x, y] : v) cin >> x >> y;

    mt19937 rng;

    vector<pair<int, int>> ans;
    while (1) {
        int dx = rng() % w;
        int dy = rng() % h;
        ans.clear();
        int cnt = 0;
        for (auto [x, y] : v) {
            int i = (y - dy) / h;
            [&]() {
                for (int ci = i - 2; ci <= i + 2; ci++) {
                    int j = (x - dx - (ci & 1) * r) / w;
                    for (int cj = j - 2; cj <= j + 2; cj++) {
                        int cx = dx + w * cj + (ci & 1) * r;
                        int cy = dy + h * ci;
                        if (ll(x - cx) * (x - cx) + ll(y - cy) * (y - cy) <= ll(r) * r) {
                            ans.emplace_back(cx, cy);
                            ++cnt;
                            return;
                        }
                    }
                }
            }();
        }
        if (cnt * 100 >= n * 89) break;
    }

    sort(ans.begin(), ans.end());
    ans.erase(unique(ans.begin(), ans.end()), ans.end());
    
    cout << ans.size() << "\n";
    for (auto [x, y] : ans) cout << x << " " << y << "\n";

    return 0;
}
