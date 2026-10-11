#include <cstdio>
long long n; int k, m;
bool enough(long long robots) {
    long long remain = n;
    for (int day = 1; day <= m; day++) {
        // ceil(remain*k/100), without overflowing remain*k.
        long long bad = (remain/100)*k + ((remain%100)*k+99)/100;
        remain -= bad;
        if (remain < robots) return false;
        remain -= robots;
    }
    return true;
}
int main() {
    scanf("%lld%d%d", &n, &k, &m);
    long long lo = 0, hi = n/m;
    if (hi > 1000000000LL) hi = 1000000000LL;
    while (lo < hi) {
        long long mid = lo+(hi-lo+1)/2;
        if (enough(mid)) lo = mid;
        else hi = mid-1;
    }
    printf("%lld\n", lo);
    return 0;
}
