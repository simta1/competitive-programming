#include <bits/stdc++.h>
using namespace std;
using ll = long long;

vector<ll> getMulFunc(int n) { // O(N)
    vector<ll> func(n + 1);
    func[1] = 1;
    vector<int> primes, lpf(n + 1), lpe(n + 1); // least prime factor, least prime exponent
    for (ll i = 2; i <= n; i++) {
        if (!lpf[i]) {
            lpf[i] = i;
            lpe[i] = 1;
            primes.push_back(i);
            // func[i] = ? // func(p) // i는 소수
            // ex) mu[i] = -1;
            func[i] = i - 1;
        }
        for (auto p : primes) {
            if (i * p > n) break;
            lpf[i * p] = p;
            if (i % p == 0) {
                lpe[i * p] = lpe[i] + 1;
                // func[i * p] = ? // func(i' * p * p) // 소인수 p의 지수 1 증가
                // ex) mu[i * p] = 0;
                func[i * p] = func[i] * p;
                break;
            }
            else {
                lpe[i * p] = 1;
                func[i * p] = func[i] * func[p]; // gcd(i, p) = 1
            }
        }
    }
    return func;
}

constexpr int N = 5e6;
auto phi = getMulFunc(N);

struct Node {
    int val = -1, cnt = 0, sz = 1, mn = 0;
    // void f(int x) {
    //     while (x--) {
    //         if (val == 1) break;
    //         if (mn > 0) {
    //             cnt -= sz;
    //             --mn;
    //         }
    //         else {
    //             if (val == 1) {
    //                 // ㅠㅠ
    //             }
    //             else val = phi[val];
    //         }
    //     }
    // }
};

Node op(const Node &a, const Node &b) {
    if (!~a.val) return b;
    if (!~b.val) return a;
    Node res;
    res.cnt = a.cnt + b.cnt;
    res.sz = a.sz + b.sz;
    int x = a.val;
    int y = b.val;
    int am = a.mn;
    int bm = b.mn;
    while (x != y) {
        if (x > y) {
            x = phi[x];
            res.cnt += a.sz;
            ++am;
        }
        else {
            y = phi[y];
            res.cnt += b.sz;
            ++bm;
        }
    }
    res.val = x;
    res.mn = min(am, bm);
    return res;
}

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n, q;
    cin >> n >> q;

    int sz = 1;
    while (sz < n) sz <<= 1;
    vector<Node> tree(sz << 1);
    vector<int> lazy(sz << 1);
    for (int i = 0; i < n; i++) cin >> tree[sz | i].val;
    for (int i = sz - 1; i > 0; i--) {
        tree[i] = op(tree[i << 1], tree[i << 1 | 1]);
    }
    // auto propagate = [&](int node, int s, int e) {
    //     if (lazy[node]) {
    //         tree[node].f(lazy[node]);
    //         if (s != e) {
    //             lazy[node << 1] += lazy[node];
    //             lazy[node << 1 | 1] += lazy[node];
    //         }
    //         lazy[node] = 0;
    //     }
    // };
    // auto update = [&](auto &&update, int node, int s, int e, int l, int r) {
    //     propagate(node, s, e);
    //     if (l <= s && e <= r) {
    //         lazy[node] = 1;
    //         propagate(node, s, e);
    //         return;
    //     }
    //     if (l > e || s > r) return;
    //     int m = s + e >> 1;
    //     update(update, node << 1, s, m, l, r);
    //     update(update, node << 1 | 1, m + 1, e, l, r);
    //     tree[node] = op(tree[node << 1], tree[node << 1 | 1]);
    // };
    constexpr ll INF = 1e18;
    auto query = [&](auto &&query, int node, int s, int e, int l, int r) {
        // propagate(node, s, e);
        if (l <= s && e <= r) return tree[node];
        if (l > e || s > r) return Node();
        int m = s + e >> 1;
        return op(query(query, node << 1, s, m, l, r), query(query, node << 1 | 1, m + 1, e, l, r));
    };

    auto update = [&](int i) {
        i |= sz;
        tree[i].val = phi[tree[i].val];
        while (i >>= 1) tree[i] = op(tree[i << 1], tree[i << 1 | 1]);
    };

    vector<int> p(n + 1);
    iota(p.begin(), p.end(), 0);
    auto find = [&](int a) {
        while (a != p[a]) a = p[a] = p[p[a]];
        return a;
    };
    auto merge = [&](int a, int b) {
        p[find(a)] = find(b);
    };

    while (q--) {
        int op, l, r;
        cin >> op >> l >> r;
        --l, --r;
        if (op == 1) {
            // update(update, 1, 0, sz - 1, l, r);
            for (int i = find(l); i <= r; i = find(i + 1)) {
                update(i);
                if (tree[i | sz].val == 1) merge(i, i + 1);
            }
        }
        else {
            cout << query(query, 1, 0, sz - 1, l, r).cnt << "\n";
        }
    }

    return 0;
}
