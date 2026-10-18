#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n;
    cin >> n;

    if (n & 1) cout << n / 2;
    else if (n & 3) cout << n / 2 - 2;
    else cout << n / 2 - 1;

    return 0;
}
