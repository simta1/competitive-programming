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
};

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	int TC;
	for (cin >> TC; TC--;) {
		int n;
		cin >> n;

		set<int> s;
		for (int i = 1; i < n; i++) s.insert(i);
		vector<int> v(n + 1, n + 1);
		vector<array<int, 3>> evt;
		vector<pair<int, int>> qs;
		for (int i = 2; i <= n; i++) {
			int l, r;
			cin >> l >> r;
			auto it = s.lower_bound(l);
			while (it != s.end() && *it <= r) {
				v[*it] = i;
				it = s.erase(it);
			}
			qs.emplace_back(r, l);
		}

		for (int i = 1; i < n; i++) {
			evt.push_back({i, i, 1});
			evt.push_back({v[i], i, -1});
		}
		sort(evt.begin(), evt.end());
		sort(qs.begin(), qs.end());
		int ei = 0;
		BIT<int> fw(n);
		ll ans = 0;
		for (auto [r, l] : qs) {
			while (ei < evt.size() && evt[ei][0] <= r) {
				auto [t, idx, add] = evt[ei++];
				fw.upd(idx, add);
			}
			ans += fw.qry(l, n);
		}
		cout << ans << "\n";
	}

	return 0;
}
