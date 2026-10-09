#include <cstdio>
#include <climits>
const int N = 1005;
long long d[N][N];
int main() {
    int n, m, q;
    scanf("%d%d%d", &n, &m, &q);
    while (q--) {
        int x1, y1, x2, y2; long long v;
        scanf("%d%d%d%d%lld", &x1, &y1, &x2, &y2, &v);
        d[x1][y1] += v; d[x2 + 1][y1] -= v;
        d[x1][y2 + 1] -= v; d[x2 + 1][y2 + 1] += v;
    }
    long long best = LLONG_MIN, count = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            d[i][j] += d[i - 1][j] + d[i][j - 1] - d[i - 1][j - 1];
            if (d[i][j] > best) { best = d[i][j]; count = 1; }
            else if (d[i][j] == best) count++;
        }
    }
    printf("%lld %lld\n", best, count);
    return 0;
}
