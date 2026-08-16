#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Node {
    int l = -1, r = -1;
    int pr, sz = 1;
    char ch;
    inline static mt19937 rng;
    Node(char ch) : pr(rng()), ch(ch) {}
    void recalc();
};
vector<Node> tree;
int cnt(int node) { return ~node ? tree[node].sz : 0; }
void Node::recalc() { sz = cnt(l) + cnt(r) + 1; }
pair<int, int> split(int node, int k) {
    if (!~node) return {-1, -1};
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
    if (tree[a].pr > tree[b].pr) {
        tree[a].r = merge(tree[a].r, b);
        tree[a].recalc();
        return a;
    }
    tree[b].l = merge(a, tree[b].l);
    tree[b].recalc();
    return b;
}

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n, m;
    cin >> n >> m;

    for (int i = 0; i < n; i++) {
        char c;
        cin >> c;
        tree.emplace_back(c);
    }

    int root = 0;
    for (int i = 1; i < n; i++) root = merge(root, i);

    while (m--) {
        int a, b;
        cin >> a >> b;
        auto [x, x2] = split(root, a - 1);
        auto [y, z] = split(x2, b - a + 1);
        root = merge(merge(x, z), y);
    }

    auto dfs = [&](auto &&dfs, int cur) {
        if (!~cur) return;
        dfs(dfs, tree[cur].l);
        cout << tree[cur].ch;
        dfs(dfs, tree[cur].r);
    };
    dfs(dfs, root);

    return 0;
}
