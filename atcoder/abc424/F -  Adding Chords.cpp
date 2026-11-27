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

int op_max(int a, int b) {
	return max(a, b);
}
int e_max() {
	return -1;
}
int op_min(int a, int b) {
	return min(a, b);
}
int e_min() {
	return 1e7;
}


int main() {
	cin.tie(0) -> sync_with_stdio(0);

	int n, q;
	cin >> n >> q;

	Seg<int, op_max, e_max> seg_mx(n);
	Seg<int, op_min, e_min> seg_mn(n);
	while (q--) {
		int a, b;
		cin >> a >> b;
		--a, --b;
		if (a + 1 == b || seg_mx.qry(a + 1, b - 1) < b && seg_mn.qry(a + 1, b - 1) > a) {
			cout << "Yes\n";
			seg_mx.upd(a, b);
			seg_mn.upd(b, a);
		}
		else cout << "No\n";
	}

	return 0;
}
