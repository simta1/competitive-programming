#include <bits/stdc++.h>
using namespace std;
using ll = long long;

template <typename T>
vector<int> getPi(const T &st) { // O(N)
	vector<int> pi(st.size());
	for (int i = 1, j = 0; i < st.size(); i++) {
		while (j > 0 && st[i] != st[j]) j = pi[j - 1];
		if (st[i] == st[j]) pi[i] = ++j;
	}
	return pi;
}

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	string st;
	cin >> st;

	int n = st.size();
	bool same = 1;
	for (int i = 1; i < n; i++) if (st[i] != st[0]) same = 0;

	if (same) {
		cout << n << "\n" << 1;
		return 0;
	}

	auto pi = getPi(st);
	int len = n - pi.back();
	if (len < n && n % len == 0) {
		vector<bool> pref(n);
		for (int i = 0; i < n - 1; i++) {
			pref[i] = pi[i] && (i + 1) % (i + 1 - pi[i]) == 0;
		}

		auto rev = st;
		reverse(rev.begin(), rev.end());
		auto pi2 = getPi(rev);
		vector<bool> suf(n);
		for (int i = 0; i < n - 1; i++) {
			suf[n - 1 - i] = pi2[i] && (i + 1) % (i + 1 - pi2[i]) == 0;
		}

		int ans = 0;
		for (int i = 0; i < n - 1; i++) ans += !pref[i] && !suf[i + 1];
		cout << "2\n" << ans;
	}
	else cout << "1\n1";

	return 0;
}
