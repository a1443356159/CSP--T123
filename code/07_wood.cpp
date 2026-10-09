#include <cstdio>
const int N = 200005;
int n;
long long k, a[N];
int check(long long len) {
    long long count = 0;
    for (int i = 0; i < n; i++) {
        count += a[i] / len;
        if (count >= k) return 1;
    }
    return 0;
}
int main() {
    scanf("%d%lld", &n, &k);
    long long lo = 0, hi = 0;
    for (int i = 0; i < n; i++) {
        scanf("%lld", &a[i]);
        if (a[i] > hi) hi = a[i];
    }
    while (lo < hi) {
        long long mid = lo + (hi - lo + 1) / 2;
        if (check(mid)) lo = mid;
        else hi = mid - 1;
    }
    printf("%lld\n", lo);
    return 0;
}
