#include <cstdio>
const int N = 200005;
long long a[N], d[N];
int main() {
    int n, q;
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &a[i]);
        d[i] = a[i] - a[i - 1];
    }
    while (q--) {
        int l, r; long long v;
        scanf("%d%d%lld", &l, &r, &v);
        d[l] += v; d[r + 1] -= v;
    }
    long long x = 0;
    for (int i = 1; i <= n; i++) {
        x += d[i];
        printf("%lld%c", x, i == n ? '\n' : ' ');
    }
    return 0;
}
