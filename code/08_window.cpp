#include <bits/stdc++.h>
using namespace std;
int main() {
    int n; long long k; cin >> n >> k;
    vector<long long> a(n);
    for (auto &x : a) cin >> x;
    if (k <= 1) { cout << 0 << '\n'; return 0; }
    long long product = 1, answer = 0; int left = 0;
    for (int right = 0; right < n; ++right) {
        product *= a[right];
        while (left <= right && product >= k) product /= a[left++];
        answer += right - left + 1;
    }
    cout << answer << '\n';
}
