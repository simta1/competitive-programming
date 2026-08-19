#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n;
    string st;
    cin >> n >> st;

    vector<int> pi(n);
    for (int i = 1, j = 0; i < n; i++) {
        while (j && st[i] != st[j]) j = pi[j - 1];
        if (st[i] == st[j]) pi[i] = ++j;
    }
    int T = n - pi.back();
    if (n % T) T = n;

    cout << n / T << "\n" << n * n << "\n";
    for (int i = 0; i < n; i++) cout << st;

    return 0;
}
