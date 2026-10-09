#include <cstdio>
const int N = 200005;
long long pre[N];
int main() {
    int n, q;
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++) {
        long long x;
        scanf("%lld", &x);
        pre[i] = pre[i - 1] + x;
    }
    while (q--) {
        int l, r;
        scanf("%d%d", &l, &r);
        printf("%lld\n", pre[r] - pre[l - 1]);
    }
    return 0;
}
