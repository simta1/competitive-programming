#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Node {
	int l = -1, r = -1;
	int val = -1, sum, mn, mx;
	int pr, sz = 1;
	bool flip = false;
	bool lazy = 0;
	inline static mt19937 rng;
	Node(bool val) : val(val), sum(val ? 1 : -1), pr(rng()) {
		mn = min(0, sum);
		mx = max(0, sum);
	}
	void apply(bool op_f, bool op_r) {
		if (op_f) {
			swap(l, r);
			flip ^= 1;
			tie(mn, mx) = pair{sum - mx, sum -mn};
		}
		if (op_r) {
			val ^= 1;
			sum *= -1;
			lazy ^= 1;
			tie(mn, mx) = pair{-mx, -mn};
		}
	}
	void push();
	void recalc();
};
vector<Node> tree;
int cnt(int node) { return ~node ? tree[node].sz : 0; }
void Node::push() {
	if (!flip && !lazy) return;
	if (~l) tree[l].apply(flip, lazy);
	if (~r) tree[r].apply(flip, lazy);
	flip = lazy = 0;
}
void Node::recalc() {
	sz = 1;
	sum = 0;
	mn = 0;
	mx = 0;

	if (~l) {
		sz += tree[l].sz;
		sum = tree[l].sum;
		mn = tree[l].mn;
		mx = tree[l].mx;
	}

	sum += val ? 1 : -1;
	mn = min(mn, sum);
	mx = max(mx, sum);

	if (~r) {
		sz += tree[r].sz;
		mn = min(mn, sum + tree[r].mn);
		mx = max(mx, sum + tree[r].mx);
		sum += tree[r].sum;
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
int find(int node, int target) {
	if (!~node) return -1;
	if (target < tree[node].mn || tree[node].mx < target) return -1;
	tree[node].push();
	int l = tree[node].l;
	int r = tree[node].r;
	if (~l) {
		if (tree[l].mn <= target && target <= tree[l].mx) return find(l, target);
		target -= tree[l].sum;
	}
	target -= tree[node].val ? 1 : -1;
	if (target == 0) return cnt(l);
	return cnt(l) + 1 + find(r, target);
}

void f(int cur) {
	if (!~cur) return;
	tree[cur].push();
	f(tree[cur].l);
	cout << tree[cur].val;
	f(tree[cur].r);
}

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	int TC;
	for (cin >> TC; TC--;) {
		tree.clear();
		string st;
		cin >> st;

		int n = st.size();
		int root = -1;
		for (int i = 0; i < n; i++) {
			int node = tree.size();
			tree.emplace_back(st[i] == '1');
			root = merge(root, node);
		}

		for (int i = 0; i < n; i++) {
			auto [a, bc] = split(root, i);
			auto [b, c] = split(bc, 1);
			if (tree[b].val) {
				bc = merge(b, c);
				int idx = find(bc, -1);
				if (!~idx) root = merge(a, bc);
				else {
					auto [x, yz] = split(bc, idx + 1);
					int idx2 = find(yz, 1);
					if (!~idx2) root = merge(a, merge(x, yz));
					else {
						auto [y, z] = split(yz, idx2 + 1);
						int t = merge(x, y);
						tree[t].apply(1, 1);
						root = merge(a, merge(t, z));
					}
				}
			}
			else {
				root = merge(a, merge(b, c));
			}
		}
		f(root);
		cout << "\n";
	}

	return 0;
}
