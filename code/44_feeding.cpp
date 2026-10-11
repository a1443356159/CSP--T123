#include <cstdio>
long long f[10005];
int value[105];
int main() {
    int n, m; scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) scanf("%d", &value[i]);
    const long long NEG = -(1LL << 60);
    for (int v = 1; v <= n; v++) f[v] = NEG;
    f[0] = 0;
    for (int v = 1; v <= n; v++) {
        for (int i = 1; i <= m && i <= v; i++) {
            if (f[v-i] != NEG && f[v-i]+value[i] > f[v])
                f[v] = f[v-i]+value[i];
        }
    }
    printf("%lld\n", f[n]);
    return 0;
}
