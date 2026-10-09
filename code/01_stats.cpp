#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; cin >> n;
    long long sum = 0, mn = LLONG_MAX, mx = LLONG_MIN;
    map<long long, int> cnt;
    for (int i = 0; i < n; ++i) {
        long long x; cin >> x;
        sum += x; mn = min(mn, x); mx = max(mx, x); ++cnt[x];
    }
    long long mode = 0; int best = 0;
    for (auto [x, c] : cnt) {
        if (c > best) { best = c; mode = x; }
    }
    cout << sum << ' ' << mn << ' ' << mx << '\n';
    cout << mode << ' ' << best << '\n';
}
