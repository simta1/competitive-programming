#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	int n;
	cin >> n;

	vector<int> p(n + 1);
	vector<vector<int>> chd(n + 1);
	for (int i = 2; i <= n; i++) {
		cin >> p[i];
		chd[p[i]].push_back(i);
	}

	vector<int> dep(n + 1), top(n + 1);
	auto mkt = [&](auto &&mkt, int cur) -> void {
		for (auto nxt : chd[cur]) {
			top[nxt] = cur == 1 ? nxt : top[cur];
			dep[nxt] = dep[cur] + 1;
			mkt(mkt, nxt);
		}
	};
	mkt(mkt, 1);

	int mx = *max_element(dep.begin(), dep.end());
	int k = 1;
	auto input = [&]() {
		int res;
		cin >> res;
		if (res) exit(0);

		vector<int> cnt(k + 1);
		for (int i = 1; i <= k; i++) cin >> cnt[i];
		return cnt;
	};

	if (mx == 1) {
		cout << "1\n";
		for (int i = 2; i <= n; i++) cout << "1 ";
		cout << endl;
		auto cnt = input();
		cout << 1 << endl;
	}
	else {
		map<pair<int, int>, int> ans;
		vector<bool> flip(n + 1);
		if ([&]() -> bool {
			map<pair<int, int>, int> mps[101];
			for (int i = 2; i <= n; i++) {
				if (chd[i].empty()) continue;
				int cnt1, cnt2, tp;
				int go;
				if (dep[i] & 1) {
					cnt1 = 1, cnt2 = chd[i].size(), tp = top[i];
					go = 1;
				}
				else {
					cnt2 = 1, cnt1 = chd[i].size(), tp = top[i];
					go = 2;
				}
				pair<int, int> cur = {cnt1, cnt2};

				auto &mp = mps[tp];
				if (!mp.count(cur)) mp[cur] = go;
				else if (mp[cur] != go) return false;
			}

			for (int i = 1; i <= 100; i++) if (!mps[i].empty()) {
				bool flag = 0;
				for (auto [p, go] : mps[i]) {
					auto [c1, c2] = p;
					if (ans.count({c1, c2}) && ans[{c1, c2}] != go) {
						flag = 1;
						break;
					}
				}
				flip[i] = flag;
				for (auto [p, go] : mps[i]) {
					auto [c1, c2] = p;
					if (flag) ans[{c2, c1}] = 3 - go;
					else ans[p] = go;
				}
			}
			return true;
		}()) {
			k = 2;
			cout << "2\n";
			for (int i = 2; i <= n; i++) cout << ((dep[i] & 1) ^ flip[top[i]] ? 1 : 2) << " ";
			cout << endl;

			while (1) {
				auto cnt = input();
				if (!cnt[1]) cout << 2 << endl;
				else if (!cnt[2]) cout << 1 << endl;
				else cout << ans[{cnt[1], cnt[2]}] << endl;
			}
		}
		else {
			k = 3;
			cout << "3\n";
			for (int i = 2; i <= n; i++) cout << (dep[i] % 3 + 1) << " ";
			cout << endl;

			while (1) {
				auto cnt = input();
				if (cnt[2] && cnt[3]) cout << 2 << endl;
				else if (cnt[3] && cnt[1]) cout << 3 << endl;
				else if (cnt[1] && cnt[2]) cout << 1 << endl;
				else if (cnt[1]) cout << 1 << endl;
				else if (cnt[2]) cout << 2 << endl;
				else if (cnt[3]) cout << 3 << endl;
				else assert(false);
			}
		}
	}

	return 0;
}
