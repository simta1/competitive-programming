#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Sqdc {
    vector<int> val, sum;
    static constexpr int B =  447;
    Sqdc(int n) : val(n), sum(n / B + 5) {}
    void upd(int i, int add) {
        val[i] += add;
        sum[i / B] += add;
    }
    int qry(int l, int r) {
        int res = 0;
        while (l <= r && l % B) res += val[l++];
        while (l + B - 1 <= r) {
            res += sum[l / B];
            l += B;
        }
        while (l <= r) res += val[l++];
        return res;
    }
};

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n, p, q;
    cin >> n >> p >> q;

    int w, h;
    cin >> w >> h;

    vector<pair<int, int>> vx(n, {-1, -1}), vy(n, {-1, -1});
    vector<int> cs;
    for (int i = 0; i < p; i++) {
        int x, y, c;
        cin >> x >> y >> c;
        --x, --y;
        cs.push_back(c);
        vx[x] = {y, c};
        vy[y] = {x, c};
    }

    sort(cs.begin(), cs.end());
    cs.erase(unique(cs.begin(), cs.end()), cs.end());

    for (auto &[y, c] : vx) if (~y) c = lower_bound(cs.begin(), cs.end(), c) - cs.begin();
    for (auto &[x, c] : vy) if (~x) c = lower_bound(cs.begin(), cs.end(), c) - cs.begin();

    vector<array<int, 5>> qs(q);
    for (int i = 0; i < q; i++) {
        auto &[x, y, mn, mx, idx] = qs[i];
        cin >> x >> y >> mn >> mx;
        --x, --y;
        idx = i;
    }

    int sqr = sqrt(n);
    sort(qs.begin(), qs.end(), [&](auto &a, auto &b) {
        if (a[0] / sqr != b[0] / sqr) return a[0] < b[0];
        return (a[0] / sqr & 1) ? a[1] > b[1] : a[1] < b[1];
    });

    vector<int> cnt(cs.size());
    Sqdc sqdc(p + 1);
    auto upd = [&](int c, int add) {
        if (cnt[c]) sqdc.upd(cnt[c], -1);
        cnt[c] += add;
        if (cnt[c]) sqdc.upd(cnt[c], 1);
    };

    vector<int> ans(q);
    auto [cx, cy, mn, mx, idx] = qs[0];
    for (int i = 0; i <= w; i++) {
        auto [y, c] = vx[cx + i];
        if (cy <= y && y <= cy + h) upd(c, 1);
    }
    ans[idx] = sqdc.qry(mn, mx);

    auto addx = [&](int x, int add) {
        auto [y, c] = vx[x];
        if (cy <= y && y <= cy + h) upd(c, add);
    };
    auto addy = [&](int y, int add) {
        auto [x, c] = vy[y];
        if (cx <= x && x <= cx + w) upd(c, add);
    };

    for (int i = 1; i < q; i++) {
        auto [x, y, mn, mx, idx] = qs[i];
        while (cx > x) {
            addx(cx + w, -1);
            addx(--cx, 1);
        }
        while (cx < x) {
            addx(cx, -1);
            addx(++cx + w, 1);
        }
        while (cy > y) {
            addy(cy + h, -1);
            addy(--cy, 1);
        }
        while (cy < y) {
            addy(cy, -1);
            addy(++cy + h, 1);
        }
        ans[idx] = sqdc.qry(mn, mx);
    }

    for (int i = 0; i < q; i++) cout << ans[i] << "\n";

    return 0;
}
