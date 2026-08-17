#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Node {
    int l = -1, r = -1;
    ll sum = 0;
    int pr, sz = 1, val;
    bool flip = false;
    inline static mt19937 rng;
    Node(int val) : sum(val), pr(rng()), val(val) {}
    void recalc();
};
vector<Node> tree;
int cnt(int node) { return ~node ? tree[node].sz : 0; }
void propagate(int node) {
    if (!tree[node].flip) return;
    swap(tree[node].l, tree[node].r);
    if (~tree[node].l) tree[tree[node].l].flip ^= 1;
    if (~tree[node].r) tree[tree[node].r].flip ^= 1;
    tree[node].flip = 0;
}
void Node::recalc() {
    if (~l) propagate(l);
    if (~r) propagate(r);
    sz = cnt(l) + cnt(r) + 1;
    sum = (~l ? tree[l].sum : 0) + (~r ? tree[r].sum : 0) + val;
}
pair<int, int> split(int node, int k) {
    if (!~node) return {-1, -1};
    propagate(node);
    if (cnt(tree[node].l) >= k) {
        auto [a, b] = split(tree[node].l, k);
        tree[node].l = b;
        tree[node].recalc();
        return {a, node};
    }
    auto [a, b] = split(tree[node].r, k - cnt(tree[node].l) - 1);
    tree[node].r = a;
    tree[node].recalc();
    return {node, b};
}
int merge(int a, int b) {
    if (!~a) return b;
    if (!~b) return a;
    propagate(a);
    propagate(b);
    if (tree[a].pr > tree[b].pr) {
        tree[a].r = merge(tree[a].r, b);
        tree[a].recalc();
        return a;
    }
    tree[b].l = merge(a, tree[b].l);
    tree[b].recalc();
    return b;
}
void reverse(int &root, int l, int r) {
    auto [a, bc] = split(root, l);
    auto [b, c] = split(bc, r - l + 1);
    tree[b].flip ^= 1;
    root = merge(merge(a, b), c);
}
ll query(int &root, int l, int r) {
    auto [a, bc] = split(root, l);
    auto [b, c] = split(bc, r - l + 1);
    ll res = tree[b].sum;
    root = merge(merge(a, b), c);
    return res;
}

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n, m;
    cin >> n >> m;

    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        tree.emplace_back(x);
    }
    int root = 0;
    for (int i = 1; i < n; i++) root = merge(root, i);

    while (m--) {
        int op, a, b;
        cin >> op >> a >> b;
        if (op == 1) reverse(root, a - 1, b - 1);
        else {
            cout << query(root, a - 1, b - 1) << "\n";
        }
    }

    return 0;
}
