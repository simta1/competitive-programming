#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	string st = "0123456789";
	for (int i = 0; i < 26; i++) st += 'A' + i;

	int TC;
	for (cin >> TC; TC--;) {
		int n, m;
		ll k;
		cin >> n >> k >> m;

		vector<bool> rm(n);
		while (m--) {
			char c;
			cin >> c;
			if (isdigit(c)) rm[c - '0'] = 1;
			else rm[c - 'A' + 10] = 1;
		}

		string cur;
		for (int i = 0; i < n; i++) if (!rm[i]) cur += st[i];

		string ans;
		while (k) {
			ans += cur[k % cur.size()];
			k /= cur.size();
		}
		reverse(ans.begin(), ans.end());
		cout << ans << "\n";
	}

	return 0;
}
