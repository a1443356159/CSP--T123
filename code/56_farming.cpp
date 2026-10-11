#include <cstdio>
int t[100005], c[100005], n; long long budget;
bool possible(int days) {
    long long cost = 0;
    for (int i = 0; i < n; i++) {
        if (t[i] > days) cost += 1LL*(t[i]-days)*c[i];
        if (cost > budget) return false;
    }
    return true;
}
int main() {
    int k, hi = 0; scanf("%d%lld%d", &n, &budget, &k);
    for (int i = 0; i < n; i++) {
        scanf("%d%d", &t[i], &c[i]); if (t[i] > hi) hi = t[i];
    }
    int lo = k;
    while (lo < hi) {
        int mid = lo+(hi-lo)/2;
        if (possible(mid)) hi = mid;
        else lo = mid+1;
    }
    printf("%d\n", lo);
    return 0;
}
