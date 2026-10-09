#include <bits/stdc++.h>
using namespace std;
int main() {
    int n; long long k; cin >> n >> k;
    vector<long long> a(n);
    long long hi = 0;
    for (auto &x : a) { cin >> x; hi = max(hi, x); }
    auto ok = [&](long long len) {
        long long count = 0;
        for (long long x : a) { count += x / len; if (count >= k) return true; }
        return false;
    };
    long long lo = 0;
    while (lo < hi) {
        long long mid = lo + (hi - lo + 1) / 2;
        if (ok(mid)) lo = mid; else hi = mid - 1;
    }
    cout << lo << '\n';
}
