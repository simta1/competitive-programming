#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	int TC;
	for (cin >> TC; TC--;) {
		int n;
		cin >> n;

		vector<int> v(n), pos(n + 1, -1);
		for (int i = 0; i < n; i++) {
			cin >> v[i];
			--v[i];
			pos[v[i]] = i;
		}

		string ans(n, 'a');
		if ([&]() {
			for (int i = 1; i < n; i++) {
				int pidx = v[i - 1], idx = v[i];
				int add = 0;
				if (pos[pidx + 1] > pos[idx + 1]) add = 1;
				if (add && ans[pidx] == 'z') return false;
				ans[idx] = ans[pidx] + add;
			}
			return true;
		}()) cout << ans << "\n";
		else cout << "-1\n";


		
	}

	return 0;
}
