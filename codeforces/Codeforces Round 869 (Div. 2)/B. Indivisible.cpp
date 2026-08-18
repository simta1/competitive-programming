#include <bits/stdc++.h>
using namespace std;
using ll = long long;

bool check(const vector<int> &v) {
    for (int l = 0; l < v.size(); l++) {
        for (int r = l + 1; r < v.size(); r++) {
            int sum = 0;
            for (int i = l; i <= r; i++) sum += v[i];
            if (sum % (r - l + 1) == 0) return false;
        }
    }
    return true;
}

void f(int n) {
    vector<int> v(n);
    iota(v.begin(), v.end(), 1);
    do {
        if (check(v)) {
            for (auto &e : v) cout << e << " "; cout << "\n";
            return;
        }
    } while (next_permutation(v.begin(), v.end()));
}

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    // for (int n = 1; n <= 12; n++) {
    //     cout << n << "::\n";
    //     f(n);
    // }

    int TC;
    for (cin >> TC; TC--;) {
        int n;
        cin >> n;

        if (n == 1) cout << "1\n";
        else if (n == 2) cout << "1 2\n";
        else if (n & 1) cout << "-1\n";
        else {
            vector<int> v(n);
            for (int i = 0; i < n; i += 2) v[i] = i + 2;
            for (int i = 1; i < n; i += 2) v[i] = i;
            assert(check(v));
            for (auto &e : v) cout << e << " ";
            cout << "\n";
        }
    }

    return 0;
}
