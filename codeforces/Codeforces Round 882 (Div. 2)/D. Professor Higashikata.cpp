#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct DSU {
    vector<int> p;
    DSU(int n) : p(n) {
        iota(p.begin(), p.end(), 0);
    }
    int find(int a) {
        while (a != p[a]) a = p[a] = p[p[a]];
        return a;
    }
    void merge(int a, int b) {
        p[find(a)] = find(b);
    }
};

template <typename T>
struct BIT {
    vector<T> tree;
    BIT(int n) : tree(n + 1) {}
    void update(int i, T add) { // 0-based
        ++i;
        for (; i < tree.size(); i += (i & -i)) tree[i] += add;
    }
    T query(int l, int r) { // 0-based
        ++l, ++r;
        if (l > r) return 0;
        T res = 0;
        for (int i = r; i > 0; i -= (i & -i)) res += tree[i];
        for (int i = l - 1; i > 0; i -= (i & -i)) res -= tree[i];
        return res;
    }
};

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n, m, q;
    cin >> n >> m >> q;

    string st;
    cin >> st;

    vector<int> pos(n, -1);
    vector<int> sorted;
    DSU dsu(n);
    while (m--) {
        int l, r;
        cin >> l >> r;
        --l, --r;
        // cout << l << " " << r << "--\n";
        if (~pos[l]) l = dsu.find(l) + 1;
        // cout << l << "---\n";
        for (int i = l; i <= r; i = dsu.find(i) + 1) {
            // cout << i << " " << dsu.find(i) + 1 << "::\n";
            pos[i] = sorted.size();
            sorted.push_back(i);
            if (i) dsu.merge(i - 1, i);
        }
    }

    // for (auto &e : sorted) cout << e << " "; cout << "\n";

    BIT<int> fw(sorted.size());
    int one = 0;
    for (int i = 0; i < n; i++) if (st[i] == '1') {
        ++one;
        if (~pos[i]) fw.update(pos[i], 1);
    }

    while (q--) {
        int x;
        cin >> x;
        --x;
        if (st[x] == '0') {
            if (~pos[x]) fw.update(pos[x], 1);
            ++one;
            st[x] = '1';
        }
        else {
            if (~pos[x]) fw.update(pos[x], -1);
            --one;
            st[x] = '0';
        }
        // for (int i = 0; i < sorted.size(); i++) cout << fw.query(i, i) << " ";
        // cout << "--\n";


        int target = min<int>(sorted.size(), one);
        cout << target - fw.query(0, target - 1) << "\n";
    }

    return 0;
}
