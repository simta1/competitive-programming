#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	int n, m, k;
	cin >> n >> m >> k;

	vector v(n, vector<bool>(m));
	vector<int> cnt(n);
	while (k--) {
		int a, b;
		cin >> a >> b;
		--a, --b;
		if (!v[a][b]) {
			v[a][b] = 1;
			if (++cnt[a] == m) cout << a + 1 << " ";
		}
	}



	return 0;
}
