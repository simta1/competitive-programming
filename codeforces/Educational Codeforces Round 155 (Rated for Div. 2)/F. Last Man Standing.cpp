#include <bits/stdc++.h>
using namespace std;
using ll = long long;

template<typename T, T (*op)(T, T), T (*e)()>
struct Seg {
	int sz;
	vector<T> tree;
	Seg(int n) {
		sz = 1;
		while (sz < n) sz <<= 1;
		tree.resize(sz << 1, e());
		// for (int i = 0; i < n; i++) tree[sz | i] = v[i];
		// for (int i = sz - 1; i >= 1; i--) tree[i] = op(tree[i << 1], tree[i << 1 | 1]); 
	}
	void upd(int i, T val) { // 0-based
		tree[i |= sz] = val;
		while (i >>= 1) tree[i] = op(tree[i << 1], tree[i << 1 | 1]);
	}
	T qry(int l, int r) { // 0-based
		if (l > r) return e();
		T resL = e(), resR = e();
		for (l |= sz, r |= sz; l <= r; l >>= 1, r >>= 1) {
			if (l & 1) resL = op(resL, tree[l++]);
			if (~r & 1) resR = op(tree[r--], resR);
		}
		return op(resL, resR);
	}
};

struct Node {
	int mx = 0, mx2 = 0, cnt = 0, idx = -1;
};
Node e() {
	return {0, 0, 0, -1};
}
Node op(Node a, Node b) {
	if (a.mx > b.mx) return {a.mx, max(a.mx2, b.mx), a.cnt, a.idx};
	if (a.mx < b.mx) return {b.mx, max(b.mx2, a.mx), b.cnt, b.idx};
	return {a.mx, max(a.mx2, b.mx2), a.cnt + b.cnt, -1};
}

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	int TC;
	for (cin >> TC; TC--;) {
		int n;
		cin >> n;

		vector<array<int, 3>> v(n); // {a, h, idx}
		for (int i = 0; i < n; i++) cin >> v[i][1];
		for (int i = 0; i < n; i++) cin >> v[i][0];
		for (int i = 0; i < n; i++) v[i][2] = i;
		sort(v.begin(), v.end());

		constexpr int N = 2e5;
		int lb[N + 1]{}, ub[N + 1]{};
		int clb = 0, cub = 0;
		for (int x = 1; x <= N; x++) {
			while (clb < v.size() && v[clb][0] < x) ++clb;
			while (cub < v.size() && v[cub][0] <= x) ++cub;
			lb[x] = clb;
			ub[x] = cub;
		}

		vector<int> hs(n);
		for (int i = 0; i < n; i++) hs[i] = v[i][1];

		Seg<Node, op, e> seg(n);
		for (int i = 0; i < n; i++) seg.upd(i, Node{v[i][1], 0, 1, v[i][2]});

		vector<ll> ans(n);
		for (int x = 1; x <= N; x++) {
			ll mx = 0, mx2 = 0, mxidx = 0;
			int mxcnt = 0;
			for (int s = 1, e = x, ceil = 1; s <= N; s += x, e += x, ++ceil) {
				if (e > N) e = N;
				int l = lb[s], r = ub[e];
				if (l == r) continue;
				--r;

				auto [mxh, mxh2, cnt, idx] = seg.qry(l, r);
				ll val = ceil * ll(mxh);
				if (mx < val) {
					mx2 = max(mx, ceil * ll(mxh2));
					mx = val;
					mxcnt = cnt;
					mxidx = idx;
				}
				else if (mx == val) mxcnt += cnt;
				else mx2 = max(mx2, val);
			}
			if (mxcnt == 1) {
				ans[mxidx] = max(ans[mxidx], mx - mx2);
			}
		}

		for (auto e : ans) cout << e << " ";
		cout << "\n";
	}

	return 0;
}
