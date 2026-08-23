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
        if (l > r) return 0;
        T res = 0;
        for (int i = r; i > 0; i -= (i & -i)) res += tree[i];
        for (int i = l - 1; i > 0; i -= (i & -i)) res -= tree[i];
        return res;
    }
};

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n;
    cin >> n;

    string st;
    cin >> st;

    BIT<int> fw(4 * n + 1);
    int offset = n + 1;
    int cnt = 0;
    fw.update(offset, 1);
    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        cnt += st[i - 1] == '1';
        int cur = 4 * cnt - i;
        ans += fw.query(cur - 1 + offset, cur - 1 + offset);
        ans += fw.query(cur + 2 + offset, 4 * n + 1);
        fw.update(cur + offset, 1);
    }
    cout << ans;

    return 0;
}
