#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n, q; cin >> n >> q;
    vector<long long> a(n+1), d(n+2);
    for (int i = 1; i <= n; ++i) { cin >> a[i]; d[i] = a[i] - a[i-1]; }
    while (q--) { int l, r; long long v; cin >> l >> r >> v; d[l] += v; d[r+1] -= v; }
    long long x = 0;
    for (int i = 1; i <= n; ++i) { x += d[i]; cout << x << (i == n ? '\n' : ' '); }
}
