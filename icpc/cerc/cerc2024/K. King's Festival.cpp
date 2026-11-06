#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using uint = unsigned int;

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	string st;
	cin >> st;

	int n = st.size();
	if (n == 1) {
		cout << "1\n#";
		return 0;
	}

	array<string, 2> candi{};
	for (int i = 0; i < n; i++) candi[i & 1] += st[i];

	int ans = 2e9;
	string ans_st;

	for (int p = 0; p < 2; p++) {
		auto st = candi[p];
		int cnt = n - st.size();
		auto dfs = [&](auto &&dfs, int idx, uint mask) {
			int cur = cnt + __builtin_popcount(mask);
			if (cur >= ans) return;

			if (idx == st.size()) {
				ans = cur;
				ans_st = string(n, '#');
				for (int i = 0; i < st.size(); i++) if (~mask >> i & 1) ans_st[i << 1 | p] = '.';
				return;
			}

			dfs(dfs, idx + 1, mask | 1u << idx);
			if (st[idx] == '.') {
				bool flag = 1;
				for (int i = 0; i < idx; i++) if (~mask >> i & 1) {
					if (i + idx & 1) continue;
					int j = i + idx >> 1;
					if (~mask >> j & 1) flag = 0;
				}
				if (flag) dfs(dfs, idx + 1, mask);
			}
		};
		dfs(dfs, 0, 0);
	}
	cout << ans << "\n" << ans_st;

	return 0;
}
