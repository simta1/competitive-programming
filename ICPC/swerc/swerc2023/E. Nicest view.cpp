#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Frac {
	ll a, b;
	bool operator<(const Frac &o) const {
		return a * o.b < o.a * b;
	}
};

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	int n;
	cin >> n;

	vector<int> v(n);
	for (auto &e : v) cin >> e;

	Frac ans = {0, 1};

	auto f = [&]() {
		stack<int> s;
		for (int i = 0; i < n; i++) {
			while (!s.empty() && v[s.top()] < v[i]) s.pop();
			if (!s.empty()) {
				int j = s.top();
				ll dy = v[j] - v[j + 1];
				ans = max(ans, Frac{(i - j) * dy - v[j] + v[i], dy});
			}
			s.push(i);
		}
	};

	f();
	reverse(v.begin(), v.end());
	f();

	auto [a, b] = ans;
	ll g = __gcd(a, b);
	a /= g, b /= g;
	cout << a;
	if (b != 1) cout << "/" << b << "\n";

	return 0;
}
