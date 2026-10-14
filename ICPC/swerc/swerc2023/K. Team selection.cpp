#include <bits/stdc++.h>
using namespace std;
using ll = long long;

template <typename T>
struct BIT {
	vector<T> tree;
	BIT(int n) : tree(n + 1) {}
	void upd(int i, T add) { // 1-based
		for (; i < tree.size(); i += (i & -i)) tree[i] += add;
	}
	T qry(int l, int r) { // 1-based
		T res = 0;
		for (int i = r; i > 0; i -= (i & -i)) res += tree[i];
		for (int i = l - 1; i > 0; i -= (i & -i)) res -= tree[i];
		return res;
	}
	int kth(T k) { // 1-based
		int n = tree.size() - 1;
		assert(n > 0);
		if (k <= 0) return 0;
		int res = 0;
		for (int i = 1 << __lg(n); i > 0; i >>= 1) {
			if (res + i <= n && tree[res + i] < k) {
				res += i;
				k -= tree[res];
			}
		}
		return res + 1;
	}
};

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	int n;
	cin >> n;

	BIT<int> fw(n);
	for (int i = 1; i <= n; i++) fw.upd(i, 1);

	vector<int> a(n / 2), b(n / 2);
	for (auto &e : a) cin >> e;
	for (auto &e : b) cin >> e;

	vector<int> ans1, ans2;
	for (int i = 0; i < n / 2; i++) {
		int idx = fw.kth(a[i]);
		ans1.push_back(idx);
		fw.upd(idx, -1);
		idx = fw.kth(b[i]);
		ans2.push_back(idx);
		fw.upd(idx, -1);
	}
	for (auto e : ans1) cout << e << " ";
	cout << "\n";
	for (auto e : ans2) cout << e << " ";
	

	return 0;
}
