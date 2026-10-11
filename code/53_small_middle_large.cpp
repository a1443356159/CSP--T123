#include <cstdio>
int a[100005];
int main() {
    int n; scanf("%d", &n);
    for (int i = 0; i < n; i++) scanf("%d", &a[i]);
    int low = a[0] < a[n-1] ? a[0] : a[n-1];
    int high = a[0] > a[n-1] ? a[0] : a[n-1];
    long long twice = n%2 ? 2LL*a[n/2] : 1LL*a[n/2-1]+a[n/2];
    printf("%d ", high);
    if (twice % 2 == 0) printf("%lld", twice/2);
    else printf("%.1f", twice/2.0);
    printf(" %d\n", low);
    return 0;
}
