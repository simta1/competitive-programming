#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int f(char ch) {
	return 1 << (ch - 'a');
}

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	int n;
	ll T;
	cin >> n >> T;

	string st;
	cin >> st;

	ll sum = f(st.back()) - f(st[n - 2]);
	vector<int> v;
	for (int i = 0; i < n - 2; i++) {
		int cur = f(st[i]);
		sum -= cur;
		// v.push_back(st[i] - 'a' + 1);
		v.push_back(cur * 2);
	}

	ll need = T - sum;

	sort(v.rbegin(), v.rend());
	for (auto e : v) {
		if (need >= e) need -= e;
	}

	if (need == 0) cout << "Yes\n";
	else cout << "No\n";

	return 0;
}
