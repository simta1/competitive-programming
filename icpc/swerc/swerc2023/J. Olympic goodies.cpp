#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	int n, p;
	cin >> n >> p;

	vector<int> deg(n + 1);
	for (int i = 1; i < n; i++) {
	    int u, v;
	    cin >> u >> v;
		++deg[u], ++deg[v];
	}

	int cnt = 0;
	for (int i = 1; i <= n; i++) {
		cnt += deg[i] == 1;
	}

	int q = p / cnt, r = p % cnt;
	cout << 2 * q + min(2, r);

	return 0;
}
