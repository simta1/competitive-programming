#include <bits/stdc++.h>
using namespace std;
using ll = long long;

constexpr ll INF = 1e17;
struct Seg {
	int sz;
	vector<ll> tree, lazy;
	Seg(int n) {
		sz = 1;
		while (sz < n) sz <<= 1;
		tree.resize(sz << 1);
		lazy.resize(sz << 1);
	}
	void apply(int node, int s, int e, ll add) {
		tree[node] += add;
		lazy[node] += add;
	}
	void push(int node, int s, int e) {
		if (lazy[node]) {
			int m = s + e >> 1;
			apply(node << 1, s, m, lazy[node]);
			apply(node << 1 | 1, m + 1, e, lazy[node]);
			lazy[node] = 0;
		}
	}
	void upd(int node, int s, int e, int l, int r, ll add) {
		if (l <= s && e <= r) {
			apply(node, s, e, add);
			return;
		}
		if (l > e || s > r) return;
		push(node, s, e);
		int m = s + e >> 1;
		upd(node << 1, s, m, l, r, add);
		upd(node << 1 | 1, m + 1, e, l, r, add);
		tree[node] = min(tree[node << 1], tree[node << 1 | 1]);
	}
	void upd(int l, int r, ll add) { upd(1, 0, sz - 1, l, r, add); }
	ll qry(int node, int s, int e, int l, int r) {
		if (l <= s && e <= r) return tree[node];
		if (l > e || s > r) return INF;
		push(node, s, e);
		int m = s + e >> 1;
		return min(qry(node << 1, s, m, l, r), qry(node << 1 | 1, m + 1, e, l, r));
	}
	ll qry(int l, int r) { return qry(1, 0, sz - 1, l, r); }
};

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	int n;
	cin >> n;

	vector<int> v(n + 1);
	for (int i = 1; i <= n; i++) cin >> v[i];

	Seg seg(n + 1);

	stack<int> desc, inc;
	for (int i = 1; i <= n; i++) {
		while (!desc.empty() && v[desc.top()] <= v[i]) {
			int idx = desc.top();
			desc.pop();
			int pidx = desc.empty() ? 1 : desc.top() + 1;
			seg.upd(pidx - 1, idx - 1, v[i] - v[idx]);
		}
		while (!inc.empty() && v[inc.top()] >= v[i]) {
			int idx = inc.top();
			inc.pop();
			int pidx = inc.empty() ? 1 : inc.top() + 1;
			seg.upd(pidx - 1, idx - 1, v[idx] - v[i]);
		}
		desc.push(i);
		inc.push(i);
		if (i == 1) seg.upd(1, 1, INF);
		else seg.upd(i, i, seg.qry(0, i - 2));
	}
	cout << seg.qry(n, n);

	return 0;
}
