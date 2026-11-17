#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	int TC;
	for (cin >> TC; TC--;) {
		int n;
		cin >> n;

		if (n <= 3) {
			cout << "-1\n";
			continue;
		}

		vector<int> ans(n + 1);
		iota(ans.begin(), ans.end(), 0);
		swap(ans[1], ans[4]);
		for (int i = 1; i <= n; i++) {
			cout << ans[i] << " ";
		}
		cout << "\n";
	}

	return 0;
}
