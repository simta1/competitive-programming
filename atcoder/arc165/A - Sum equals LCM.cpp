#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	int TC;
	for (cin >> TC; TC--;) {
		int n;
		cin >> n;

		if ([&]() {
			int cnt = 0;
			for (int p = 2; p <= n / p; p++) if (n % p == 0) {
				while (n % p == 0) n /= p;
				++cnt;
			}
			cnt += n > 1;
			return cnt >= 2;
		}()) cout << "Yes\n";
		else cout << "No\n";
	}

	return 0;
}
