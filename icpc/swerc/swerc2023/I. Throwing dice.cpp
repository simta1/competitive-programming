#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	int n, m;
	cin >> n >> m;

	vector<int> a(n), b(m);
	for (auto &e : a) cin >> e;
	for (auto &e : b) cin >> e;

	ll sum1 = n + accumulate(a.begin(), a.end(), 0LL);
	ll sum2 = m + accumulate(b.begin(), b.end(), 0LL);
	if (sum1 > sum2) cout << "ALICE";
	else if (sum1 == sum2) cout << "TIED";
	else cout << "BOB";

	return 0;
}
