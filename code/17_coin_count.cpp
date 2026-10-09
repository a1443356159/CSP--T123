#include <bits/stdc++.h>
using namespace std;
int main() {
    int n, target; cin >> n >> target;
    const int MOD = 1000000007;
    vector<int> f(target+1); f[0] = 1;
    for (int i = 0; i < n; ++i) {
        int c; cin >> c;
        for (int v = c; v <= target; ++v) f[v] = (f[v]+f[v-c])%MOD;
    }
    cout << f[target] << '\n';
}
