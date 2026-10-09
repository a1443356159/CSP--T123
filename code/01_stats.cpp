#include <cstdio>
#include <cstdlib>
#include <climits>
long long a[200005];
int compare(const void *p, const void *q) {
    long long x = *(const long long *)p;
    long long y = *(const long long *)q;
    if (x < y) return -1;
    if (x > y) return 1;
    return 0;
}
int main() {
    int n;
    scanf("%d", &n);
    long long sum = 0, mn = LLONG_MAX, mx = LLONG_MIN;
    for (int i = 0; i < n; i++) {
        scanf("%lld", &a[i]); sum += a[i];
        if (a[i] < mn) mn = a[i];
        if (a[i] > mx) mx = a[i];
    }
    qsort(a, n, sizeof(a[0]), compare);
    long long mode = a[0];
    int best = 0, i = 0;
    while (i < n) {
        int j = i;
        while (j < n && a[j] == a[i]) j++;
        if (j - i > best) { best = j - i; mode = a[i]; }
        i = j;
    }
    printf("%lld %lld %lld\n%lld %d\n", sum, mn, mx, mode, best);
    return 0;
}
