#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	int n, k;
	cin >> n >> k;

	vector<int> v(n);
	for (auto &e : v) cin >> e;

	vector<int> pfs(n);
	for (int i = 1; i < n; i++) {
		pfs[i] = (v[i - 1] > v[i]) + pfs[i - 1];
	}

	for (int l = 0, r = k - 1; r < n; ++l, ++r) {
		if (pfs[r] - pfs[l] == 0) {
			for (auto e : v) cout << e << " ";
			return 0;
		}
	}

	priority_queue<int, vector<int>, greater<int>> pq, rm;
	for (int i = n - k; i < n; i++) pq.push(v[i]);

	int l = n - k;
	int x = 0;
	while (n - k - x > 0) {
		if (v[n - k - x - 1] > v[n - k - x]) break;

		++x;
		int last = v[n - k - x + k];
		rm.push(last);
		while (!rm.empty() && pq.top() == rm.top()) {
			pq.pop();
			rm.pop();
		}
		if (pq.empty() || v[n - k - 1] < pq.top()) {
			l = n - k - x;
		}
	}

	sort(v.begin() + l, v.begin() + l + k);
	for (auto e : v) cout << e << " ";

	return 0;
}
