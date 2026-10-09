#include <cstdio>
const int MOD = 1000000007;
int f[10005];
int main() {
    int n, target;
    scanf("%d%d", &n, &target);
    f[0] = 1;
    for (int i = 0; i < n; i++) {
        int c;
        scanf("%d", &c);
        for (int v = c; v <= target; v++) f[v] = (f[v] + f[v - c]) % MOD;
    }
    printf("%d\n", f[target]);
    return 0;
}
