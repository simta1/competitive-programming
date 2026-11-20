#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Node {
	using elem = pair<int, int>;
	int l = -1, r = -1;
	elem val, mn;
	int pr, sz = 1;
	bool flip = false;
	inline static mt19937 rng;
	Node(elem val) : val(val), mn(val), pr(rng()) {}
	void apply() {
		swap(l, r);
		flip ^= 1;
	}
	void push();
	void recalc();
};
vector<Node> tree;
int cnt(int node) { return ~node ? tree[node].sz : 0; }
void Node::push() {
	if (!flip) return;
	if (~l) tree[l].apply();
	if (~r) tree[r].apply();
	flip = 0;
}
void Node::recalc() {
	sz = 1;
	mn = val;
	if (~l) {
		sz += tree[l].sz;
		mn = min(mn, tree[l].mn);
	}
	if (~r) {
		sz += tree[r].sz;
		mn = min(mn, tree[r].mn);
	}
}
pair<int, int> split(int node, int k) {
	if (!~node) return {-1, -1};
	tree[node].push();
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
		tree[a].push();
		tree[a].r = merge(tree[a].r, b);
		tree[a].recalc();
		return a;
	}
	tree[b].push();
	tree[b].l = merge(a, tree[b].l);
	tree[b].recalc();
	return b;
}
void reverse(int &root, int l, int r) {
	auto [a, bc] = split(root, l);
	auto [b, c] = split(bc, r - l + 1);
	tree[b].apply();
	root = merge(merge(a, b), c);
}
int get_min_idx(int node) { // 0-based
	tree[node].push();
	auto &t = tree[node];
	if (~t.l && tree[t.l].mn == t.mn) return get_min_idx(t.l);
	int lsz = cnt(t.l);
	if (t.val == t.mn) return lsz;
	return lsz + 1 + get_min_idx(t.r);
}

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	int n;
	while (cin >> n && n) {
		tree.clear();
		tree.reserve(n);
		int root = -1;
		for (int i = 0; i < n; i++) {
			int x;
			cin >> x;
			int node = tree.size();
			tree.emplace_back(pair{x, i});
			root = merge(root, node);
		}

		for (int i = 0; i < n; i++) {
			int idx = get_min_idx(root);
			cout << idx + i + 1 << " ";

			auto [a, bc] = split(root, idx);
			auto [b, c] = split(bc, 1);
			if (~a) tree[a].apply();
			root = merge(a, c);
		}
		cout << "\n";
	}

	return 0;
}
