#include <bits/stdc++.h>
using namespace std;
using ll = long long;

template <typename T>
struct BIT {
    vector<T> tree;
    BIT(int n) : tree(n + 1) {}
    void update(int i, T add) { // 1-based
        for (; i < tree.size(); i += (i & -i)) tree[i] += add;
    }
    T query(int l, int r) { // 1-based
        T res = 0;
        for (int i = r; i > 0; i -= (i & -i)) res += tree[i];
        for (int i = l - 1; i > 0; i -= (i & -i)) res -= tree[i];
        return res;
    }
    int findKth(T k) { // 1-based
        int n = tree.size() - 1;
        assert(n > 0);
        if (k <= 0) return 0;
        int res = 0;
        for (int i = 1 << __lg(n); i > 0; i >>= 1) {
            if (res + i <= n && tree[res + i] < k) {
                res += i;
                k -= tree[res];
            }
        }
        return res + 1;
    }
};

struct DSU {
    vector<int> p;
    DSU(int n) : p(n + 1) {
        iota(p.begin(), p.end(), 0);
    }
    int find(int a) {
        while (p[a] != a) a = p[a] = p[p[a]];
        return a;
    }
    void merge(int a, int b) {
        a = find(a);
        b = find(b);
        if (a > b) swap(a, b);
        p[a] = b;
    }
};

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n;
    cin >> n;

    vector<int> cnt(n);
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        ++cnt[x];
    }

    int used = 0;
    vector<int> ans(n + 1);
    BIT<int> fw(n);
    for (int i = 1; i <= n; i++) fw.update(i, 1);
    DSU dsu(n + 1);
    for (int val = n - 1; val >= 0; val--) if (cnt[val]) {
        int rem = n - used - cnt[val];
        if (rem < val) {
            cout << "No\n";
            return 0;
        }
        int idx = fw.findKth(val + 1);
        // cout << val << " " << idx << "::\n";
        for (int cur = cnt[val]; cur--;) {
            assert(idx <= n);
            // if (idx > n) exit(0);
            ans[idx] = val;
            fw.update(idx, -1);
            dsu.merge(idx, idx + 1);
            idx = dsu.find(idx);
        }
        used += cnt[val];
    }

    cout << "Yes\n";
    for (int i = 1; i <= n; i++) cout << ans[i] << " ";
    return 0;
}
