#include <bits/stdc++.h>
using namespace std;
using ll = long long;
constexpr ll MOD = 998'244'353;

tuple<ll, ll, ll> egcd(ll a, ll b) { // ax + by = gcd(a, b)
    if (b == 0) return {1, 0, a};
    auto [x, y, g] = egcd(b, a % b);
    return {y, x - (a / b) * y, g};
}
ll modInv(ll a, ll b) {
    auto [x, y, g] = egcd(a, b); //ax + by = g
    if (g == 1) return (x + b) % b;
    return -1;
} // modInv(n, MOD)

template <typename T>
void add(T &a, T b) {
    a += b;
    if (a >= MOD) a -= MOD;
}

template <typename T>
struct Seg {
    int sz;
    vector<T> tree;
    Seg(int n) {
	sz = 1;
	while (sz < n) sz <<= 1;
	tree.resize(sz << 1);
    }
    void update(int i, T add) { // 0-based
	tree[i |= sz] += add;
	while (i >>= 1) tree[i] += add;
    }
    T query(int l, int r) { // 0-based
	T res = 0;
	for (l |= sz, r |= sz; l <= r; l >>= 1, r >>= 1) {
	    if (l & 1) res += tree[l++];
	    if (~r & 1) res += tree[r--];
	}
	return res;
    }
    int findKth(int node, int s, int e, T k) { // k만 1-based
	if (s == e) return s; // 0-based
	int m = s + e >> 1;
	if (tree[node << 1] >= k) return findKth(node << 1, s, m, k);
	return findKth(node << 1 | 1, m + 1, e, k - tree[node << 1]);
    }
};

int main() {
    cin.tie(0) -> sync_with_stdio(0);
    constexpr ll MOD = 998'244'353;

    int n;
    cin >> n;

    vector<ll> v(n);
    for (auto &e : v) cin >> e;

    auto comp = v;
    sort(comp.begin(), comp.end());
    comp.erase(unique(comp.begin(), comp.end()), comp.end());

    Seg<int> cnt(comp.size());
    Seg<ll> seg(comp.size());

    auto getSum = [&](int k) {
        if (k == 0) return 0LL;
        assert(k <= cnt.tree[1]);
        int idx = cnt.findKth(1, 0, cnt.sz - 1, k);
        int cur = cnt.query(0, idx);
        return seg.query(0, idx) - (cur - k) * comp[idx];
    };

    auto f1 = [&](int a, int n) {
        int b = a - 1;
        return comp[cnt.findKth(1, 0, cnt.sz - 1, b)] * (b - 1) - getSum(b - 1);
    };
    auto f2 = [&](int a, int n) {
        int b = a + 1;
        return getSum(n) - getSum(b) - (n - b) * comp[cnt.findKth(1, 0, cnt.sz - 1, b)];
    };

    for (int i = 1; i <= n; i++) {
        int x = lower_bound(comp.begin(), comp.end(), v[i - 1]) - comp.begin();
        cnt.update(x, 1);
        seg.update(x, comp[x]);

        if (i < 3) continue;

        cout << [&]() {
            int lo = 2, hi = i;
            while (lo + 1 < hi) {
                int mid = lo + hi >> 1;
                if (f1(mid, i) <= f2(mid, i)) lo = mid;
                else hi = mid;
            }
            return min(f2(lo, i), f1(hi, i));
        }() % MOD * modInv(i - 2, MOD) % MOD << "\n";
    }

    return 0;
}
