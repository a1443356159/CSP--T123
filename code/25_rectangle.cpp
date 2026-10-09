#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n, m, q; cin >> n >> m >> q;
    vector<vector<long long>> d(n+2, vector<long long>(m+2));
    while (q--) {
        int x1,y1,x2,y2; long long v; cin >> x1 >> y1 >> x2 >> y2 >> v;
        d[x1][y1] += v; d[x2+1][y1] -= v;
        d[x1][y2+1] -= v; d[x2+1][y2+1] += v;
    }
    long long best = LLONG_MIN, count = 0;
    for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) {
        d[i][j] += d[i-1][j] + d[i][j-1] - d[i-1][j-1];
        if (d[i][j] > best) { best = d[i][j]; count = 1; }
        else if (d[i][j] == best) ++count;
    }
    cout << best << ' ' << count << '\n';
}
