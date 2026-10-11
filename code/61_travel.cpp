#include <cstdio>
int d[200005];
int main() {
    int n, m, k; scanf("%d%d%d", &n, &m, &k);
    for (int i = 0; i < n; i++) {
        int t, c; scanf("%d%d", &t, &c);
        int l = t-c+1-k, r = t-k;
        if (l < 1) l = 1;
        if (l <= r) { d[l]++; d[r+1]--; }
    }
    for (int q = 1; q <= 200000; q++) d[q] += d[q-1];
    while (m--) { int q; scanf("%d", &q); printf("%d\n", d[q]); }
    return 0;
}
