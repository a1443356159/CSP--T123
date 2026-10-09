#include <bits/stdc++.h>
using namespace std;
int main() {
    int n; cin >> n; vector<int> a(n), f(n,1);
    for (int &x : a) cin >> x;
    int answer = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < i; ++j) if (a[j] < a[i]) f[i] = max(f[i], f[j]+1);
        answer = max(answer, f[i]);
    }
    cout << answer << '\n';
}
